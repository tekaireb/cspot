//
// Created by Lukas Brand Privat on 21.03.23.
//

#include "df_operation_logger.h"

#include <stdlib.h>

#include "df_logger.h"

void log_result_type_ignored() {
    //TODO
}

void log_operation_not_existing(const char *operation_category, unsigned int operation) {
    //TODO
}

void log_unsupported_type() {
    //TODO
}

void log_unsupported_type_on_operation(DF_TYPE type, const char *operation_name) {
    //TODO
}

void log_type_mismatch(const DF_TYPE result_type, const DF_TYPE current_type) {
    char *result_type_string = type_to_string((result_type));
    char *operand_type_string = type_to_string((current_type));
    log_error("Types mismatch: %s (operation_type) / %s (value type)", result_type_string,
              operand_type_string);
    free(result_type_string);
    free(operand_type_string);
}

void log_not_a_number(const DF_TYPE current_type) {
    char *operand_type_string = type_to_string((current_type));
    log_error("Operand is not a number: %s", operand_type_string);
    free(operand_type_string);
}

void log_value_count_mismatch(const unsigned int expected, const unsigned int actual) {
    log_error("Input value mismatch operation input count: expected %ud actual %ud", expected, actual);
}


