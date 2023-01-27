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
    OP(SEL)     

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

    operand(double value=0.0) : value(value) {}
};

struct subscriber {
    int id;
    int port;

    subscriber(int dst_id=0, int dst_port=0) : id(dst_id), port(dst_port) {}

    bool operator<(const subscriber& other) const {
        return id < other.id;
    }
};

struct subscription {
    int id;
    int port;

    subscription(int src_id=0, int dst_port=0) : id(src_id), port(dst_port) {}

    bool operator<(const subscription& other) const {
        return port < other.port;
    }
};

struct subscription_event {
    int id;
    int port;
    unsigned long seq;

    subscription_event(int id=0, int port=0, unsigned long seqno=0)
        : id(id), port(port), seq(seqno) {}
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
