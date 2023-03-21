//
// Created by lukas on 20.03.2023.
//

#ifndef CSPOT_DF_LOGIC_H
#define CSPOT_DF_LOGIC_H

#include "../type_system/dftype.h"

enum df_logics_enum
{
    DF_LOGIC_NOT,
    DF_LOGIC_AND,
    DF_LOGIC_OR,
    DF_LOGIC_XOR,
    DF_LOGIC_LT,
    DF_LOGIC_LTE,
    DF_LOGIC_GT,
    DF_LOGIC_GTE,
    DF_LOGIC_EQ,


};
typedef enum df_logics_enum DF_LOGIC;

int df_logic_operation(DF_LOGIC logic_operation,
                       const DF_VALUE values[],
                       unsigned int value_count,
                       DF_VALUE* return_value);

int df_logic_operation_with_type(DF_LOGIC logic_operation,
                                 DF_TYPE operation_type,
                                 const DF_VALUE values[],
                                 unsigned int value_count,
                                 DF_VALUE* return_value);

#endif // CSPOT_DF_LOGIC_H
