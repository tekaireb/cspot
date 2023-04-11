//
// Created by Lukas Brand on 29.03.23.
//

#ifndef CSPOT_DF_OPERATIONS_H
#define CSPOT_DF_OPERATIONS_H

enum df_operation_categories
{
    DF_CAST,
    DF_LOGIC,
    DF_ARITHMETIC,
    DF_INTERNAL,
    DF_MACHINE_LEARNING,
};
typedef enum df_operation_categories DF_OPERATION_CATEGORY;

struct df_operation {
    enum df_operation_categories category;
    unsigned int operation;
};
typedef struct df_operation DF_OPERATION;

struct df_operation_metadata {
    int host_id;
    int laminar_namespace;
    int node_id;
    unsigned long consumer_sequence;
};
typedef struct df_operation_metadata DF_OPERATION_METADATA;


enum df_cast_ops_enum
{
    DF_CAST_TO_BOOLEAN,
    DF_CAST_TO_BYTE,
    DF_CAST_TO_SHORT,
    DF_CAST_TO_INTEGER,
    DF_CAST_TO_LONG,
    DF_CAST_TO_UNSIGNED_BYTE,
    DF_CAST_TO_UNSIGNED_SHORT,
    DF_CAST_TO_UNSIGNED_INTEGER,
    DF_CAST_TO_UNSIGNED_LONG,
    DF_CAST_TO_DOUBLE,
};
typedef enum df_cast_ops_enum DF_CAST_OP;


enum df_logic_ops_enum
{
    DF_LOGIC_NOT,
    DF_LOGIC_AND,
    DF_LOGIC_OR,
    DF_LOGIC_LESS_THAN,
    DF_LOGIC_LESS_THAN_EQUALS,
    DF_LOGIC_GREATER_THAN,
    DF_LOGIC_GREATER_THAN_EQUALS,
    DF_LOGIC_EQUALS,
    DF_LOGIC_NOT_EQUALS,
};
typedef enum df_logic_ops_enum DF_LOGIC_OP;


enum df_arithmetic_ops_enum
{
    DF_ARITH_ADDITION,
    DF_ARITH_SUBTRACTION,
    DF_ARITH_MULTIPLICATION,
    DF_ARITH_DIVISION,
    DF_ARITH_MODULO,
    DF_ARITH_SQRT,
    DF_ARITH_ABS,
};
typedef enum df_arithmetic_ops_enum DF_ARITHMETIC_OP;


enum df_internal_ops_enum
{
    DF_INTERNAL_OPERAND,
    DF_INTERNAL_SELECT,
    DF_INTERNAL_FILTER,
    DF_INTERNAL_OFFSET,
};
typedef enum df_internal_ops_enum DF_INTERNAL_OP;


enum df_machine_learning_ops_enum
{
    DF_MACHINE_LEARNING_KNN,
    DF_MACHINE_LEARNING_LINREG,
};
typedef enum df_machine_learning_ops_enum DF_MACHINE_LEARNING_OP;


#ifdef __cplusplus
extern "C" {
#endif

char* operation_to_string(DF_OPERATION type);

#ifdef __cplusplus
}
#endif

#endif // CSPOT_DF_OPERATIONS_H
