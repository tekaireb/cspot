#include "df_operation.h"

#include "df_arithmetic.h"
#include "df_internal.h"
#include "df_logic.h"
#include "df_machine_learning.h"

int df_operation(const DF_OPERATION_TYPE operation,
                 const unsigned int command,
                 const DF_VALUE values[],
                 const unsigned int value_count,
                 DF_VALUE* return_value) {
    // TODO
    switch (operation) {
    case ARITHMETIC:
        return df_arithmetic_operation(command, values, value_count, return_value);
    case LOGIC:
        return df_logic_operation(command, values, value_count, return_value);
    case INTERNAL:
        return df_internal_operation(command, values, value_count, return_value);
    case MACHINE_LEARNING:
        return df_machine_learning_operation(command, values, value_count, return_value);
    default:
        return -1;
    }
}

int df_operation_with_type(const DF_OPERATION_TYPE operation,
                           const unsigned int command,
                           const DF_TYPE operation_type,
                           const DF_VALUE values[],
                           const unsigned int value_count,
                           DF_VALUE* return_value) {
    switch (operation) {
    case ARITHMETIC:
        return df_arithmetic_operation_with_type(command, operation_type, values, value_count, return_value);
    case LOGIC:
        return df_logic_operation_with_type(command, operation_type, values, value_count, return_value);
    case INTERNAL:
        return df_internal_operation_with_type(command, operation_type, values, value_count, return_value);
    case MACHINE_LEARNING:
        return df_machine_learning_operation_with_type(command, operation_type, values, value_count, return_value);
    default:
        return -1;
    }
}
