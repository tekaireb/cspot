//
// Created by lukas on 20.03.2023.
//
#include <string.h>
#include "df_logic.h"

#include "../logger_system/df_operation_logger.h"

int compute_not(DF_VALUE operand, DF_VALUE *result);

int compute_and(const DF_VALUE operands[], unsigned int operand_count, DF_VALUE *result);

int compute_or(const DF_VALUE operands[], unsigned int operand_count, DF_VALUE *result);

int compute_lt(const DF_VALUE operands[], unsigned int operand_count, DF_VALUE *result);

int compute_lte(const DF_VALUE operands[], unsigned int operand_count, DF_VALUE *result);

int compute_gt(const DF_VALUE operands[], unsigned int operand_count, DF_VALUE *result);

int compute_gte(const DF_VALUE operands[], unsigned int operand_count, DF_VALUE *result);

int compute_eq(const DF_VALUE operands[], unsigned int operand_count, DF_VALUE *result);

int compute_neq(const DF_VALUE operands[], unsigned int operand_count, DF_VALUE *result);

static int equal_types(const DF_VALUE operands[], unsigned int operand_count);

/*
int df_logic_operation(const DF_LOGIC_OP logic_operation,
                       const DF_VALUE operands[],
                       const unsigned int operand_count,
                       DF_VALUE *result) {
    const DF_TYPE result_type = DF_BOOLEAN;
    if (!equal_types(operands, operand_count)) {
        return 0;
    }
    return df_logic_operation_with_type(logic_operation, operands, operand_count, result_type, result);
}
*/

int df_logic_operation_with_type(const DF_LOGIC_OP logic_operation,
                                 const DF_VALUE operands[],
                                 const unsigned int operand_count,
                                 const DF_TYPE result_type,
                                 DF_VALUE *const result) {
    if (result_type != DF_BOOLEAN) {
        log_result_type_ignored();
    }
    result->type = DF_BOOLEAN;
    if (!equal_types(operands, operand_count)) {
        return 0;
    }

    switch (logic_operation) {
        case DF_LOGIC_NOT: {
            if (operand_count != 1) {
                log_operand_count_mismatch(1, operand_count);
                return 0;
            }
            return compute_not(operands[0], result);
        }
        case DF_LOGIC_AND:
            return compute_and(operands, operand_count, result);
        case DF_LOGIC_OR:
            return compute_or(operands, operand_count, result);
        case DF_LOGIC_LESS_THAN:
            return compute_lt(operands, operand_count, result);
        case DF_LOGIC_LESS_THAN_EQUALS:
            return compute_lte(operands, operand_count, result);
        case DF_LOGIC_GREATER_THAN:
            return compute_gt(operands, operand_count, result);
        case DF_LOGIC_GREATER_THAN_EQUALS:
            return compute_gte(operands, operand_count, result);
        case DF_LOGIC_EQUALS:
            return compute_eq(operands, operand_count, result);
        case DF_LOGIC_NOT_EQUALS:
            return compute_neq(operands, operand_count, result);
        default:
            log_operation_not_existing("LOGIC", logic_operation);
            return 0;
    }
}


int compute_not(const DF_VALUE operand,
                DF_VALUE *const result) {
    const DF_TYPE operand_type = operand.type;
    switch (operand_type) {
        case DF_BOOLEAN:
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER: {
            result->value.df_int = !operand.value.df_int;
            return 1;
        }
        case DF_LONG: {
            result->value.df_int = !operand.value.df_long;
            return 1;
        }
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER: {
            result->value.df_int = !operand.value.df_unsigned_int;
            return 1;
        }
        case DF_UNSIGNED_LONG: {
            result->value.df_int = !operand.value.df_unsigned_long;
            return 1;
        }
        case DF_DOUBLE: {
            result->value.df_int = !operand.value.df_double;
            return 1;
        }
        default:
            log_unsupported_type_on_operation(operand_type, "NOT");
            return 0;
    }
}

int compute_and(const DF_VALUE *const operands,
                const unsigned int operand_count,
                DF_VALUE *const result) {
    const DF_TYPE operand_type = operands[0].type;
    switch (operand_type) {
        case DF_BOOLEAN:
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER: {
            int value = 1;
            for (unsigned int i = 0; i < operand_count; i++) {
                value = value && operands[i].value.df_int;
            }
            result->value.df_int = value;
            return 1;
        }
        case DF_LONG: {
            int value = 1;
            for (unsigned int i = 0; i < operand_count; i++) {
                value = value && operands[i].value.df_long;
            }
            result->value.df_int = value;
            return 1;
        }
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER: {
            int value = 1;
            for (unsigned int i = 0; i < operand_count; i++) {
                value = value && operands[i].value.df_unsigned_int;
            }
            result->value.df_int = value;
            return 1;
        }
        case DF_UNSIGNED_LONG: {
            int value = 1;
            for (unsigned int i = 0; i < operand_count; i++) {
                value = value && operands[i].value.df_unsigned_long;
            }
            result->value.df_int = value;
            return 1;
        }
        case DF_DOUBLE: {
            int value = 1;
            for (unsigned int i = 0; i < operand_count; i++) {
                value = value && operands[i].value.df_double;
            }
            result->value.df_int = value;
            return 1;
        }
        default:
            log_unsupported_type_on_operation(operand_type, "AND");
            return 0;
    }
}

int compute_or(const DF_VALUE *const operands,
               const unsigned int operand_count,
               DF_VALUE *const result) {
    const DF_TYPE operand_type = operands[0].type;
    switch (operand_type) {
        case DF_BOOLEAN:
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER: {
            int value = 0;
            for (unsigned int i = 0; i < operand_count; i++) {
                value = value || operands[i].value.df_int;
            }
            result->value.df_int = value;
            return 1;
        }
        case DF_LONG: {
            int value = 0;
            for (unsigned int i = 0; i < operand_count; i++) {
                value = value || operands[i].value.df_long;
            }
            result->value.df_int = value;
            return 1;
        }
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER: {
            int value = 0;
            for (unsigned int i = 0; i < operand_count; i++) {
                value = value || operands[i].value.df_unsigned_int;
            }
            result->value.df_int = value;
            return 1;
        }
        case DF_UNSIGNED_LONG: {
            int value = 0;
            for (unsigned int i = 0; i < operand_count; i++) {
                value = value || operands[i].value.df_unsigned_long;
            }
            result->value.df_int = value;
            return 1;
        }
        case DF_DOUBLE: {
            int value = 0;
            for (unsigned int i = 0; i < operand_count; i++) {
                value = value || operands[i].value.df_double;
            }
            result->value.df_int = value;
            return 1;
        }
        default:
            return 0;
    }
}

int compute_lt(const DF_VALUE *const operands,
               const unsigned int operand_count,
               DF_VALUE *const result) {
    const DF_TYPE operand_type = operands[0].type;
    switch (operand_type) {
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER: {
            int value = operands[0].value.df_int;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value < operands[i].value.df_int) {
                    value = operands[i].value.df_int;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_LONG: {
            long value = operands[0].value.df_long;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value < operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER: {
            unsigned int value = operands[0].value.df_unsigned_int;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value < operands[i].value.df_unsigned_int) {
                    value = operands[i].value.df_unsigned_int;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_UNSIGNED_LONG: {
            unsigned long value = operands[0].value.df_unsigned_long;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value < operands[i].value.df_unsigned_long) {
                    value = operands[i].value.df_unsigned_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_DOUBLE: {
            double value = operands[0].value.df_double;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value < operands[i].value.df_double) {
                    value = operands[i].value.df_double;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_DATETIME: {
            unsigned long value = operands[0].value.df_long;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value < operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_STRING: {
            size_t value = strlen(operands[0].value.df_string.value);
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                const size_t new_value = strlen(operands[i].value.df_string.value);
                if (value < new_value) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_ARRAY: {
            size_t value = operands[0].value.df_array.size;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                const size_t new_value = operands[i].value.df_array.size;
                if (value < new_value) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_LIST: {
            //TODO
        }
        default:
            return 0;
    }
}

int compute_lte(const DF_VALUE *const operands,
                const unsigned int operand_count,
                DF_VALUE *const result) {
    const DF_TYPE operand_type = operands[0].type;
    switch (operand_type) {
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER: {
            int value = operands[0].value.df_int;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value <= operands[i].value.df_int) {
                    value = operands[i].value.df_int;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_LONG: {
            long value = operands[0].value.df_long;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value <= operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER: {
            unsigned int value = operands[0].value.df_unsigned_int;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value <= operands[i].value.df_unsigned_int) {
                    value = operands[i].value.df_unsigned_int;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_UNSIGNED_LONG: {
            unsigned long value = operands[0].value.df_unsigned_long;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value <= operands[i].value.df_unsigned_long) {
                    value = operands[i].value.df_unsigned_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_DOUBLE: {
            double value = operands[0].value.df_double;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value <= operands[i].value.df_double) {
                    value = operands[i].value.df_double;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_DATETIME: {
            unsigned long value = operands[0].value.df_long;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value <= operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_STRING: {
            size_t value = strlen(operands[0].value.df_string.value);
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                const size_t new_value = strlen(operands[i].value.df_string.value);
                if (value <= new_value) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_ARRAY: {
            size_t value = operands[0].value.df_array.size;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                const size_t new_value = operands[i].value.df_array.size;
                if (value <= new_value) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_LIST: {
            //TODO
        }
        default:
            return 0;
    }
}

int compute_gt(const DF_VALUE *const operands,
               const unsigned int operand_count,
               DF_VALUE *const result) {
    const DF_TYPE operand_type = operands[0].type;
    switch (operand_type) {
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER: {
            int value = operands[0].value.df_int;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value > operands[i].value.df_int) {
                    value = operands[i].value.df_int;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_LONG: {
            long value = operands[0].value.df_long;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value > operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER: {
            unsigned int value = operands[0].value.df_unsigned_int;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value > operands[i].value.df_unsigned_int) {
                    value = operands[i].value.df_unsigned_int;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_UNSIGNED_LONG: {
            unsigned long value = operands[0].value.df_unsigned_long;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value > operands[i].value.df_unsigned_long) {
                    value = operands[i].value.df_unsigned_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_DOUBLE: {
            double value = operands[0].value.df_double;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value > operands[i].value.df_double) {
                    value = operands[i].value.df_double;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_DATETIME: {
            unsigned long value = operands[0].value.df_long;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value > operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_STRING: {
            size_t value = strlen(operands[0].value.df_string.value);
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                const size_t new_value = strlen(operands[i].value.df_string.value);
                if (value > new_value) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_ARRAY: {
            size_t value = operands[0].value.df_array.size;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                const size_t new_value = operands[i].value.df_array.size;
                if (value > new_value) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_LIST: {
            //TODO
        }
        default:
            return 0;
    }
}

int compute_gte(const DF_VALUE *const operands,
                const unsigned int operand_count,
                DF_VALUE *const result) {
    const DF_TYPE operand_type = operands[0].type;
    switch (operand_type) {
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER: {
            int value = operands[0].value.df_int;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value >= operands[i].value.df_int) {
                    value = operands[i].value.df_int;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_LONG: {
            long value = operands[0].value.df_long;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value >= operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER: {
            unsigned int value = operands[0].value.df_unsigned_int;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value >= operands[i].value.df_unsigned_int) {
                    value = operands[i].value.df_unsigned_int;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_UNSIGNED_LONG: {
            unsigned long value = operands[0].value.df_unsigned_long;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value >= operands[i].value.df_unsigned_long) {
                    value = operands[i].value.df_unsigned_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_DOUBLE: {
            double value = operands[0].value.df_double;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value >= operands[i].value.df_double) {
                    value = operands[i].value.df_double;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_DATETIME: {
            unsigned long value = operands[0].value.df_long;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value >= operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_STRING: {
            size_t value = strlen(operands[0].value.df_string.value);
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                const size_t new_value = strlen(operands[i].value.df_string.value);
                if (value >= new_value) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_ARRAY: {
            size_t value = operands[0].value.df_array.size;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                const size_t new_value = operands[i].value.df_array.size;
                if (value >= new_value) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_LIST: {
            //TODO
        }
        default:
            return 0;
    }
}

int compute_eq(const DF_VALUE *const operands,
               const unsigned int operand_count,
               DF_VALUE *const result) {
    const DF_TYPE operand_type = operands[0].type;
    switch (operand_type) {
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER: {
            int value = operands[0].value.df_int;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value == operands[i].value.df_int) {
                    value = operands[i].value.df_int;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_LONG: {
            long value = operands[0].value.df_long;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value == operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER: {
            unsigned int value = operands[0].value.df_unsigned_int;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value == operands[i].value.df_unsigned_int) {
                    value = operands[i].value.df_unsigned_int;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_UNSIGNED_LONG: {
            unsigned long value = operands[0].value.df_unsigned_long;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value == operands[i].value.df_unsigned_long) {
                    value = operands[i].value.df_unsigned_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_DOUBLE: {
            double value = operands[0].value.df_double;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value == operands[i].value.df_double) {
                    value = operands[i].value.df_double;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_DATETIME: {
            unsigned long value = operands[0].value.df_long;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value == operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_STRING: {
            size_t value = strlen(operands[0].value.df_string.value);
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                const size_t new_value = strlen(operands[i].value.df_string.value);
                if (value == new_value) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_ARRAY: {
            size_t value = operands[0].value.df_array.size;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                const size_t new_value = operands[i].value.df_array.size;
                if (value == new_value) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_LIST: {
            //TODO
        }
        default:
            return 0;
    }
}

int compute_neq(const DF_VALUE *const operands,
                const unsigned int operand_count,
                DF_VALUE *const result) {
    const DF_TYPE operand_type = operands[0].type;
    switch (operand_type) {
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER: {
            int value = operands[0].value.df_int;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value != operands[i].value.df_int) {
                    value = operands[i].value.df_int;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_LONG: {
            long value = operands[0].value.df_long;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value != operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER: {
            unsigned int value = operands[0].value.df_unsigned_int;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value != operands[i].value.df_unsigned_int) {
                    value = operands[i].value.df_unsigned_int;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_UNSIGNED_LONG: {
            unsigned long value = operands[0].value.df_unsigned_long;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value != operands[i].value.df_unsigned_long) {
                    value = operands[i].value.df_unsigned_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_DOUBLE: {
            double value = operands[0].value.df_double;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value != operands[i].value.df_double) {
                    value = operands[i].value.df_double;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_DATETIME: {
            unsigned long value = operands[0].value.df_long;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                if (value != operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_STRING: {
            size_t value = strlen(operands[0].value.df_string.value);
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                const size_t new_value = strlen(operands[i].value.df_string.value);
                if (value != new_value) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_ARRAY: {
            size_t value = operands[0].value.df_array.size;
            int is_smaller = 1;
            for (unsigned int i = 1; i < operand_count; i++) {
                const size_t new_value = operands[i].value.df_array.size;
                if (value != new_value) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                    break;
                }
            }
            result->value.df_int = is_smaller;
            return 1;
        }
        case DF_LIST: {
            //TODO
        }
        default:
            return 0;
    }
}

static int equal_types(const DF_VALUE operands[], const unsigned int operand_count) {
    const DF_TYPE initial_type = operands[0].type;
    for (unsigned int i = 1; i < operand_count; i++) {
        if (operands[i].type != initial_type) {
            log_type_mismatch(initial_type, operands[i].type);
            return 0;
        }
    }
    return 1;
}