//
// Created by lukas on 20.03.2023.
//
#include "df_arithmetic.h"

#include "../logger_system/df_operation_logger.h"
#include "../type_system/df_type.h"
#include <math.h>
#include <stdlib.h>

int compute_add(const DF_VALUE operands[], unsigned int operand_count, DF_TYPE result_type, DF_VALUE *result);

int compute_subtract(const DF_VALUE operands[], unsigned int operand_count, DF_TYPE result_type, DF_VALUE *result);

int compute_multiplication(const DF_VALUE operands[],
                           unsigned int operand_count,
                           DF_TYPE result_type,
                           DF_VALUE *result);

int compute_division(const DF_VALUE operands[], unsigned int operand_count, DF_TYPE result_type, DF_VALUE *result);

int compute_modulo(const DF_VALUE operands[], unsigned int operand_count, DF_TYPE result_type, DF_VALUE *result);

int compute_sqrt(DF_VALUE operand, DF_TYPE result_type, DF_VALUE *result);

int compute_abs(DF_VALUE operand, DF_TYPE result_type, DF_VALUE *result);


static int compatible_types(const DF_VALUE operands[], unsigned int operand_count, DF_TYPE result_type);

static int equal_types(const DF_VALUE operands[], unsigned int operand_count);

/*
int df_arithmetic_operation(const DF_ARITHMETIC_OP arithmetic_operation,
                            const DF_VALUE operands[],
                            const unsigned int operand_count,
                            DF_VALUE *result) {
    const DF_TYPE result_type = operands[0].type;
    if (!compatible_types(operands, operand_count, result_type)) {
        return 0;
    }
    if (!equal_types(operands, operand_count)) {
        return 0;
    }
    return df_arithmetic_operation_with_type(arithmetic_operation, operands, operand_count, result_type, result);
}
*/


int df_arithmetic_operation_with_type(const DF_ARITHMETIC_OP arithmetic_operation,
                                      const DF_VALUE operands[],
                                      const unsigned int operand_count,
                                      const DF_TYPE result_type,
                                      DF_VALUE *result) {
    if (operand_count < 1) {
        return 0;
    }
    if (!compatible_types(operands, operand_count, result_type)) {
        return 0;
    }
    if (!equal_types(operands, operand_count)) {
        return 0;
    }
    result->type = result_type;
    switch (arithmetic_operation) {
        case DF_ARITH_ADDITION:
            return compute_add(operands, operand_count, result_type, result);
        case DF_ARITH_SUBTRACTION:
            return compute_subtract(operands, operand_count, result_type, result);
        case DF_ARITH_MULTIPLICATION:
            return compute_multiplication(operands, operand_count, result_type, result);
        case DF_ARITH_DIVISION:
            return compute_division(operands, operand_count, result_type, result);
        case DF_ARITH_MODULO:
            return compute_modulo(operands, operand_count, result_type, result);
        case DF_ARITH_SQRT: {
            if (operand_count != 1) {
                log_operand_count_mismatch(1, operand_count);
                return 0;
            }
            return compute_sqrt(operands[0], result_type, result);
        }
        case DF_ARITH_ABS:
            if (operand_count != 1) {
                log_operand_count_mismatch(1, operand_count);
                return 0;
            }
            return compute_abs(operands[0], result_type, result);
        default:
            log_operation_not_existing("ARITHMETIC", arithmetic_operation);
            return 0;
    }
}


int compute_add(const DF_VALUE operands[], unsigned int operand_count, DF_TYPE result_type, DF_VALUE *const result) {
    switch (result_type) {
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER: {
            int value = 0;
            for (unsigned int i = 0; i < operand_count; i++) {
                value += operands[i].value.df_int;
            }
            result->value.df_int = value;
            return 1;
        }
        case DF_LONG: {
            long value = 0;
            for (unsigned int i = 0; i < operand_count; i++) {
                value += operands[i].value.df_long;
            }
            result->value.df_long = value;
            return 1;
        }
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER: {
            unsigned int value = 0;
            for (unsigned int i = 0; i < operand_count; i++) {
                value += operands[i].value.df_unsigned_int;
            }
            result->value.df_unsigned_int = value;
            return 1;
        }
        case DF_UNSIGNED_LONG: {
            unsigned long value = 0;
            for (unsigned int i = 0; i < operand_count; i++) {
                value += operands[i].value.df_unsigned_long;
            }
            result->value.df_unsigned_long = value;
            return 1;
        }
        case DF_DOUBLE: {
            double value = 0;
            for (unsigned int i = 0; i < operand_count; i++) {
                value += operands[i].value.df_double;
            }
            result->value.df_double = value;
            return 1;
        }
        default:
            return 0;
    }
}


int compute_subtract(const DF_VALUE operands[],
                     unsigned int operand_count,
                     DF_TYPE result_type,
                     DF_VALUE *const result) {
    switch (result_type) {
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER: {
            int value = operands[0].value.df_int;
            for (unsigned int i = 1; i < operand_count; i++) {
                value -= operands[i].value.df_int;
            }
            result->value.df_int = value;
            return 1;
        }
        case DF_LONG: {
            long value = operands[0].value.df_long;
            for (unsigned int i = 1; i < operand_count; i++) {
                value -= operands[i].value.df_long;
            }
            result->value.df_long = value;
            return 1;
        }
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER: {
            unsigned int value = operands[0].value.df_unsigned_int;
            for (unsigned int i = 1; i < operand_count; i++) {
                value -= operands[i].value.df_unsigned_int;
            }
            result->value.df_unsigned_int = value;
            return 1;
        }
        case DF_UNSIGNED_LONG: {
            unsigned long value = operands[0].value.df_unsigned_long;
            for (unsigned int i = 1; i < operand_count; i++) {
                value -= operands[i].value.df_unsigned_long;
            }
            result->value.df_unsigned_long = value;
            return 1;
        }
        case DF_DOUBLE: {
            double value = operands[0].value.df_double;
            for (unsigned int i = 1; i < operand_count; i++) {
                value -= operands[i].value.df_double;
            }
            result->value.df_double = value;
            return 1;
        }
        default:
            return 0;
    }
}

int compute_multiplication(const DF_VALUE operands[],
                           unsigned int operand_count,
                           DF_TYPE result_type,
                           DF_VALUE *const result) {
    switch (result_type) {
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER: {
            int value = 1;
            for (unsigned int i = 0; i < operand_count; i++) {
                value *= operands[i].value.df_int;
            }
            result->value.df_int = value;
            return 1;
        }
        case DF_LONG: {
            long value = 1;
            for (unsigned int i = 0; i < operand_count; i++) {
                value *= operands[i].value.df_long;
            }
            result->value.df_long = value;
            return 1;
        }
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER: {
            unsigned int value = 1;
            for (unsigned int i = 0; i < operand_count; i++) {
                value *= operands[i].value.df_unsigned_int;
            }
            result->value.df_unsigned_int = value;
            return 1;
        }
        case DF_UNSIGNED_LONG: {
            unsigned long value = 1;
            for (unsigned int i = 0; i < operand_count; i++) {
                value *= operands[i].value.df_unsigned_long;
            }
            result->value.df_unsigned_long = value;
            return 1;
        }
        case DF_DOUBLE: {
            double value = 1;
            for (unsigned int i = 0; i < operand_count; i++) {
                value *= operands[i].value.df_double;
            }
            result->value.df_double = value;
            return 1;
        }
        default:
            return 0;
    }
}

int compute_division(const DF_VALUE operands[],
                     unsigned int operand_count,
                     DF_TYPE result_type,
                     DF_VALUE *const result) {
    switch (result_type) {
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER: {
            int value = operands[0].value.df_int;
            for (unsigned int i = 1; i < operand_count; i++) {
                value /= operands[i].value.df_int;
            }
            result->value.df_int = value;
            return 1;
        }
        case DF_LONG: {
            long value = operands[0].value.df_long;
            for (unsigned int i = 1; i < operand_count; i++) {
                value /= operands[i].value.df_long;
            }
            result->value.df_long = value;
            return 1;
        }
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER: {
            unsigned int value = operands[0].value.df_unsigned_int;
            for (unsigned int i = 1; i < operand_count; i++) {
                value /= operands[i].value.df_unsigned_int;
            }
            result->value.df_unsigned_int = value;
            return 1;
        }
        case DF_UNSIGNED_LONG: {
            unsigned long value = operands[0].value.df_unsigned_long;
            for (unsigned int i = 1; i < operand_count; i++) {
                value /= operands[i].value.df_unsigned_long;
            }
            result->value.df_unsigned_long = value;
            return 1;
        }
        case DF_DOUBLE: {
            double value = operands[0].value.df_double;
            for (unsigned int i = 1; i < operand_count; i++) {
                value /= operands[i].value.df_double;
            }
            result->value.df_double = value;
            return 1;
        }
        default:
            return 0;
    }
}

int compute_modulo(const DF_VALUE operands[],
                   unsigned int operand_count,
                   DF_TYPE result_type,
                   DF_VALUE *const result) {
    switch (result_type) {
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER: {
            int value = operands[0].value.df_int;
            for (unsigned int i = 1; i < operand_count; i++) {
                value %= operands[i].value.df_int;
            }
            result->value.df_int = value;
            return 1;
        }
        case DF_LONG: {
            long value = operands[0].value.df_long;
            for (unsigned int i = 1; i < operand_count; i++) {
                value %= operands[i].value.df_long;
            }
            result->value.df_long = value;
            return 1;
        }
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER: {
            unsigned int value = operands[0].value.df_unsigned_int;
            for (unsigned int i = 1; i < operand_count; i++) {
                value %= operands[i].value.df_unsigned_int;
            }
            result->value.df_unsigned_int = value;
            return 1;
        }
        case DF_UNSIGNED_LONG: {
            unsigned long value = operands[0].value.df_unsigned_long;
            for (unsigned int i = 1; i < operand_count; i++) {
                value %= operands[i].value.df_unsigned_long;
            }
            result->value.df_unsigned_long = value;
            return 1;
        }
        case DF_DOUBLE: {
            double value = operands[0].value.df_double;
            for (unsigned int i = 1; i < operand_count; i++) {
                value = fmod(value, operands[i].value.df_double);
            }
            result->value.df_double = value;
            return 1;
        }
        default:
            return 0;
    }
}

int compute_sqrt(const DF_VALUE operand, const DF_TYPE result_type, DF_VALUE *const result) {
    switch (result_type) {
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER: {
            result->value.df_int = (int) sqrt(operand.value.df_int);
            return 1;
        }
        case DF_LONG: {
            result->value.df_long = (long) sqrtl(
                    operand.value.df_long);  // NOLINT(cppcoreguidelines-narrowing-conversions)
            return 1;
        }
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER: {
            result->value.df_unsigned_int = (int) sqrt(operand.value.df_unsigned_int);
            return 1;
        }
        case DF_UNSIGNED_LONG: {
            result->value.df_unsigned_long = (long) sqrtl(
                    operand.value.df_unsigned_long); // NOLINT(cppcoreguidelines-narrowing-conversions)
            return 1;
        }
        case DF_DOUBLE: {
            result->value.df_double = sqrt(operand.value.df_double);
            return 1;
        }
        default:
            return 0;
    }
}

int compute_abs(const DF_VALUE operand, const DF_TYPE result_type, DF_VALUE *const result) {
    switch (result_type) {
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER: {
            result->value.df_int = abs(operand.value.df_int);
            return 1;
        }
        case DF_LONG: {
            result->value.df_long = labs(operand.value.df_long);
            return 1;
        }
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER: {
            result->value.df_unsigned_int = operand.value.df_unsigned_int;
            return 1;
        }
        case DF_UNSIGNED_LONG: {
            result->value.df_unsigned_long = operand.value.df_unsigned_long;
            return 1;
        }
        case DF_DOUBLE: {
            result->value.df_double = fabs(operand.value.df_double);
            return 1;
        }
        default:
            return 0;
    }
}


static int compatible_types(const DF_VALUE operands[], const unsigned int operand_count, const DF_TYPE result_type) {
    for (unsigned int i = 0; i < operand_count; i++) {
        const DF_TYPE current_type = operands[i].type;
        if (!is_number(&operands[i])) {
            log_not_a_number(current_type);
            return 0;
        }
        if (current_type != result_type) {
            log_type_mismatch(result_type, current_type);
            return 0;
        }
    }
    return 1;
}

static int equal_types(const DF_VALUE operands[], const unsigned int operand_count) {
    const DF_TYPE initial_type = operands[0].type;
    for (unsigned int i = 1; i < operand_count; i++) {
        if (operands[i].type != initial_type) {
            return 0;
        }
    }
    return 1;
}