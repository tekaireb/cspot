#include "df_operation.h"

#include "df_arithmetic.h"
#include "df_internal.h"
#include "df_logic.h"
#include "df_machine_learning.h"

int df_operation(const DF_OPERATION operation,
                 const DF_VALUE operands[],
                 const unsigned int operand_count,
                 DF_VALUE *result) {
    // TODO
    switch (operation.category) {
        case DF_ARITHMETIC:
            return df_arithmetic_operation(operation.operation, operands, operand_count, result);
        case DF_LOGIC:
            return df_logic_operation(operation.operation, operands, operand_count, result);
        case DF_INTERNAL:
            return df_internal_operation(operation.operation, operands, operand_count, result);
        case DF_MACHINE_LEARNING:
            return df_machine_learning_operation(operation.operation, operands, operand_count, result);
        default:
            return 0;
    }
}

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
                           const DF_TYPE result_type,
                           DF_VALUE *result) {
    switch (operation.category) {
        case DF_ARITHMETIC:
            return df_arithmetic_operation_with_type(operation.operation, operands, operand_count, result_type, result);
        case DF_LOGIC:
            return df_logic_operation_with_type(operation.operation, operands, operand_count, result_type, result);
        case DF_INTERNAL:
            return df_internal_operation_with_type(operation.operation, operands, operand_count, result_type, result);
        case DF_MACHINE_LEARNING:
            return df_machine_learning_operation_with_type(operation.operation, operands, operand_count, result_type,
                                                           result);
        default:
            return 0;
    }
}
