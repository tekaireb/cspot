#include "df.h"
#include "dfinterface.h"

#include <iostream>
#include <string>

#include <unistd.h>

int subscribe_entries = 0;
std::map<int, std::set<subscriber>> subscribers;
std::map<int, std::set<subscription>> subscriptions;
std::set<node> nodes;

void woof_create(std::string name, unsigned long element_size,
                 unsigned long history_size) {
    WooFInit(); /* attach local namespace for create */

    int err = WooFCreate(name.c_str(), element_size, history_size);
    if (err < 0) {
        std::cerr << "ERROR -- creation of " << name << " failed\n";
        exit(1);
    }
}

unsigned long woof_put(std::string name, std::string handler, const void* element) {
    unsigned long seqno = WooFPut(name.c_str(), handler.c_str(), element);

    if (WooFInvalid(seqno)) {
        std::cerr << "ERROR -- put to " << name << " failed\n";
        exit(1);
    }

    return seqno;
}

void woof_get(std::string name, void* element, unsigned long seq_no) {
    int err = WooFGet(name.c_str(), element, seq_no);
    if (err < 0) {
        std::cerr << "ERROR -- get [" << seq_no << "] from " << name << " failed\n";
        exit(1);
    }
}

unsigned long woof_last_seq(std::string name) {
    return WooFGetLatestSeqno(name.c_str());
}

void add_node(const std::string& program, int id, int opcode) {
    std::string id_str = std::to_string(id);

    // Create output woof
    woof_create(program + ".output." + id_str, sizeof(operand), 10);

    // Create subscription_events woof
    woof_create(program + ".subscription_events." + id_str,
                sizeof(subscription_event), 25);

    // Create consumer_pointer woof
    std::string consumer_ptr_woof = program + ".subscription_pointer." + id_str;
    unsigned long initial_consumer_ptr = 1;
    // TODO: consumer_ptr_woof should be of size 1, but CSPOT hangs when
    // writing to full woof (instead of overwriting), so the size has
    // been increased temporarily as a stop-gap measure while testing
    woof_create(consumer_ptr_woof, sizeof(unsigned long), 100);
    woof_put(consumer_ptr_woof, "", &initial_consumer_ptr);

    // Create node
    nodes.insert(node(id, opcode));
}

void add_operand(const std::string& program, int id) {
    std::string id_str = std::to_string(id);

    // Create output woof
    woof_create(program + ".output." + id_str, sizeof(operand), 10);

    nodes.insert(node(id, OPERAND));
}

void subscribe(int dst_id, int dst_port, int src_id) {
    subscribers[src_id].insert(subscriber(dst_id, dst_port));
    subscriptions[dst_id].insert(subscription(src_id, dst_port));

    subscribe_entries++;
}

void setup(const std::string& program) {
    // Create woof hashmaps to hold subscribers
    woof_create(program + ".subscriber_map", sizeof(unsigned long), nodes.size());
    woof_create(program + ".subscriber_data", sizeof(subscriber),
                subscribe_entries);

    unsigned long current_data_pos = 1;
    for (size_t i = 1; i <= nodes.size(); i++) {
        // Add entry in map (idx = node id, val = start idx in subscriber_data)
        woof_put(program + ".subscriber_map", "", &current_data_pos);        
        
        for (auto& sub : subscribers[i]) {
            woof_put(program + ".subscriber_data", "", &sub);
            current_data_pos++;
        }
    }

    // Create woof hashmaps to hold subscriptions
    woof_create(program + ".subscription_map", sizeof(unsigned long), nodes.size());
    woof_create(program + ".subscription_data", sizeof(subscription),
                subscribe_entries);

    current_data_pos = 1;
    for (size_t i = 1; i <= nodes.size(); i++) {
        // Add entry in map (idx = node id, val = start idx in subscription_data)
        woof_put(program + ".subscription_map", "", &current_data_pos);
        
        for (auto& sub : subscriptions[i]) {
            woof_put(program + ".subscription_data", "", &sub);
            current_data_pos++;
        }
    }

    // Create woof to hold node data
    woof_create(program + ".nodes", sizeof(node), nodes.size());

    for (auto& node : nodes) {
        woof_put(program + ".nodes", "", &node);
    }
}

std::string graphviz_representation() {
    std::string g = "digraph G {\n\tnode [shape=\"record\", style=\"rounded\"];";

    // Add nodes
    auto n = nodes.begin();
    auto s = subscriptions.begin();
    while (n != nodes.end()) {
        g += "\n\tnode_" + std::to_string(n->id) + " [label=\"{";
        
        // Add ports
        if (n->opcode != OPERAND) {
            g += "{";
            for (size_t port = 0; port < s->second.size(); port++) {
                std::string p = std::to_string(port);
                g += "<" + p + "> " + p;
                if (port < s->second.size() - 1) {
                    g += '|';
                }
            }
            g += "}|";
        }

        g += "<out>[" + std::string(OPCODE_STR[n->opcode]);
        g += "]\\nNode #" + std::to_string(n->id) + "}\"];";
    
        n++;
        s++;
    }

    // Add edges
    for (auto& [id, subs] : subscribers) {
        g += "\n\tnode_" + std::to_string(id) + ":out -> {";
        for (auto& s : subs) {
            g += "node_" + std::to_string(s.id) + ":" + std::to_string(s.port);
        }
        g += "};";
    }

    g += "\n}";

    return g;
}



// void add_node(char* prog, int id) {
//     char woof_name_base[4096] = ""; // [prog].[id]
//     char woof_name[4096] = "";
//     char id_str[100] = "";

//     // Convert id to string
//     snprintf(id_str, sizeof(id_str), "%d", id);
    
//     // woof_name_base = "[prog].[id]"
//     strncpy(woof_name_base, prog, sizeof(woof_name_base));
//     strncat(woof_name_base, id_str,
//             sizeof(woof_name_base) - strlen(woof_name_base) - 1);

//     // Create output woof
//     strncpy(woof_name, woof_name_base, sizeof(woof_name));
//     strncat(woof_name, ".output", sizeof(woof_name) - strlen(woof_name) - 1);
//     woof_create(woof_name, sizeof(operand), 10);

//     // Create subscription_events woof
//     strncpy(woof_name, woof_name_base, sizeof(woof_name));
//     strncat(woof_name, ".subscription_events", 
//             sizeof(woof_name) - strlen(woof_name) - 1);
//     woof_create(woof_name, sizeof(subscription_event), 25);

//     // Create consumer_pointer woof
//     strncpy(woof_name, woof_name_base, sizeof(woof_name));
//     strncat(woof_name, ".subscription_pointer",
//             sizeof(woof_name) - strlen(woof_name) - 1);
//     woof_create(woof_name, sizeof(unsigned long), 1);
// }
