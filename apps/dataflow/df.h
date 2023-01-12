#ifndef DF_H
#define DF_H

// opcodes

#define ADD (1)
#define SUB (2)
#define MUL (3)
#define DIV (4)
#define SQR (5)

#define LT (6)
#define GT (7)
#define EQ (8)

#define MUX (9)
#define DEMUX (10)

enum df_node_state_enum
{
    WAITING,
    CLAIM,
    PARTIAL,
    DONE
};
typedef enum df_node_state_enum DF_NODE_STATE;

struct df_node_stc {
    DF_NODE_STATE state;       // the state of the node
    int node_id;               // which node is it
    int opcode;                // this op code
    int total_values_count;    // count of total values node has to receive
    int received_values_count; // count of values received by node
    double values[10];         // array of input values, mem alloc at runtime (only for partials)
    int destination_node_id;   // next node address
    int destination_port;      // next node port
    double claim_input_value;  // single value used in claims received by operand
    int claim_input_port;      // the port of the single value in claims received by operand
};
typedef struct df_node_stc DFNODE;

struct df_operand_stc {
    double value;            // operand value
    int destination_node_id; // dest node address
    int destination_port;    // dest node's port address
    char prog_woof[1024];    // name of woof holding the program
};
typedef struct df_operand_stc DFOPERAND;

extern double DFOperation(DFNODE *node, int opcode, double* values, int size);

#endif
