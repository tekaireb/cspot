#ifndef DF_H
#define DF_H

#include "operation_system/df_operations.h"
#include "type_system/df_type_builder.h"
#include "type_system/df_types.h"

#include <cmath>
#include <cstring>

enum DFWoofType
{
    OUTPUT_WOOF_TYPE = 0,
    SUBSCRIPTION_EVENTS_WOOF_TYPE,
    SUBSCRIPTION_POINTER_WOOF_TYPE,
    SUBSCRIBER_MAP_WOOF_TYPE,
    SUBSCRIBER_DATA_WOOF_TYPE,
    SUBSCRIPTION_MAP_WOOF_TYPE,
    SUBSCRIPTION_DATA_WOOF_TYPE,
    SUBSCRIPTION_POS_WOOF_TYPE,
    NODES_WOOF_TYPE,
    HOST_ID_WOOF_TYPE,
    HOSTS_WOOF_TYPE
};

static const char* DFWOOFTYPE_STR[] = {"output",
                                       "subscription_events",
                                       "subscription_pointer",
                                       "subscriber_map",
                                       "subscriber_data",
                                       "subscription_map",
                                       "subscription_data",
                                       "subscription_pos",
                                       "nodes",
                                       "host_id",
                                       "hosts"};

struct operand {
    DF_VALUE value;
    unsigned long seq;

    explicit operand(DF_VALUE value = {.type = DF_UNKNOWN, .value = {.df_int = 1}}, unsigned long seq = 1)
        : value(value)
        , seq(seq) {
    }
};

struct cached_output {
    operand op;
    unsigned long seq; // CSPOT seq in output woof

    // Defaults execution iteration and seq to 0 so initial access is thrown out and updated
    explicit cached_output(operand op = operand({.type = DF_UNKNOWN, .value = {.df_int = 1}}, 0), unsigned long seq = 0)
        : op(op)
        , seq(seq) {
    }
};

struct execution_iteration_lock {
    unsigned long iter; // Current execution iteration
    bool lock;          // True if a handler has claimed this iteration

    explicit execution_iteration_lock(unsigned long iter = 1, bool lock = false)
        : iter(iter)
        , lock(lock) {
    }
};

struct subscriber {
    int ns;
    int id;
    int port;

    explicit subscriber(int dst_ns = 0, int dst_id = 0, int dst_port = 0)
        : ns(dst_ns)
        , id(dst_id)
        , port(dst_port) {
    }

    bool operator<(const subscriber& other) const {
        return id < other.id;
    }
};

struct subscription {
    int ns;
    int id;
    int port;

    explicit subscription(int src_ns = 0, int src_id = 0, int dst_port = 0)
        : ns(src_ns)
        , id(src_id)
        , port(dst_port) {
    }

    bool operator<(const subscription& other) const {
        return port < other.port;
    }
};

struct subscription_event {
    int ns;
    int id;
    int port;
    unsigned long seq;

    explicit subscription_event(int ns = 0, int id = 0, int port = 0, unsigned long seqno = 0)
        : ns(ns)
        , id(id)
        , port(port)
        , seq(seqno) {
    }
};

struct node {
    int id;
    int host_id;
    DF_OPERATION operation;

    explicit node(int id = 0,
                  int host_id = 0,
                  DF_OPERATION operation = {.category = DF_INTERNAL, .operation = DF_INTERNAL_OPERAND})
        : id(id)
        , host_id(host_id)
        , operation(operation) {
    }

    bool operator<(const node& other) const {
        return id < other.id;
    }
};


struct host {
    int host_id;
    char host_url[200];

    explicit host(const int host_id_ = 0, const char host_url_[200] = "") {
        host_id = host_id_;
        strcpy(host_url, host_url_);
    }

    bool operator<(const host& other) const {
        return host_id < other.host_id;
    }
};


// #define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(str)                                                                                               \
    {                                                                                                                  \
        std::cout << "[" << woof_name << "] "                                                                          \
                  << "[" << consumer_seq << "] " << str << std::endl                                                   \
                  << std::flush;                                                                                       \
    }
#else
#define DEBUG_PRINT(str)                                                                                               \
    {}
#endif

#endif
