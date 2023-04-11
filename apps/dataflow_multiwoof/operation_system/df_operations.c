//
// Created by Lukas Brand on 29.03.23.
//

#include "df_operations.h"

#include <stdlib.h>
#include <string.h>

char* operation_to_string(const DF_OPERATION operation) {
    char* category_string;
    char* operation_string;
    switch (operation.category) {
        case DF_CAST:
            category_string = "CAST";
            switch ((DF_CAST_OP)operation.operation) {
                case DF_CAST_TO_BOOLEAN:
                    operation_string = "CAST TO BOOLEAN";
                    break;
                case DF_CAST_TO_BYTE:
                    operation_string = "CAST TO BYTE";
                    break;
                case DF_CAST_TO_SHORT:
                    operation_string = "CAST TO SHORT";
                    break;
                case DF_CAST_TO_INTEGER:
                    operation_string = "CAST TO INTEGER";
                    break;
                case DF_CAST_TO_LONG:
                    operation_string = "CAST TO LONG";
                    break;
                case DF_CAST_TO_UNSIGNED_BYTE:
                    operation_string = "CAST TO UNSIGNED BYTE";
                    break;
                case DF_CAST_TO_UNSIGNED_SHORT:
                    operation_string = "CAST TO UNSIGNED SHORT";
                    break;
                case DF_CAST_TO_UNSIGNED_INTEGER:
                    operation_string = "CAST TO UNSIGNED INTEGER";
                    break;
                case DF_CAST_TO_UNSIGNED_LONG:
                    operation_string = "CAST TO UNSIGNED LONG";
                    break;
                case DF_CAST_TO_DOUBLE:
                    operation_string = "CAST TO DOUBLE";
                    break;
                default:
                    operation_string = "UNKNOWN OPERATION";
                    break;
            }
            break;
        case DF_LOGIC:
            category_string = "LOGIC";
            switch ((DF_LOGIC_OP)operation.operation) {
                case DF_LOGIC_NOT:
                    operation_string = "NOT";
                    break;
                case DF_LOGIC_AND:
                    operation_string = "AND";
                    break;
                case DF_LOGIC_OR:
                    operation_string = "OR";
                    break;
                case DF_LOGIC_LESS_THAN:
                    operation_string = "LT";
                    break;
                case DF_LOGIC_LESS_THAN_EQUALS:
                    operation_string = "LTE";
                    break;
                case DF_LOGIC_GREATER_THAN:
                    operation_string = "GT";
                    break;
                case DF_LOGIC_GREATER_THAN_EQUALS:
                    operation_string = "GTE";
                    break;
                case DF_LOGIC_EQUALS:
                    operation_string = "EQ";
                    break;
                case DF_LOGIC_NOT_EQUALS:
                    operation_string = "NEQ";
                    break;
                default:
                    operation_string = "UNKNOWN OPERATION";
                    break;
            }
            break;
        case DF_ARITHMETIC:
            category_string = "ARITHMETIC";
            switch ((DF_ARITHMETIC_OP)operation.operation) {
                case DF_ARITH_ADDITION:
                    operation_string = "ADDITION";
                    break;
                case DF_ARITH_SUBTRACTION:
                    operation_string = "SUBTRACTION";
                    break;
                case DF_ARITH_MULTIPLICATION:
                    operation_string = "MULTIPLICATION";
                    break;
                case DF_ARITH_DIVISION:
                    operation_string = "DIVISION";
                    break;
                case DF_ARITH_MODULO:
                    operation_string = "MODULO";
                    break;
                case DF_ARITH_SQRT:
                    operation_string = "SQRT";
                    break;
                case DF_ARITH_ABS:
                    operation_string = "ABSOLUTE";
                    break;
                default:
                    operation_string = "UNKNOWN OPERATION";
                    break;
            }
            break;
        case DF_INTERNAL:
            category_string = "INTERNAL";
            switch ((DF_INTERNAL_OP)operation.operation) {
                case DF_INTERNAL_OPERAND:
                    operation_string = "OPERAND";
                    break;
                case DF_INTERNAL_SELECT:
                    operation_string = "SELECT";
                    break;
                case DF_INTERNAL_FILTER:
                    operation_string = "FILTER";
                    break;
                case DF_INTERNAL_OFFSET:
                    operation_string = "OFFSET";
                    break;
                default:
                    operation_string = "UNKNOWN OPERATION";
                    break;
            }
            break;
        case DF_MACHINE_LEARNING:
            category_string = "MACHINE LEARNING";
            switch ((DF_MACHINE_LEARNING_OP)operation.operation) {
                case DF_MACHINE_LEARNING_KNN:
                    operation_string = "K-NEAREST NEIGHBOR";
                    break;
                case DF_MACHINE_LEARNING_LINREG:
                    operation_string = "LINEAR REGRESSION";
                    break;
                default:
                    operation_string = "UNKNOWN OPERATION";
                    break;
            }
            break;
        default:
            category_string = "UNKNOWN CATEGORY";
            operation_string = "UNKNOWN OPERATION";
            break;
    }
    const char* colon_string = " :";
    const size_t colon_size = strlen(colon_string);
    const size_t category_string_size = strlen(category_string);
    const size_t operation_string_size = strlen(operation_string);

    char* return_string = malloc(category_string_size + colon_size + operation_string_size + 1);
    strcpy(return_string, category_string);
    strcat(return_string, colon_string);
    strcat(return_string, operation_string);

    return return_string;
}