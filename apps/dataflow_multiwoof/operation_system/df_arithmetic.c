//
// Created by lukas on 20.03.2023.
//
#include "df_arithmetic.h"

#include "../logger_system/df_logger.h"

#include <math.h>

int compatible_types(const DF_VALUE values[], const unsigned int value_count) {
    int compatible_types = 1;
    for (unsigned int i = 0; i < value_count; i++) {
        if (!is_number(&values[i])) {
            compatible_types = 0;
        }
    }
    return compatible_types;
}

DF_TYPE identify_type(const DF_VALUE values[], const unsigned int value_count) {
    DF_TYPE first_value_type = values[0].type;
    int equal_types = 1;
    for (unsigned int i = 1; i < value_count; i++) {
        if (first_value_type == values[i].type) {
            equal_types = 0;
        }
    }
    if (equal_types) {
        return first_value_type;
    }
}

int df_arithmetic_operation(const DF_ARITHMETIC arithmetic_operation,
                            const DF_VALUE values[],
                            const unsigned int value_count,
                            DF_VALUE* return_value) {
    if (!compatible_types(values, value_count)) {
        return -1;
    }
    DF_TYPE type_to_use = identify_type(values, value_count);

    return df_arithmetic_operation_with_type(arithmetic_operation, type_to_use, values, value_count, return_value);
}

int df_arithmetic_operation_with_type(const DF_ARITHMETIC arithmetic_operation,
                                      const DF_TYPE operation_type,
                                      const DF_VALUE values[],
                                      const unsigned int value_count,
                                      DF_VALUE* return_value) {
    double result;
    switch (arithmetic_operation) {
    case DF_ARITH_ADDITION:
        result = 0;
        for (unsigned int i = 0; i < value_count; i++) {
            result += values[i].value.df_double;
        }
        break;
    case DF_ARITH_SUBTRACTION:
        result = 0;
        for (unsigned int i = 0; i < value_count; i++) {
            result -= values[i].value.df_double;
        }
        break;
    case DF_ARITH_MULTIPLICATION:
        result = 1;
        for (unsigned int i = 0; i < value_count; i++) {
            result *= values[i].value.df_double;
        }
        break;
    case DF_ARITH_DIVISION:
        result = values[0].value.df_double;
        for (unsigned int i = 1; i < value_count; i++) {
            result /= values[i].value.df_double;
        }
        break;
    case DF_ARITH_SQRT:
        result = sqrt(values[0].value.df_double);
        break;
    default:
        return 1;
    }
    return_value->type = DF_DOUBLE;
    return_value->value.df_double = result;
    return 0;
}