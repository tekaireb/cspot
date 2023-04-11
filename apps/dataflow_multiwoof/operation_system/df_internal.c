//
// Created by lukas on 20.03.2023.
//

#include "df_internal.h"

#include "../logger_system/df_operation_logger.h"

#include <stdlib.h>

int compute_operand(DF_VALUE operand, DF_VALUE* result);

int compute_select(const DF_VALUE operands[], unsigned int operand_count, DF_TYPE result_type, DF_VALUE* result);

int compute_filter(const DF_VALUE operands[], unsigned int operand_count, DF_TYPE result_type, DF_VALUE* result);

int compute_offset(const DF_VALUE operands[],
                   unsigned int operand_count,
                   DF_OPERATION_METADATA* operation_metadata,
                   DF_TYPE result_type,
                   DF_VALUE* result);

int df_internal_operation_with_type(const DF_INTERNAL_OP internal_operation,
                                    const DF_VALUE operands[],
                                    const unsigned int operand_count,
                                    DF_OPERATION_METADATA* operation_metadata,
                                    const DF_TYPE result_type,
                                    DF_VALUE* result) {
    switch (internal_operation) {
        case DF_INTERNAL_OPERAND: {
            if (operand_count != 1) {
                log_operand_count_mismatch(1, operand_count);
                return 0;
            }
            return compute_operand(operands[0], result);
        }
        case DF_INTERNAL_SELECT:
            return compute_select(operands, operand_count, result_type, result);
        case DF_INTERNAL_FILTER:
            return compute_filter(operands, operand_count, result_type, result);
        case DF_INTERNAL_OFFSET:
            return compute_offset(operands, operand_count, operation_metadata, result_type, result);
        default:
            log_operation_not_existing("INTERNAL", internal_operation);
            return 0;
    }
}


int compute_operand(const DF_VALUE operand, DF_VALUE* result) {
    return deep_copy(&operand, result);
}

int compute_select(const DF_VALUE operands[],
                   const unsigned int operand_count,
                   const DF_TYPE result_type,
                   DF_VALUE* result) {
    const DF_TYPE select_type = operands[0].type;
    unsigned long selector;
    switch (select_type) {
        case DF_BOOLEAN:
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER:
            if (operands[0].value.df_int < 0) {
                return 0;
            }
            selector = operands[0].value.df_int;
            break;
        case DF_LONG:
            if (operands[0].value.df_long < 0) {
                return 0;
            }
            selector = operands[0].value.df_long;
            break;
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER:
            selector = operands[0].value.df_unsigned_int;
            break;
        case DF_UNSIGNED_LONG:
            selector = operands[0].value.df_unsigned_long;
            break;
        case DF_DOUBLE: {
            int temp_selector = (int)operands[0].value.df_double;
            if (temp_selector < 0) {
                return 0;
            }
            selector = temp_selector;
            break;
        }
        default:
            log_unsupported_type_on_operation(select_type, "SELECT");
            return 0;
    }
    if (selector + 1 + 1 > operand_count) {
        log_operand_count_mismatch(selector + 1, operand_count);
        return 0;
    }
    const DF_VALUE selected_value = operands[selector + 1];
    const DF_TYPE selected_type = selected_value.type;
    if (result_type != select_type) {
        log_type_mismatch(result_type, selected_type);
        return 0;
    }
    return deep_copy(&selected_value, result);
}

int compute_filter(const DF_VALUE operands[],
                   const unsigned int operand_count,
                   const DF_TYPE result_type,
                   DF_VALUE* result) {
    return deep_copy(&operands[1], result);
}

int compute_offset(const DF_VALUE operands[],
                   const unsigned int operand_count,
                   DF_OPERATION_METADATA* operation_metadata,
                   const DF_TYPE result_type,
                   DF_VALUE* result) {
    deep_copy(&operands[1], result);
    // TODO
    operation_metadata->consumer_sequence =
        operation_metadata->consumer_sequence + (unsigned long)operands[0].value.df_double;
    return 1;
}