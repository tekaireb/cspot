//
// Created by lukas on 20.03.2023.
//

#ifndef CSPOT_DF_ARITHMETIC_H
#define CSPOT_DF_ARITHMETIC_H

#include "../type_system/dftype.h"

enum df_arithmetics_enum
{
    DF_ARITH_ADDITION,
    DF_ARITH_SUBTRACTION,
    DF_ARITH_MULTIPLICATION,
    DF_ARITH_DIVISION,
    DF_ARITH_SQRT,
    DF_ARITH_ABS,
};
typedef enum df_arithmetics_enum DF_ARITHMETIC;

int df_arithmetic_operation(DF_ARITHMETIC arithmetic_operation,
                            const DF_VALUE values[],
                            unsigned int value_count,
                            DF_VALUE* return_value);

int df_arithmetic_operation_with_type(DF_ARITHMETIC arithmetic_operation,
                                      DF_TYPE operation_type,
                                      const DF_VALUE values[],
                                      unsigned int value_count,
                                      DF_VALUE* return_value);

#endif // CSPOT_DF_ARITHMETIC_H
