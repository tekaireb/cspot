#include "msgpack-ep.h"
#include <iostream>
#include <thread>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <cwpack.hpp>

#include <string>
#include <vector>

#include <memory>

#include <cwpack.h>
#include <caps/emsha_signer.hpp>
#include <caps/request.hpp>
#include <cppspot/capabilities.hpp>
#include <nonstd/variant.hpp>
#include <tos/print.hpp>

extern "C"
{
#include "woofc-access.h"
#include "woofc.h"
void WooFFree(WOOF *wf);
}

using namespace tos;

struct sock_stream
{
	sock_stream(int fd) : m_fd(fd) {}
	~sock_stream()
	{
		close(m_fd);
	}

	span<char> read(span<char> buf)
	{
		auto ret = ::read(m_fd, buf.data(), buf.size());
		return buf.slice(0, ret);
	}

	size_t write(span<const char> buf)
	{
		return ::write(m_fd, buf.data(), buf.size());
	}

	sock_stream* operator->() { return this; }
	sock_stream& operator*() { return this; }

private:
	int m_fd;
};

template <class Container, class From>
Container parse_container(From& f)
{
	using el_t = typename Container::value_type;
	return Container { (const el_t*)f.start, (const el_t*)f.start + f.length };
}

void handle_put(int sock_fd, cw_unpack_context& uc)
{
    cw_unpack_next(&uc);
    if (uc.item.type != cwpack_item_types::CWP_ITEM_STR)
    {
    	std::cerr << "should've been a string\n";
    	return;
    }

    auto wf = parse_container<std::string>(uc.item.as.str);

    cw_unpack_next(&uc);
    if (uc.item.type != cwpack_item_types::CWP_ITEM_STR)
    {
    	std::cerr << "should've been a string\n";
    	return;
    }

    auto handler = parse_container<std::string>(uc.item.as.str);

    cw_unpack_next(&uc);
    if (uc.item.type != cwpack_item_types::CWP_ITEM_BIN)
    {
    	std::cerr << "should've been a binary array\n";
    	return;
    }

    auto buf = parse_container<std::vector<uint8_t>>(uc.item.as.bin);

    auto err = WooFPut(wf.c_str(), handler.c_str(), buf.data());

	char b[32];
	tos::msgpack::packer p {b};
	p.insert(uint32_t(err));
	auto res = p.get();

	write(sock_fd, res.data(), res.size());
}

using woof_ptr = std::unique_ptr<WOOF, decltype(&WooFFree)>;

size_t get_elem_sz(const char* woof)
{
	auto wf = woof_ptr(WooFOpen(woof), WooFFree);
	if (!wf) return -1;
	return wf->shared->element_size;
}

void handle_el_sz(int sock_fd, cw_unpack_context& uc)
{
    cw_unpack_next(&uc);
    if (uc.item.type != cwpack_item_types::CWP_ITEM_STR)
    {
    	std::cerr << "should've been a string\n";
    	return;
    }

    auto wf_name = parse_container<std::string>(uc.item.as.str);

    std::cerr << "sz of " << wf_name << '\n';

	char buf[32];
	tos::msgpack::packer p {buf};
	p.insert(uint32_t(get_elem_sz(wf_name.c_str())));
	auto res = p.get();

	write(sock_fd, res.data(), res.size());
}

void handle_get(int sock_fd, cw_unpack_context& uc)
{
	cw_unpack_next(&uc);
    if (uc.item.type != cwpack_item_types::CWP_ITEM_STR)
    {
    	std::cerr << "should've been a string\n";
    	return;
    }

    auto wf = parse_container<std::string>(uc.item.as.str);

	cw_unpack_next(&uc);
    if (uc.item.type != cwpack_item_types::CWP_ITEM_POSITIVE_INTEGER)
    {
    	std::cerr << "should've been an unsigned int (woof seq)\n";
    	return;
    }

    uint64_t seq = uc.item.as.u64;

    std::cerr << "woof get from " << wf << " at " << seq << '\n';

    auto elem_sz = get_elem_sz(wf.c_str());

    std::vector<uint8_t> buf(elem_sz);
    auto res = WooFGet(wf.c_str(), buf.data(), seq);

    std::vector<char> packet_buf(elem_sz + 4);
    tos::msgpack::packer p({packet_buf.data(), size_t(packet_buf.size())});
    auto arr = p.insert_arr(2);
    arr.insert(uint32_t(res));
    arr.insert(tos::span<const uint8_t>{ buf.data(), size_t(buf.size()) });

	auto r = p.get();

	write(sock_fd, r.data(), r.size());
}


namespace cspot
{
    struct put_req
    {
        char woof[16];
        std::vector<uint8_t> data;
        char handler[12];
        uint32_t host;
        event_seq_t host_seq;
    };

    using reqs = mpark::variant<mpark::monostate, put_req>;

    cspot::cap_t req_to_tok(const reqs& r)
    {
        struct
        {
            cap_t operator()(const mpark::monostate&) { return cap_t{}; }
            cap_t operator()(const put_req&) { return cap_t{woof_id_t{1}, perms::put}; }
        } vis;

        return mpark::visit(vis, r);
    }

    enum class parse_error
    {
        unexpected
    };

    tos::expected<put_req, parse_error> parse_put_req(cw_unpack_context& uc)
    {
        put_req res;
        {
            cw_unpack_next(&uc);
            if (uc.item.type != cwpack_item_types::CWP_ITEM_STR)
            {
                return tos::unexpected(parse_error::unexpected);
            }

            auto tmp = parse_container<std::string>(uc.item.as.str);
            std::strncpy(res.woof, tmp.data(), std::size(res.woof));
        }

        {
            cw_unpack_next(&uc);
            if (uc.item.type != cwpack_item_types::CWP_ITEM_STR)
            {
                return tos::unexpected(parse_error::unexpected);
            }

            auto tmp = parse_container<std::string>(uc.item.as.str);
            std::strncpy(res.handler, tmp.data(), std::size(res.handler));
        }

        cw_unpack_next(&uc);
        if (uc.item.type != cwpack_item_types::CWP_ITEM_POSITIVE_INTEGER)
        {
            return tos::unexpected(parse_error::unexpected);
        }

        res.host = uc.item.as.u64;

        cw_unpack_next(&uc);
        if (uc.item.type != cwpack_item_types::CWP_ITEM_POSITIVE_INTEGER)
        {
            return tos::unexpected(parse_error::unexpected);
        }

        res.host_seq = {(uint16_t)uc.item.as.u64};

        cw_unpack_next(&uc);
        if (uc.item.type != cwpack_item_types::CWP_ITEM_BIN)
        {
            return tos::unexpected(parse_error::unexpected);
        }

        res.data = parse_container<std::vector<uint8_t>>(uc.item.as.bin);

        return res;
    }

    reqs parse_req(tos::span<const uint8_t> buf)
    {
        cw_unpack_context uc;
        cw_unpack_context_init(&uc, (void*)buf.data(), buf.size(), nullptr);

        cw_unpack_next(&uc);
        if (uc.item.type != cwpack_item_types::CWP_ITEM_ARRAY) {
            return mpark::monostate{};
        }

        cw_unpack_next(&uc);
        if (uc.item.type != cwpack_item_types::CWP_ITEM_POSITIVE_INTEGER) {
            return mpark::monostate{};
        }

        uint8_t tag = uc.item.as.u64;

        tos_debug_print("got req %d\n", int(tag));

        switch (cspot::msg_tag(tag))
        {
            case cspot::msg_tag::put:
                return force_get(parse_put_req(uc));
                break;
            case cspot::msg_tag::get_el_sz:
                //handle_el_sz(ep, uc);
                break;
            case cspot::msg_tag::get:
                //handle_get(ep, uc);
                break;
            case cspot::msg_tag::get_log:
                //handle_get_log(ep, uc);
                break;
            case cspot::msg_tag::get_log_size:
                //handle_get_log_size(ep, uc);
                break;
            default:
                break;
        }
        return mpark::monostate{};
    }
}

auto client_key = []{
    caps::emsha::signer signer("sekkret");

    return caps::mkcaps({
        cspot::mkcap(cspot::root_cap, cspot::perms::root) }, signer);
}();

caps::emsha::signer signer("sekret");
auto proc = caps::req_deserializer<cspot::cap_t>(signer, cspot::parse_req, cspot::satisfies);

template <class Ep>
struct req_handlers
{
    void operator()(const mpark::monostate&) {
        ep.write("unknown error");
    }
    void operator()(const cspot::put_req& put)
    {
        auto err = WooFPut2(put.woof, put.handler, put.data.data(), put.host, put.host_seq.seq);
        tos::println(ep, "putting in", put.woof, put.handler, int(put.data.size()), int(err));

        char b[100];
        tos::msgpack::packer p {b};
        p.insert(uint32_t(err));
        auto res = p.get();

        auto h = signer.hash(res);

        auto t = clone(*client_key);
        t->signature = get_req_sign(*t, signer, 1000, h);

        ep.write({res.data(), res.size()});
        caps::serialize(ep, *t);
    }

    Ep& ep;
};

void handle_sock(int sock_fd, sockaddr_in addr)
{
	sock_stream sock{sock_fd};

    char buffer[100];
    auto res = sock.read(buffer);
    auto x = proc(res);

    if (!x)
    {
    	std::cerr << "auth fail " << int(force_error(x)) << '\n';
    	return;
    }

    auto& req = force_get(x);

	req_handlers<sock_stream> s{sock};

	mpark::visit(handle, req);
}

extern "C"
{
	void* WooFMsgPackThread(void* arg)
	{
		uint16_t port = *((int*)arg) - 10000;

		auto sock = socket(AF_INET, SOCK_STREAM, 0);

		if (sock <= 0)
		{
			perror("socket error");
			return nullptr;
		}

		sockaddr_in address;

		address.sin_family = AF_INET;
    	address.sin_addr.s_addr = INADDR_ANY;
    	address.sin_port = htons(port);

		if (bind(sock, (sockaddr *)&address, sizeof address) < 0)
		{
			perror("bind error");
			return nullptr;
		}

		if (listen(sock, 3) < 0)
		{
			perror("listen error");
			return nullptr;
		}

		std::cerr << "listening on " << port << '\n';

		while(true)
		{
			sockaddr_in cli_addr;
			socklen_t addrlen = sizeof cli_addr;
			auto new_sock = accept(sock, (sockaddr*)&cli_addr, &addrlen);
			std::thread t{[=]{
				handle_sock(new_sock, cli_addr);
			}};
			t.detach();
		}
	}
}