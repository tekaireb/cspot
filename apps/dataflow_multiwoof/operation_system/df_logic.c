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
        case DF_LOGIC_LESS_THAN: {
            if (operand_count < 2) {
                log_operand_count_mismatch(2, operand_count);
                return 0;
            }
            return compute_lt(operands, operand_count, result);
        }
        case DF_LOGIC_LESS_THAN_EQUALS: {
            if (operand_count < 2) {
                log_operand_count_mismatch(2, operand_count);
                return 0;
            }
            return compute_lte(operands, operand_count, result);
        }
        case DF_LOGIC_GREATER_THAN: {
            if (operand_count < 2) {
                log_operand_count_mismatch(2, operand_count);
                return 0;
            }
            return compute_gt(operands, operand_count, result);
        }
        case DF_LOGIC_GREATER_THAN_EQUALS: {
            if (operand_count < 2) {
                log_operand_count_mismatch(2, operand_count);
                return 0;
            }
            return compute_gte(operands, operand_count, result);
        }
        case DF_LOGIC_EQUALS: {
            if (operand_count < 2) {
                log_operand_count_mismatch(2, operand_count);
                return 0;
            }
            return compute_eq(operands, operand_count, result);
        }
        case DF_LOGIC_NOT_EQUALS: {
            if (operand_count < 2) {
                log_operand_count_mismatch(2, operand_count);
                return 0;
            }
            return compute_neq(operands, operand_count, result);
        }
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
    int value = 1;
    for (unsigned int i = 0; i < operand_count; i++) {
        const DF_TYPE operand_type = operands[i].type;
        switch (operand_type) {
            case DF_BOOLEAN:
            case DF_BYTE:
            case DF_SHORT:
            case DF_INTEGER:
                value = value && operands[i].value.df_int;
                break;
            case DF_LONG:
                value = value && operands[i].value.df_long;
                break;
            case DF_UNSIGNED_BYTE:
            case DF_UNSIGNED_SHORT:
            case DF_UNSIGNED_INTEGER:
                value = value && operands[i].value.df_unsigned_int;
                break;
            case DF_UNSIGNED_LONG:
                value = value && operands[i].value.df_unsigned_long;
                break;
            case DF_DOUBLE:
                value = value && operands[i].value.df_double;
                break;
            default:
                log_unsupported_type_on_operation(operand_type, "AND");
                return 0;
        }
    }
    result->value.df_int = value;
    return 1;
}

int compute_or(const DF_VALUE *const operands,
               const unsigned int operand_count,
               DF_VALUE *const result) {
    int value = 0;
    for (unsigned int i = 0; i < operand_count; i++) {
        const DF_TYPE operand_type = operands[i].type;
        switch (operand_type) {
            case DF_BOOLEAN:
            case DF_BYTE:
            case DF_SHORT:
            case DF_INTEGER:
                value = value || operands[i].value.df_int;
                break;
            case DF_LONG:
                value = value || operands[i].value.df_long;
                break;
            case DF_UNSIGNED_BYTE:
            case DF_UNSIGNED_SHORT:
            case DF_UNSIGNED_INTEGER:
                value = value || operands[i].value.df_unsigned_int;
                break;
            case DF_UNSIGNED_LONG:
                value = value || operands[i].value.df_unsigned_long;
                break;
            case DF_DOUBLE:
                value = value || operands[i].value.df_double;
                break;
            default:
                log_unsupported_type_on_operation(operand_type, "OR");
                return 0;
        }
    }
    result->value.df_int = value;
    return 1;
}

/**
 * Currently only supports comparisons in range and precision of double
 * @param operands
 * @param operand_count
 * @param result
 * @return
 */
int compute_lt(const DF_VALUE *const operands,
               const unsigned int operand_count,
               DF_VALUE *const result) {
    double value;
    int is_smaller = 1;
    DF_TYPE operand_type = operands[0].type;
    switch (operand_type) {
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER:
            value = operands[0].value.df_int;
            break;
        case DF_LONG:
            value = operands[0].value.df_long;
            break;
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER:
            value = operands[0].value.df_unsigned_int;
            break;
        case DF_UNSIGNED_LONG:
            value = operands[0].value.df_unsigned_long;
            break;
        case DF_DOUBLE:
            value = operands[0].value.df_double;
            break;
        case DF_DATETIME:
            value = operands[0].value.df_long;
            break;
        default:
            log_unsupported_type_on_operation(operand_type, "LESS THAN");
            return 0;
    }
    for (unsigned int i = 1; i < operand_count; i++) {
        operand_type = operands[i].type;
        switch (operand_type) {
            case DF_BYTE:
            case DF_SHORT:
            case DF_INTEGER: {
                if (value < operands[i].value.df_int) {
                    value = operands[i].value.df_int;
                } else {
                    is_smaller = 0;
                }
                break;
            }
            case DF_LONG: {
                if (value < operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                }
                break;
            }
            case DF_UNSIGNED_BYTE:
            case DF_UNSIGNED_SHORT:
            case DF_UNSIGNED_INTEGER: {
                if (value < operands[i].value.df_int) {
                    value = operands[i].value.df_int;
                } else {
                    is_smaller = 0;
                }
                break;
            }
            case DF_UNSIGNED_LONG: {
                if (value < operands[i].value.df_unsigned_long) {
                    value = operands[i].value.df_unsigned_long;
                } else {
                    is_smaller = 0;
                }
                break;
            }
            case DF_DOUBLE: {
                if (value < operands[i].value.df_double) {
                    value = operands[i].value.df_double;
                } else {
                    is_smaller = 0;
                }
                break;
            }
            case DF_DATETIME: {
                if (value < operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                }
                break;
            }
            case DF_STRING: {
                //TODO
            }
            case DF_ARRAY: {
                //TODO
            }
            case DF_LIST: {
                //TODO
            }
            default:
                log_unsupported_type_on_operation(operand_type, "LESS THAN");
                return 0;

        }
        if (!is_smaller) {
            break;
        }
    }
    result->value.df_int = is_smaller;
    return 1;
}

/**
 * Currently only supports comparisons in range and precision of double
 * @param operands
 * @param operand_count
 * @param result
 * @return
 */
int compute_lte(const DF_VALUE *const operands,
               const unsigned int operand_count,
               DF_VALUE *const result) {
    double value;
    int is_smaller = 1;
    DF_TYPE operand_type = operands[0].type;
    switch (operand_type) {
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER:
            value = operands[0].value.df_int;
            break;
        case DF_LONG:
            value = operands[0].value.df_long;
            break;
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER:
            value = operands[0].value.df_unsigned_int;
            break;
        case DF_UNSIGNED_LONG:
            value = operands[0].value.df_unsigned_long;
            break;
        case DF_DOUBLE:
            value = operands[0].value.df_double;
            break;
        case DF_DATETIME:
            value = operands[0].value.df_long;
            break;
        default:
            log_unsupported_type_on_operation(operand_type, "LESS THAN EQUALS");
            return 0;
    }
    for (unsigned int i = 1; i < operand_count; i++) {
        operand_type = operands[i].type;
        switch (operand_type) {
            case DF_BYTE:
            case DF_SHORT:
            case DF_INTEGER: {
                if (value <= operands[i].value.df_int) {
                    value = operands[i].value.df_int;
                } else {
                    is_smaller = 0;
                }
                break;
            }
            case DF_LONG: {
                if (value <= operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                }
                break;
            }
            case DF_UNSIGNED_BYTE:
            case DF_UNSIGNED_SHORT:
            case DF_UNSIGNED_INTEGER: {
                if (value <= operands[i].value.df_int) {
                    value = operands[i].value.df_int;
                } else {
                    is_smaller = 0;
                }
                break;
            }
            case DF_UNSIGNED_LONG: {
                if (value <= operands[i].value.df_unsigned_long) {
                    value = operands[i].value.df_unsigned_long;
                } else {
                    is_smaller = 0;
                }
                break;
            }
            case DF_DOUBLE: {
                if (value <= operands[i].value.df_double) {
                    value = operands[i].value.df_double;
                } else {
                    is_smaller = 0;
                }
                break;
            }
            case DF_DATETIME: {
                if (value <= operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_smaller = 0;
                }
                break;
            }
            case DF_STRING: {
                //TODO
            }
            case DF_ARRAY: {
                //TODO
            }
            case DF_LIST: {
                //TODO
            }
            default:
                log_unsupported_type_on_operation(operand_type, "LESS THAN EQUALS");
                return 0;

        }
        if (!is_smaller) {
            break;
        }
    }
    result->value.df_int = is_smaller;
    return 1;
}

/**
 * Currently only supports comparisons in range and precision of double
 * @param operands
 * @param operand_count
 * @param result
 * @return
 */
int compute_gt(const DF_VALUE *const operands,
               const unsigned int operand_count,
               DF_VALUE *const result) {
    double value;
    int is_bigger = 1;
    DF_TYPE operand_type = operands[0].type;
    switch (operand_type) {
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER:
            value = operands[0].value.df_int;
            break;
        case DF_LONG:
            value = operands[0].value.df_long;
            break;
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER:
            value = operands[0].value.df_unsigned_int;
            break;
        case DF_UNSIGNED_LONG:
            value = operands[0].value.df_unsigned_long;
            break;
        case DF_DOUBLE:
            value = operands[0].value.df_double;
            break;
        case DF_DATETIME:
            value = operands[0].value.df_long;
            break;
        default:
            log_unsupported_type_on_operation(operand_type, "GREATER THAN");
            return 0;
    }
    for (unsigned int i = 1; i < operand_count; i++) {
        operand_type = operands[i].type;
        switch (operand_type) {
            case DF_BYTE:
            case DF_SHORT:
            case DF_INTEGER: {
                if (value > operands[i].value.df_int) {
                    value = operands[i].value.df_int;
                } else {
                    is_bigger = 0;
                }
                break;
            }
            case DF_LONG: {
                if (value > operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_bigger = 0;
                }
                break;
            }
            case DF_UNSIGNED_BYTE:
            case DF_UNSIGNED_SHORT:
            case DF_UNSIGNED_INTEGER: {
                if (value > operands[i].value.df_int) {
                    value = operands[i].value.df_int;
                } else {
                    is_bigger = 0;
                }
                break;
            }
            case DF_UNSIGNED_LONG: {
                if (value > operands[i].value.df_unsigned_long) {
                    value = operands[i].value.df_unsigned_long;
                } else {
                    is_bigger = 0;
                }
                break;
            }
            case DF_DOUBLE: {
                if (value > operands[i].value.df_double) {
                    value = operands[i].value.df_double;
                } else {
                    is_bigger = 0;
                }
                break;
            }
            case DF_DATETIME: {
                if (value > operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_bigger = 0;
                }
                break;
            }
            case DF_STRING: {
                //TODO
            }
            case DF_ARRAY: {
                //TODO
            }
            case DF_LIST: {
                //TODO
            }
            default:
                log_unsupported_type_on_operation(operand_type, "GREATER THAN");
                return 0;

        }
        if (!is_bigger) {
            break;
        }
    }
    result->value.df_int = is_bigger;
    return 1;
}

/**
 * Currently only supports comparisons in range and precision of double
 * @param operands
 * @param operand_count
 * @param result
 * @return
 */
int compute_gte(const DF_VALUE *const operands,
               const unsigned int operand_count,
               DF_VALUE *const result) {
    double value;
    int is_bigger = 1;
    DF_TYPE operand_type = operands[0].type;
    switch (operand_type) {
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER:
            value = operands[0].value.df_int;
            break;
        case DF_LONG:
            value = operands[0].value.df_long;
            break;
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER:
            value = operands[0].value.df_unsigned_int;
            break;
        case DF_UNSIGNED_LONG:
            value = operands[0].value.df_unsigned_long;
            break;
        case DF_DOUBLE:
            value = operands[0].value.df_double;
            break;
        case DF_DATETIME:
            value = operands[0].value.df_long;
            break;
        default:
            log_unsupported_type_on_operation(operand_type, "GRATER THAN EQUALS");
            return 0;
    }
    for (unsigned int i = 1; i < operand_count; i++) {
        operand_type = operands[i].type;
        switch (operand_type) {
            case DF_BYTE:
            case DF_SHORT:
            case DF_INTEGER: {
                if (value >= operands[i].value.df_int) {
                    value = operands[i].value.df_int;
                } else {
                    is_bigger = 0;
                }
                break;
            }
            case DF_LONG: {
                if (value >= operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_bigger = 0;
                }
                break;
            }
            case DF_UNSIGNED_BYTE:
            case DF_UNSIGNED_SHORT:
            case DF_UNSIGNED_INTEGER: {
                if (value >= operands[i].value.df_int) {
                    value = operands[i].value.df_int;
                } else {
                    is_bigger = 0;
                }
                break;
            }
            case DF_UNSIGNED_LONG: {
                if (value >= operands[i].value.df_unsigned_long) {
                    value = operands[i].value.df_unsigned_long;
                } else {
                    is_bigger = 0;
                }
                break;
            }
            case DF_DOUBLE: {
                if (value >= operands[i].value.df_double) {
                    value = operands[i].value.df_double;
                } else {
                    is_bigger = 0;
                }
                break;
            }
            case DF_DATETIME: {
                if (value >= operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_bigger = 0;
                }
                break;
            }
            case DF_STRING: {
                //TODO
            }
            case DF_ARRAY: {
                //TODO
            }
            case DF_LIST: {
                //TODO
            }
            default:
                log_unsupported_type_on_operation(operand_type, "GREATER THAN EQUALS");
                return 0;

        }
        if (!is_bigger) {
            break;
        }
    }
    result->value.df_int = is_bigger;
    return 1;
}

/**
 * Currently only supports comparisons in range and precision of double
 * @param operands
 * @param operand_count
 * @param result
 * @return
 */
int compute_eq(const DF_VALUE *const operands,
               const unsigned int operand_count,
               DF_VALUE *const result) {
    double value;
    int is_equal = 1;
    DF_TYPE operand_type = operands[0].type;
    switch (operand_type) {
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER:
            value = operands[0].value.df_int;
            break;
        case DF_LONG:
            value = operands[0].value.df_long;
            break;
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER:
            value = operands[0].value.df_unsigned_int;
            break;
        case DF_UNSIGNED_LONG:
            value = operands[0].value.df_unsigned_long;
            break;
        case DF_DOUBLE:
            value = operands[0].value.df_double;
            break;
        case DF_DATETIME:
            value = operands[0].value.df_long;
            break;
        default:
            log_unsupported_type_on_operation(operand_type, "EQUALS");
            return 0;
    }
    for (unsigned int i = 1; i < operand_count; i++) {
        operand_type = operands[i].type;
        switch (operand_type) {
            case DF_BYTE:
            case DF_SHORT:
            case DF_INTEGER: {
                if (value == operands[i].value.df_int) {
                    value = operands[i].value.df_int;
                } else {
                    is_equal = 0;
                }
                break;
            }
            case DF_LONG: {
                if (value == operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_equal = 0;
                }
                break;
            }
            case DF_UNSIGNED_BYTE:
            case DF_UNSIGNED_SHORT:
            case DF_UNSIGNED_INTEGER: {
                if (value == operands[i].value.df_int) {
                    value = operands[i].value.df_int;
                } else {
                    is_equal = 0;
                }
                break;
            }
            case DF_UNSIGNED_LONG: {
                if (value == operands[i].value.df_unsigned_long) {
                    value = operands[i].value.df_unsigned_long;
                } else {
                    is_equal = 0;
                }
                break;
            }
            case DF_DOUBLE: {
                if (value == operands[i].value.df_double) {
                    value = operands[i].value.df_double;
                } else {
                    is_equal = 0;
                }
                break;
            }
            case DF_DATETIME: {
                if (value == operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_equal = 0;
                }
                break;
            }
            case DF_STRING: {
                //TODO
            }
            case DF_ARRAY: {
                //TODO
            }
            case DF_LIST: {
                //TODO
            }
            default:
                log_unsupported_type_on_operation(operand_type, "EQUALS");
                return 0;

        }
        if (!is_equal) {
            break;
        }
    }
    result->value.df_int = is_equal;
    return 1;
}

/**
 * Currently only supports comparisons in range and precision of double
 * @param operands
 * @param operand_count
 * @param result
 * @return
 */
int compute_neq(const DF_VALUE *const operands,
               const unsigned int operand_count,
               DF_VALUE *const result) {
    double value;
    int is_not_equal = 1;
    DF_TYPE operand_type = operands[0].type;
    switch (operand_type) {
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER:
            value = operands[0].value.df_int;
            break;
        case DF_LONG:
            value = operands[0].value.df_long;
            break;
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER:
            value = operands[0].value.df_unsigned_int;
            break;
        case DF_UNSIGNED_LONG:
            value = operands[0].value.df_unsigned_long;
            break;
        case DF_DOUBLE:
            value = operands[0].value.df_double;
            break;
        case DF_DATETIME:
            value = operands[0].value.df_long;
            break;
        default:
            log_unsupported_type_on_operation(operand_type, "EQUALS");
            return 0;
    }
    for (unsigned int i = 1; i < operand_count; i++) {
        operand_type = operands[i].type;
        switch (operand_type) {
            case DF_BYTE:
            case DF_SHORT:
            case DF_INTEGER: {
                if (value != operands[i].value.df_int) {
                    value = operands[i].value.df_int;
                } else {
                    is_not_equal = 0;
                }
                break;
            }
            case DF_LONG: {
                if (value != operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_not_equal = 0;
                }
                break;
            }
            case DF_UNSIGNED_BYTE:
            case DF_UNSIGNED_SHORT:
            case DF_UNSIGNED_INTEGER: {
                if (value != operands[i].value.df_int) {
                    value = operands[i].value.df_int;
                } else {
                    is_not_equal = 0;
                }
                break;
            }
            case DF_UNSIGNED_LONG: {
                if (value != operands[i].value.df_unsigned_long) {
                    value = operands[i].value.df_unsigned_long;
                } else {
                    is_not_equal = 0;
                }
                break;
            }
            case DF_DOUBLE: {
                if (value != operands[i].value.df_double) {
                    value = operands[i].value.df_double;
                } else {
                    is_not_equal = 0;
                }
                break;
            }
            case DF_DATETIME: {
                if (value != operands[i].value.df_long) {
                    value = operands[i].value.df_long;
                } else {
                    is_not_equal = 0;
                }
                break;
            }
            case DF_STRING: {
                //TODO
            }
            case DF_ARRAY: {
                //TODO
            }
            case DF_LIST: {
                //TODO
            }
            default:
                log_unsupported_type_on_operation(operand_type, "NOT EQUALS");
                return 0;

        }
        if (!is_not_equal) {
            break;
        }
    }
    result->value.df_int = is_not_equal;
    return 1;
}