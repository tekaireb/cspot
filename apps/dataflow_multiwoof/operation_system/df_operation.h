//
// Created by lukas on 09.01.2023.
//
#ifndef CSPOT_DF_OPERATION_H
#define CSPOT_DF_OPERATION_H

#include "../type_system/dftype.h"

enum df_command_types
{
    LOGIC,
    ARITHMETIC,
    INTERNAL,
    MACHINE_LEARNING,
};
typedef enum df_command_types DF_OPERATION_TYPE;

int df_operation(DF_OPERATION_TYPE operation,
                 unsigned int command,
                 const DF_VALUE values[],
                 unsigned int value_count,
                 DF_VALUE* return_value);

int df_operation_with_type(DF_OPERATION_TYPE operation,
                           unsigned int command,
                           DF_TYPE operation_type,
                           const DF_VALUE values[],
                           unsigned int value_count,
                           DF_VALUE* return_value);

#endif // CSPOT_DF_OPERATION_H
