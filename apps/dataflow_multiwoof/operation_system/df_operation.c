#include "df_operation.h"

#include "../logger_system/df_operation_logger.h"
#include "df_arithmetic.h"
#include "df_cast.h"
#include "df_internal.h"
#include "df_logic.h"
#include "df_machine_learning.h"

/**
 * Operation which
 * @param operation_category
 * @param operation
 * @param operands
 * @param operand_count
 * @param result_type
 * @param result
 * @return
 */
int df_operation_with_type(const DF_OPERATION operation,
                           const DF_VALUE operands[],
                           const unsigned int operand_count,
                           DF_OPERATION_METADATA* operation_metadata,
                           const DF_TYPE result_type,
                           DF_VALUE* result) {
    if (result == NULL) {
        log_reference_must_not_be_null("result reference");
        return 0;
    }
    switch (operation.category) {
        case DF_CAST:
            return df_cast_operation(operation.operation, operands, operand_count, result);
        case DF_ARITHMETIC:
            return df_arithmetic_operation_with_type(operation.operation, operands, operand_count, result_type, result);
        case DF_LOGIC:
            return df_logic_operation_with_type(operation.operation, operands, operand_count, result_type, result);
        case DF_INTERNAL:
            return df_internal_operation_with_type(
                operation.operation, operands, operand_count, operation_metadata, result_type, result);
        case DF_MACHINE_LEARNING:
            return df_machine_learning_operation_with_type(
                operation.operation, operands, operand_count, result_type, result);
        default:
            return 0;
    }
}
