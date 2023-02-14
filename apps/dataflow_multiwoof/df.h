#ifndef DF_H
#define DF_H

// opcodes

#define OPCODES \
    OP(OPERAND) \
    OP(ADD)     \
    OP(SUB)     \
    OP(MUL)     \
    OP(DIV)     \
    OP(SQR)     \
    OP(LT)      \
    OP(GT)      \
    OP(EQ)      \
    OP(ABS)     \
    OP(NOT)     \
    OP(SEL)     \
    OP(FILTER)  \
    OP(OFFSET)  \
    OP(FUNC)

enum Opcode {
#define OP(name) name,
  OPCODES
#undef OP
    OPCODES_N
};

static const char* OPCODE_STR[OPCODES_N] = {
#define OP(name) [name] = #name,
    OPCODES
#undef OP
};

struct operand {
    double value;
    unsigned long seq;

    operand(double value=0.0, unsigned long seq=1) : value(value), seq(seq) {}
};

struct subscriber {
    int ns;  // namespace
    int id;
    int port;

    subscriber(int dst_ns = 0, int dst_id = 0, int dst_port = 0)
        : ns(dst_ns), id(dst_id), port(dst_port) {}

    bool operator<(const subscriber& other) const { return id < other.id; }
};

struct subscription {
    int ns;
    int id;
    int port;

    subscription(int src_ns = 0, int src_id = 0, int dst_port = 0)
        : ns(src_ns), id(src_id), port(dst_port) {}

    bool operator<(const subscription& other) const {
        return port < other.port;
    }
};

struct subscription_event {
    int ns;
    int id;
    int port;
    unsigned long seq;

    subscription_event(int ns=0, int id=0, int port=0, unsigned long seqno=0)
        : ns(ns), id(id), port(port), seq(seqno) {}
};

struct node {
    int id;
    int opcode;

    node(int id=0, int opcode=0) : id(id), opcode(opcode) {}

    bool operator<(const node& other) const {
        return id < other.id;
    }
};


#endif
