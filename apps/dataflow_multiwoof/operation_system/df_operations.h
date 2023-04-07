//
// Created by Lukas Brand on 29.03.23.
//

#ifndef CSPOT_DF_OPERATIONS_H
#define CSPOT_DF_OPERATIONS_H

enum df_operation_categories
{
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


enum df_arithmetics_enum
{
    DF_ARITH_ADDITION,
    DF_ARITH_SUBTRACTION,
    DF_ARITH_MULTIPLICATION,
    DF_ARITH_DIVISION,
    DF_ARITH_MODULO,
    DF_ARITH_SQRT,
    DF_ARITH_ABS,
};
typedef enum df_arithmetics_enum DF_ARITHMETIC_OP;


enum df_internals_enum
{
    DF_INTERNAL_OPERAND,
    DF_INTERNAL_SELECT,
    DF_INTERNAL_FILTER,
    DF_INTERNAL_OFFSET,
};
typedef enum df_internals_enum DF_INTERNAL_OP;


enum df_machine_learnings_enum
{
    DF_MACHINE_LEARNING_KNN,
    DF_MACHINE_LEARNING_LINREG,
};
typedef enum df_machine_learnings_enum DF_MACHINE_LEARNING_OP;

#ifdef __cplusplus
extern "C" {
#endif

DF_OPERATION default_df_operation();

char* operation_to_string(DF_OPERATION type);

#ifdef __cplusplus
}
#endif

#endif // CSPOT_DF_OPERATIONS_H
