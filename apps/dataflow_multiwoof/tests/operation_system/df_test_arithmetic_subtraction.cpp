//
// Created by Lukas Brand on 01.04.23.
//
#include <catch2/catch_test_macros.hpp>
#include "../../operation_system/df_arithmetic.h"

TEST_CASE("arithmetic: subtract: no value") {
    const DF_ARITHMETIC_OP arithmetic_operation = DF_ARITH_SUBTRACTION;
    const DF_VALUE op_list[] = {};
    const int operand_count = 0;
    DF_VALUE result;
    int return_value;
    SECTION("DF_UNKNOWN") {
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_UNKNOWN,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_BYTE") {
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_BYTE, &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_SHORT") {
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_SHORT,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_INTEGER") {
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_INTEGER,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_LONG") {
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_LONG, &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_UNSIGNED_BYTE") {
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_UNSIGNED_BYTE,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_UNSIGNED_SHORT") {
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count,
                                                         DF_UNSIGNED_SHORT, &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_UNSIGNED_INTEGER") {
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count,
                                                         DF_UNSIGNED_INTEGER, &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_UNSIGNED_LONG") {
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_UNSIGNED_LONG,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_DOUBLE") {
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_DOUBLE,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_DATETIME") {
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_DATETIME,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_STRING") {
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_STRING,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_ARRAY") {
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_ARRAY,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_LIST") {
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_LIST, &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_STREAM") {
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_STREAM,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_RECORD") {
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_RECORD,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
}

TEST_CASE("arithmetic: subtract: one value") {
    const DF_ARITHMETIC_OP arithmetic_operation = DF_ARITH_SUBTRACTION;
    const int operand_count = 1;
    DF_VALUE result;
    int return_value;
    SECTION("DF_UNKNOWN") {
        const DF_VALUE op1 = {.value = {}, .type=DF_UNKNOWN};
        const DF_VALUE op_list[] = {op1};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_UNKNOWN,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_BYTE") {
        const DF_VALUE op1 = {.value = {.df_int = 4}, .type=DF_BYTE};
        const DF_VALUE op_list[] = {op1};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_BYTE,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BYTE);
        REQUIRE(result.value.df_int == 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_SHORT") {
        const DF_VALUE op1 = {.value = {.df_int = 4}, .type=DF_SHORT};
        const DF_VALUE op_list[] = {op1};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_SHORT,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_SHORT);
        REQUIRE(result.value.df_int == 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_INTEGER") {
        const DF_VALUE op1 = {.value = {.df_int =4}, .type=DF_INTEGER};
        const DF_VALUE op_list[] = {op1};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_INTEGER,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_INTEGER);
        REQUIRE(result.value.df_int == 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_LONG") {
        const DF_VALUE op1 = {.value = {.df_long = 4}, .type=DF_LONG};
        const DF_VALUE op_list[] = {op1};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_LONG,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_LONG);
        REQUIRE(result.value.df_long == 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_UNSIGNED_BYTE") {
        const DF_VALUE op1 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op_list[] = {op1};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_UNSIGNED_BYTE,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_UNSIGNED_BYTE);
        REQUIRE(result.value.df_unsigned_int == 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_UNSIGNED_SHORT") {
        const DF_VALUE op1 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_SHORT};
        const DF_VALUE op_list[] = {op1};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count,
                                                         DF_UNSIGNED_SHORT, &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_UNSIGNED_SHORT);
        REQUIRE(result.value.df_unsigned_int == 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_UNSIGNED_INTEGER") {
        const DF_VALUE op1 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_INTEGER};
        const DF_VALUE op_list[] = {op1};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count,
                                                         DF_UNSIGNED_INTEGER, &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_UNSIGNED_INTEGER);
        REQUIRE(result.value.df_unsigned_int == 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_UNSIGNED_LONG") {
        const DF_VALUE op1 = {.value = {.df_unsigned_long = 4}, .type=DF_UNSIGNED_LONG};
        const DF_VALUE op_list[] = {op1};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_UNSIGNED_LONG,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_UNSIGNED_LONG);
        REQUIRE(result.value.df_unsigned_long == 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_DOUBLE") {
        const DF_VALUE op1 = {.value = {.df_double = 4}, .type=DF_DOUBLE};
        const DF_VALUE op_list[] = {op1};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_DOUBLE,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_DOUBLE);
        REQUIRE(result.value.df_double == 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_DATETIME") {
        const DF_VALUE op1 = {.value = {.df_long = 4}, .type=DF_DATETIME};
        const DF_VALUE op_list[] = {op1};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_DATETIME,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_STRING") {
        const DF_VALUE op1 = {.value = {.df_string = {}}, .type=DF_STRING};
        const DF_VALUE op_list[] = {op1};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_STRING,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_ARRAY") {
        const DF_VALUE op1 = {.value = {.df_array ={}}, .type=DF_ARRAY};
        const DF_VALUE op_list[] = {op1};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_ARRAY,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_LIST") {
        const DF_VALUE op1 = {.value = {.df_list = {}}, .type=DF_LIST};
        const DF_VALUE op_list[] = {op1};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_LIST,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_STREAM") {
        const DF_VALUE op1 = {.value = {.df_stream = {}}, .type=DF_STREAM};
        const DF_VALUE op_list[] = {op1};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_STREAM,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_RECORD") {
        const DF_VALUE op1 = {.value = {.df_record = {}}, .type=DF_RECORD};
        const DF_VALUE op_list[] = {op1};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_RECORD,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
}

TEST_CASE("arithmetic: subtract: two values") {
    const DF_ARITHMETIC_OP arithmetic_operation = DF_ARITH_SUBTRACTION;
    const int operand_count = 2;
    DF_VALUE result;
    int return_value;
    SECTION("DF_UNKNOWN") {
        const DF_VALUE op1 = {.value = {}, .type=DF_UNKNOWN};
        const DF_VALUE op2 = {.value = {}, .type=DF_UNKNOWN};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_UNKNOWN,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_BYTE") {
        const DF_VALUE op1 = {.value = {.df_int = 4}, .type=DF_BYTE};
        const DF_VALUE op2 = {.value = {.df_int = 4}, .type=DF_BYTE};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_BYTE,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BYTE);
        REQUIRE(result.value.df_int == 4 - 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_SHORT") {
        const DF_VALUE op1 = {.value = {.df_int = 4}, .type=DF_SHORT};
        const DF_VALUE op2 = {.value = {.df_int = 4}, .type=DF_SHORT};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_SHORT,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_SHORT);
        REQUIRE(result.value.df_int == 4 - 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_INTEGER") {
        const DF_VALUE op1 = {.value = {.df_int =4}, .type=DF_INTEGER};
        const DF_VALUE op2 = {.value = {.df_int =4}, .type=DF_INTEGER};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_INTEGER,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_INTEGER);
        REQUIRE(result.value.df_int == 4 - 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_LONG") {
        const DF_VALUE op1 = {.value = {.df_long = 4}, .type=DF_LONG};
        const DF_VALUE op2 = {.value = {.df_long = 4}, .type=DF_LONG};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_LONG,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_LONG);
        REQUIRE(result.value.df_long == 4 - 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_UNSIGNED_BYTE") {
        const DF_VALUE op1 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op2 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_UNSIGNED_BYTE,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_UNSIGNED_BYTE);
        REQUIRE(result.value.df_unsigned_int == 4 - 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_UNSIGNED_SHORT") {
        const DF_VALUE op1 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_SHORT};
        const DF_VALUE op2 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_SHORT};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count,
                                                         DF_UNSIGNED_SHORT, &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_UNSIGNED_SHORT);
        REQUIRE(result.value.df_unsigned_int == 4 - 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_UNSIGNED_INTEGER") {
        const DF_VALUE op1 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_INTEGER};
        const DF_VALUE op2 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_INTEGER};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count,
                                                         DF_UNSIGNED_INTEGER, &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_UNSIGNED_INTEGER);
        REQUIRE(result.value.df_unsigned_int == 4 - 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_UNSIGNED_LONG") {
        const DF_VALUE op1 = {.value = {.df_unsigned_long = 4}, .type=DF_UNSIGNED_LONG};
        const DF_VALUE op2 = {.value = {.df_unsigned_long = 4}, .type=DF_UNSIGNED_LONG};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_UNSIGNED_LONG,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_UNSIGNED_LONG);
        REQUIRE(result.value.df_unsigned_long == 4 - 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_DOUBLE") {
        const DF_VALUE op1 = {.value = {.df_double = 4}, .type=DF_DOUBLE};
        const DF_VALUE op2 = {.value = {.df_double = 4}, .type=DF_DOUBLE};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_DOUBLE,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_DOUBLE);
        REQUIRE(result.value.df_double == 4 - 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_DATETIME") {
        const DF_VALUE op1 = {.value = {.df_long = 4}, .type=DF_DATETIME};
        const DF_VALUE op2 = {.value = {.df_long = 4}, .type=DF_DATETIME};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_DATETIME,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_STRING") {
        const DF_VALUE op1 = {.value = {.df_string = {}}, .type=DF_STRING};
        const DF_VALUE op2 = {.value = {.df_string = {}}, .type=DF_STRING};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_STRING,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_ARRAY") {
        const DF_VALUE op1 = {.value = {.df_array ={}}, .type=DF_ARRAY};
        const DF_VALUE op2 = {.value = {.df_array ={}}, .type=DF_ARRAY};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_ARRAY,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_LIST") {
        const DF_VALUE op1 = {.value = {.df_list = {}}, .type=DF_LIST};
        const DF_VALUE op2 = {.value = {.df_list = {}}, .type=DF_LIST};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_LIST,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_STREAM") {
        const DF_VALUE op1 = {.value = {.df_stream = {}}, .type=DF_STREAM};
        const DF_VALUE op2 = {.value = {.df_stream = {}}, .type=DF_STREAM};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_STREAM,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_RECORD") {
        const DF_VALUE op1 = {.value = {.df_record = {}}, .type=DF_RECORD};
        const DF_VALUE op2 = {.value = {.df_record = {}}, .type=DF_RECORD};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_RECORD,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
}

TEST_CASE("arithmetic: subtract: ten values") {
    const DF_ARITHMETIC_OP arithmetic_operation = DF_ARITH_SUBTRACTION;
    const int operand_count = 10;
    DF_VALUE result;
    int return_value;
    SECTION("DF_UNKNOWN") {
        const DF_VALUE op1 = {.value = {}, .type=DF_UNKNOWN};
        const DF_VALUE op2 = {.value = {}, .type=DF_UNKNOWN};
        const DF_VALUE op3 = {.value = {}, .type=DF_UNKNOWN};
        const DF_VALUE op4 = {.value = {}, .type=DF_UNKNOWN};
        const DF_VALUE op5 = {.value = {}, .type=DF_UNKNOWN};
        const DF_VALUE op6 = {.value = {}, .type=DF_UNKNOWN};
        const DF_VALUE op7 = {.value = {}, .type=DF_UNKNOWN};
        const DF_VALUE op8 = {.value = {}, .type=DF_UNKNOWN};
        const DF_VALUE op9 = {.value = {}, .type=DF_UNKNOWN};
        const DF_VALUE op10 = {.value = {}, .type=DF_UNKNOWN};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5, op6, op7, op8, op9, op10};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_UNKNOWN,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_BYTE") {
        const DF_VALUE op1 = {.value = {.df_int = 100}, .type=DF_BYTE};
        const DF_VALUE op2 = {.value = {.df_int = 4}, .type=DF_BYTE};
        const DF_VALUE op3 = {.value = {.df_int = 4}, .type=DF_BYTE};
        const DF_VALUE op4 = {.value = {.df_int = 4}, .type=DF_BYTE};
        const DF_VALUE op5 = {.value = {.df_int = 4}, .type=DF_BYTE};
        const DF_VALUE op6 = {.value = {.df_int = 4}, .type=DF_BYTE};
        const DF_VALUE op7 = {.value = {.df_int = 4}, .type=DF_BYTE};
        const DF_VALUE op8 = {.value = {.df_int = 4}, .type=DF_BYTE};
        const DF_VALUE op9 = {.value = {.df_int = 4}, .type=DF_BYTE};
        const DF_VALUE op10 = {.value = {.df_int = 4}, .type=DF_BYTE};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5, op6, op7, op8, op9, op10};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_BYTE,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BYTE);
        REQUIRE(result.value.df_int == 100 - 9 * 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_SHORT") {
        const DF_VALUE op1 = {.value = {.df_int = 100}, .type=DF_SHORT};
        const DF_VALUE op2 = {.value = {.df_int = 4}, .type=DF_SHORT};
        const DF_VALUE op3 = {.value = {.df_int = 4}, .type=DF_SHORT};
        const DF_VALUE op4 = {.value = {.df_int = 4}, .type=DF_SHORT};
        const DF_VALUE op5 = {.value = {.df_int = 4}, .type=DF_SHORT};
        const DF_VALUE op6 = {.value = {.df_int = 4}, .type=DF_SHORT};
        const DF_VALUE op7 = {.value = {.df_int = 4}, .type=DF_SHORT};
        const DF_VALUE op8 = {.value = {.df_int = 4}, .type=DF_SHORT};
        const DF_VALUE op9 = {.value = {.df_int = 4}, .type=DF_SHORT};
        const DF_VALUE op10 = {.value = {.df_int = 4}, .type=DF_SHORT};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5, op6, op7, op8, op9, op10};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_SHORT,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_SHORT);
        REQUIRE(result.value.df_int == 100 - 9 * 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_INTEGER") {
        const DF_VALUE op1 = {.value = {.df_int = 100}, .type=DF_INTEGER};
        const DF_VALUE op2 = {.value = {.df_int = 4}, .type=DF_INTEGER};
        const DF_VALUE op3 = {.value = {.df_int = 4}, .type=DF_INTEGER};
        const DF_VALUE op4 = {.value = {.df_int = 4}, .type=DF_INTEGER};
        const DF_VALUE op5 = {.value = {.df_int = 4}, .type=DF_INTEGER};
        const DF_VALUE op6 = {.value = {.df_int = 4}, .type=DF_INTEGER};
        const DF_VALUE op7 = {.value = {.df_int = 4}, .type=DF_INTEGER};
        const DF_VALUE op8 = {.value = {.df_int = 4}, .type=DF_INTEGER};
        const DF_VALUE op9 = {.value = {.df_int = 4}, .type=DF_INTEGER};
        const DF_VALUE op10 = {.value = {.df_int = 4}, .type=DF_INTEGER};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5, op6, op7, op8, op9, op10};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_INTEGER,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_INTEGER);
        REQUIRE(result.value.df_int == 100 - 9 * 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_LONG") {
        const DF_VALUE op1 = {.value = {.df_long = 100}, .type=DF_LONG};
        const DF_VALUE op2 = {.value = {.df_long = 4}, .type=DF_LONG};
        const DF_VALUE op3 = {.value = {.df_long = 4}, .type=DF_LONG};
        const DF_VALUE op4 = {.value = {.df_long = 4}, .type=DF_LONG};
        const DF_VALUE op5 = {.value = {.df_long = 4}, .type=DF_LONG};
        const DF_VALUE op6 = {.value = {.df_long = 4}, .type=DF_LONG};
        const DF_VALUE op7 = {.value = {.df_long = 4}, .type=DF_LONG};
        const DF_VALUE op8 = {.value = {.df_long = 4}, .type=DF_LONG};
        const DF_VALUE op9 = {.value = {.df_long = 4}, .type=DF_LONG};
        const DF_VALUE op10 = {.value = {.df_long = 4}, .type=DF_LONG};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5, op6, op7, op8, op9, op10};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_LONG,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_LONG);
        REQUIRE(result.value.df_long == 100 - 9 * 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_UNSIGNED_BYTE") {
        const DF_VALUE op1 = {.value = {.df_unsigned_int = 100}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op2 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op3 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op4 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op5 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op6 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op7 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op8 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op9 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op10 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5, op6, op7, op8, op9, op10};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_UNSIGNED_BYTE,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_UNSIGNED_BYTE);
        REQUIRE(result.value.df_unsigned_int == 100 - 9 * 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_UNSIGNED_SHORT") {
        const DF_VALUE op1 = {.value = {.df_unsigned_int = 100}, .type=DF_UNSIGNED_SHORT};
        const DF_VALUE op2 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_SHORT};
        const DF_VALUE op3 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_SHORT};
        const DF_VALUE op4 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_SHORT};
        const DF_VALUE op5 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_SHORT};
        const DF_VALUE op6 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_SHORT};
        const DF_VALUE op7 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_SHORT};
        const DF_VALUE op8 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_SHORT};
        const DF_VALUE op9 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_SHORT};
        const DF_VALUE op10 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_SHORT};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5, op6, op7, op8, op9, op10};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count,
                                                         DF_UNSIGNED_SHORT, &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_UNSIGNED_SHORT);
        REQUIRE(result.value.df_unsigned_int == 100 - 9 * 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_UNSIGNED_INTEGER") {
        const DF_VALUE op1 = {.value = {.df_unsigned_int = 100}, .type=DF_UNSIGNED_INTEGER};
        const DF_VALUE op2 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_INTEGER};
        const DF_VALUE op3 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_INTEGER};
        const DF_VALUE op4 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_INTEGER};
        const DF_VALUE op5 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_INTEGER};
        const DF_VALUE op6 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_INTEGER};
        const DF_VALUE op7 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_INTEGER};
        const DF_VALUE op8 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_INTEGER};
        const DF_VALUE op9 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_INTEGER};
        const DF_VALUE op10 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_INTEGER};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5, op6, op7, op8, op9, op10};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count,
                                                         DF_UNSIGNED_INTEGER, &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_UNSIGNED_INTEGER);
        REQUIRE(result.value.df_unsigned_int == 100 - 9 * 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_UNSIGNED_LONG") {
        const DF_VALUE op1 = {.value = {.df_unsigned_long = 100}, .type=DF_UNSIGNED_LONG};
        const DF_VALUE op2 = {.value = {.df_unsigned_long = 4}, .type=DF_UNSIGNED_LONG};
        const DF_VALUE op3 = {.value = {.df_unsigned_long = 4}, .type=DF_UNSIGNED_LONG};
        const DF_VALUE op4 = {.value = {.df_unsigned_long = 4}, .type=DF_UNSIGNED_LONG};
        const DF_VALUE op5 = {.value = {.df_unsigned_long = 4}, .type=DF_UNSIGNED_LONG};
        const DF_VALUE op6 = {.value = {.df_unsigned_long = 4}, .type=DF_UNSIGNED_LONG};
        const DF_VALUE op7 = {.value = {.df_unsigned_long = 4}, .type=DF_UNSIGNED_LONG};
        const DF_VALUE op8 = {.value = {.df_unsigned_long = 4}, .type=DF_UNSIGNED_LONG};
        const DF_VALUE op9 = {.value = {.df_unsigned_long = 4}, .type=DF_UNSIGNED_LONG};
        const DF_VALUE op10 = {.value = {.df_unsigned_long = 4}, .type=DF_UNSIGNED_LONG};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5, op6, op7, op8, op9, op10};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_UNSIGNED_LONG,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_UNSIGNED_LONG);
        REQUIRE(result.value.df_unsigned_long == 100 - 9 * 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_DOUBLE") {
        const DF_VALUE op1 = {.value = {.df_double = 100}, .type=DF_DOUBLE};
        const DF_VALUE op2 = {.value = {.df_double = 4}, .type=DF_DOUBLE};
        const DF_VALUE op3 = {.value = {.df_double = 4}, .type=DF_DOUBLE};
        const DF_VALUE op4 = {.value = {.df_double = 4}, .type=DF_DOUBLE};
        const DF_VALUE op5 = {.value = {.df_double = 4}, .type=DF_DOUBLE};
        const DF_VALUE op6 = {.value = {.df_double = 4}, .type=DF_DOUBLE};
        const DF_VALUE op7 = {.value = {.df_double = 4}, .type=DF_DOUBLE};
        const DF_VALUE op8 = {.value = {.df_double = 4}, .type=DF_DOUBLE};
        const DF_VALUE op9 = {.value = {.df_double = 4}, .type=DF_DOUBLE};
        const DF_VALUE op10 = {.value = {.df_double = 4}, .type=DF_DOUBLE};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5, op6, op7, op8, op9, op10};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_DOUBLE,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_DOUBLE);
        REQUIRE(result.value.df_double == 100 - 9 * 4);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_DATETIME") {
        const DF_VALUE op1 = {.value = {.df_long = 100}, .type=DF_DATETIME};
        const DF_VALUE op2 = {.value = {.df_long = 4}, .type=DF_DATETIME};
        const DF_VALUE op3 = {.value = {.df_long = 4}, .type=DF_DATETIME};
        const DF_VALUE op4 = {.value = {.df_long = 4}, .type=DF_DATETIME};
        const DF_VALUE op5 = {.value = {.df_long = 4}, .type=DF_DATETIME};
        const DF_VALUE op6 = {.value = {.df_long = 4}, .type=DF_DATETIME};
        const DF_VALUE op7 = {.value = {.df_long = 4}, .type=DF_DATETIME};
        const DF_VALUE op8 = {.value = {.df_long = 4}, .type=DF_DATETIME};
        const DF_VALUE op9 = {.value = {.df_long = 4}, .type=DF_DATETIME};
        const DF_VALUE op10 = {.value = {.df_long = 4}, .type=DF_DATETIME};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5, op6, op7, op8, op9, op10};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_DATETIME,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_STRING") {
        const DF_VALUE op1 = {.value = {.df_string = {}}, .type=DF_STRING};
        const DF_VALUE op2 = {.value = {.df_string = {}}, .type=DF_STRING};
        const DF_VALUE op3 = {.value = {.df_string = {}}, .type=DF_STRING};
        const DF_VALUE op4 = {.value = {.df_string = {}}, .type=DF_STRING};
        const DF_VALUE op5 = {.value = {.df_string = {}}, .type=DF_STRING};
        const DF_VALUE op6 = {.value = {.df_string = {}}, .type=DF_STRING};
        const DF_VALUE op7 = {.value = {.df_string = {}}, .type=DF_STRING};
        const DF_VALUE op8 = {.value = {.df_string = {}}, .type=DF_STRING};
        const DF_VALUE op9 = {.value = {.df_string = {}}, .type=DF_STRING};
        const DF_VALUE op10 = {.value = {.df_string = {}}, .type=DF_STRING};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5, op6, op7, op8, op9, op10};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_STRING,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_ARRAY") {
        const DF_VALUE op1 = {.value = {.df_array = {}}, .type=DF_ARRAY};
        const DF_VALUE op2 = {.value = {.df_array = {}}, .type=DF_ARRAY};
        const DF_VALUE op3 = {.value = {.df_array = {}}, .type=DF_ARRAY};
        const DF_VALUE op4 = {.value = {.df_array = {}}, .type=DF_ARRAY};
        const DF_VALUE op5 = {.value = {.df_array = {}}, .type=DF_ARRAY};
        const DF_VALUE op6 = {.value = {.df_array = {}}, .type=DF_ARRAY};
        const DF_VALUE op7 = {.value = {.df_array = {}}, .type=DF_ARRAY};
        const DF_VALUE op8 = {.value = {.df_array = {}}, .type=DF_ARRAY};
        const DF_VALUE op9 = {.value = {.df_array = {}}, .type=DF_ARRAY};
        const DF_VALUE op10 = {.value = {.df_array = {}}, .type=DF_ARRAY};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5, op6, op7, op8, op9, op10};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_ARRAY,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_LIST") {
        const DF_VALUE op1 = {.value = {.df_list = {}}, .type=DF_LIST};
        const DF_VALUE op2 = {.value = {.df_list = {}}, .type=DF_LIST};
        const DF_VALUE op3 = {.value = {.df_list = {}}, .type=DF_LIST};
        const DF_VALUE op4 = {.value = {.df_list = {}}, .type=DF_LIST};
        const DF_VALUE op5 = {.value = {.df_list = {}}, .type=DF_LIST};
        const DF_VALUE op6 = {.value = {.df_list = {}}, .type=DF_LIST};
        const DF_VALUE op7 = {.value = {.df_list = {}}, .type=DF_LIST};
        const DF_VALUE op8 = {.value = {.df_list = {}}, .type=DF_LIST};
        const DF_VALUE op9 = {.value = {.df_list = {}}, .type=DF_LIST};
        const DF_VALUE op10 = {.value = {.df_list = {}}, .type=DF_LIST};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5, op6, op7, op8, op9, op10};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_LIST,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_STREAM") {
        const DF_VALUE op1 = {.value = {.df_stream = {}}, .type=DF_STREAM};
        const DF_VALUE op2 = {.value = {.df_stream = {}}, .type=DF_STREAM};
        const DF_VALUE op3 = {.value = {.df_stream = {}}, .type=DF_STREAM};
        const DF_VALUE op4 = {.value = {.df_stream = {}}, .type=DF_STREAM};
        const DF_VALUE op5 = {.value = {.df_stream = {}}, .type=DF_STREAM};
        const DF_VALUE op6 = {.value = {.df_stream = {}}, .type=DF_STREAM};
        const DF_VALUE op7 = {.value = {.df_stream = {}}, .type=DF_STREAM};
        const DF_VALUE op8 = {.value = {.df_stream = {}}, .type=DF_STREAM};
        const DF_VALUE op9 = {.value = {.df_stream = {}}, .type=DF_STREAM};
        const DF_VALUE op10 = {.value = {.df_stream = {}}, .type=DF_STREAM};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5, op6, op7, op8, op9, op10};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_STREAM,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_RECORD") {
        const DF_VALUE op1 = {.value = {.df_record = {}}, .type=DF_RECORD};
        const DF_VALUE op2 = {.value = {.df_record = {}}, .type=DF_RECORD};
        const DF_VALUE op3 = {.value = {.df_record = {}}, .type=DF_RECORD};
        const DF_VALUE op4 = {.value = {.df_record = {}}, .type=DF_RECORD};
        const DF_VALUE op5 = {.value = {.df_record = {}}, .type=DF_RECORD};
        const DF_VALUE op6 = {.value = {.df_record = {}}, .type=DF_RECORD};
        const DF_VALUE op7 = {.value = {.df_record = {}}, .type=DF_RECORD};
        const DF_VALUE op8 = {.value = {.df_record = {}}, .type=DF_RECORD};
        const DF_VALUE op9 = {.value = {.df_record = {}}, .type=DF_RECORD};
        const DF_VALUE op10 = {.value = {.df_record = {}}, .type=DF_RECORD};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5, op6, op7, op8, op9, op10};
        return_value = df_arithmetic_operation_with_type(arithmetic_operation, op_list, operand_count, DF_RECORD,
                                                         &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
}