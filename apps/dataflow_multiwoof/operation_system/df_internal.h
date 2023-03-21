//
// Created by lukas on 20.03.2023.
//

#ifndef CSPOT_DF_INTERNAL_H
#define CSPOT_DF_INTERNAL_H

#include "../type_system/dftype.h"

enum df_internals_enum
{
    DF_INTERNAL_OPERAND,
    DF_INTERNAL_SELECT,
    DF_INTERNAL_FILTER,
    DF_INTERNAL_OFFSET,
};
typedef enum df_internals_enum DF_INTERNAL;

int df_internal_operation(DF_INTERNAL internal_operation,
                          const DF_VALUE values[],
                          unsigned int value_count,
                          DF_VALUE* return_value);

int df_internal_operation_with_type(DF_INTERNAL internal_operation,
                                    DF_TYPE operation_type,
                                    const DF_VALUE values[],
                                    unsigned int value_count,
                                    DF_VALUE* return_value);

#endif // CSPOT_DF_INTERNAL_H
