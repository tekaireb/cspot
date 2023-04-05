//
// Created by Lukas Brand on 04.04.23.
//
#include <catch2/catch_test_macros.hpp>
#include "../../operation_system/df_logic.h"

TEST_CASE("logic: neq: no value") {
    const DF_LOGIC_OP logic_operation = DF_LOGIC_NOT_EQUALS;
    const DF_VALUE op_list[] = {};
    const int operand_count = 0;
    DF_VALUE result;
    int return_value;
    SECTION("DF_UNKNOWN") {
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_UNKNOWN,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_BOOLEAN") {
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_BOOLEAN,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_BYTE") {
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_BYTE, &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_SHORT") {
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_SHORT,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_INTEGER") {
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_INTEGER,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_LONG") {
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_LONG, &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_UNSIGNED_BYTE") {
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_UNSIGNED_BYTE,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_UNSIGNED_SHORT") {
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count,
                                                    DF_UNSIGNED_SHORT, &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_UNSIGNED_INTEGER") {
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count,
                                                    DF_UNSIGNED_INTEGER, &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_UNSIGNED_LONG") {
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_UNSIGNED_LONG,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_DOUBLE") {
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_DOUBLE,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_DATETIME") {
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_DATETIME,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_STRING") {
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_STRING,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_ARRAY") {
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_ARRAY,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_LIST") {
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_LIST, &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_STREAM") {
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_STREAM,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_RECORD") {
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_RECORD,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
}

TEST_CASE("logic: neq: one value") {
    const DF_LOGIC_OP logic_operation = DF_LOGIC_NOT_EQUALS;
    const int operand_count = 1;
    DF_VALUE result;
    int return_value;
    SECTION("DF_UNKNOWN") {
        const DF_VALUE op1 = {.value = {}, .type=DF_UNKNOWN};
        const DF_VALUE op_list[] = {op1};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_UNKNOWN,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_BOOLEAN") {
        const DF_VALUE op1 = {.value = {.df_int = 1}, .type=DF_BOOLEAN};
        const DF_VALUE op_list[] = {op1};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_BOOLEAN,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_BYTE") {
        const DF_VALUE op1 = {.value = {.df_int = 4}, .type=DF_BYTE};
        const DF_VALUE op_list[] = {op1};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_BYTE,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_SHORT") {
        const DF_VALUE op1 = {.value = {.df_int = 4}, .type=DF_SHORT};
        const DF_VALUE op_list[] = {op1};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_SHORT,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_INTEGER") {
        const DF_VALUE op1 = {.value = {.df_int = 4}, .type=DF_INTEGER};
        const DF_VALUE op_list[] = {op1};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_INTEGER,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_LONG") {
        const DF_VALUE op1 = {.value = {.df_long = 4}, .type=DF_LONG};
        const DF_VALUE op_list[] = {op1};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_LONG,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_UNSIGNED_BYTE") {
        const DF_VALUE op1 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op_list[] = {op1};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_UNSIGNED_BYTE,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_UNSIGNED_SHORT") {
        const DF_VALUE op1 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_SHORT};
        const DF_VALUE op_list[] = {op1};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count,
                                                    DF_UNSIGNED_SHORT, &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_UNSIGNED_INTEGER") {
        const DF_VALUE op1 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_INTEGER};
        const DF_VALUE op_list[] = {op1};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count,
                                                    DF_UNSIGNED_INTEGER, &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_UNSIGNED_LONG") {
        const DF_VALUE op1 = {.value = {.df_unsigned_long = 4}, .type=DF_UNSIGNED_LONG};
        const DF_VALUE op_list[] = {op1};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_UNSIGNED_LONG,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_DOUBLE") {
        const DF_VALUE op1 = {.value = {.df_double = 4}, .type=DF_DOUBLE};
        const DF_VALUE op_list[] = {op1};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_DOUBLE,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_DATETIME") {
        const DF_VALUE op1 = {.value = {.df_long = 4}, .type=DF_DATETIME};
        const DF_VALUE op_list[] = {op1};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_DATETIME,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_STRING") {
        const DF_VALUE op1 = {.value = {.df_string = {}}, .type=DF_STRING};
        const DF_VALUE op_list[] = {op1};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_STRING,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_ARRAY") {
        const DF_VALUE op1 = {.value = {.df_array ={}}, .type=DF_ARRAY};
        const DF_VALUE op_list[] = {op1};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_ARRAY,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_LIST") {
        const DF_VALUE op1 = {.value = {.df_list = {}}, .type=DF_LIST};
        const DF_VALUE op_list[] = {op1};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_LIST,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_STREAM") {
        const DF_VALUE op1 = {.value = {.df_stream = {}}, .type=DF_STREAM};
        const DF_VALUE op_list[] = {op1};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_STREAM,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_RECORD") {
        const DF_VALUE op1 = {.value = {.df_record = {}}, .type=DF_RECORD};
        const DF_VALUE op_list[] = {op1};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_RECORD,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
}

TEST_CASE("logic: neq: two values") {
    const DF_LOGIC_OP logic_operation = DF_LOGIC_NOT_EQUALS;
    const int operand_count = 2;
    DF_VALUE result;
    int return_value;
    SECTION("DF_UNKNOWN") {
        const DF_VALUE op1 = {.value = {}, .type=DF_UNKNOWN};
        const DF_VALUE op2 = {.value = {}, .type=DF_UNKNOWN};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_UNKNOWN,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_BOOLEAN") {
        const DF_VALUE op1 = {.value = {.df_int = 1}, .type=DF_BOOLEAN};
        const DF_VALUE op2 = {.value = {.df_int = 0}, .type=DF_BOOLEAN};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_BOOLEAN,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_BYTE") {
        const DF_VALUE op1 = {.value = {.df_int = 1}, .type=DF_BYTE};
        const DF_VALUE op2 = {.value = {.df_int = 2}, .type=DF_BYTE};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_BYTE,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BOOLEAN);
        REQUIRE(result.value.df_int == 1);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_SHORT") {
        const DF_VALUE op1 = {.value = {.df_int = 1}, .type=DF_SHORT};
        const DF_VALUE op2 = {.value = {.df_int = 2}, .type=DF_SHORT};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_SHORT,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BOOLEAN);
        REQUIRE(result.value.df_int == 1);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_INTEGER") {
        const DF_VALUE op1 = {.value = {.df_int = 1}, .type=DF_INTEGER};
        const DF_VALUE op2 = {.value = {.df_int = 2}, .type=DF_INTEGER};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_INTEGER,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BOOLEAN);
        REQUIRE(result.value.df_int == 1);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_LONG") {
        const DF_VALUE op1 = {.value = {.df_long = 1}, .type=DF_LONG};
        const DF_VALUE op2 = {.value = {.df_long = 2}, .type=DF_LONG};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_LONG,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BOOLEAN);
        REQUIRE(result.value.df_int == 1);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_UNSIGNED_BYTE") {
        const DF_VALUE op1 = {.value = {.df_unsigned_int = 1}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op2 = {.value = {.df_unsigned_int = 2}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_UNSIGNED_BYTE,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BOOLEAN);
        REQUIRE(result.value.df_int == 1);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_UNSIGNED_SHORT") {
        const DF_VALUE op1 = {.value = {.df_unsigned_int = 1}, .type=DF_UNSIGNED_SHORT};
        const DF_VALUE op2 = {.value = {.df_unsigned_int = 2}, .type=DF_UNSIGNED_SHORT};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count,
                                                    DF_UNSIGNED_SHORT, &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BOOLEAN);
        REQUIRE(result.value.df_int == 1);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_UNSIGNED_INTEGER") {
        const DF_VALUE op1 = {.value = {.df_unsigned_int = 1}, .type=DF_UNSIGNED_INTEGER};
        const DF_VALUE op2 = {.value = {.df_unsigned_int = 2}, .type=DF_UNSIGNED_INTEGER};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count,
                                                    DF_UNSIGNED_INTEGER, &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BOOLEAN);
        REQUIRE(result.value.df_int == 1);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_UNSIGNED_LONG") {
        const DF_VALUE op1 = {.value = {.df_unsigned_long = 1}, .type=DF_UNSIGNED_LONG};
        const DF_VALUE op2 = {.value = {.df_unsigned_long = 2}, .type=DF_UNSIGNED_LONG};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_UNSIGNED_LONG,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BOOLEAN);
        REQUIRE(result.value.df_int == 1);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_DOUBLE") {
        const DF_VALUE op1 = {.value = {.df_double = 1}, .type=DF_DOUBLE};
        const DF_VALUE op2 = {.value = {.df_double = 2}, .type=DF_DOUBLE};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_DOUBLE,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BOOLEAN);
        REQUIRE(result.value.df_int == 1);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_DATETIME") {
        const DF_VALUE op1 = {.value = {.df_long = 1}, .type=DF_DATETIME};
        const DF_VALUE op2 = {.value = {.df_long = 2}, .type=DF_DATETIME};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_DATETIME,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BOOLEAN);
        REQUIRE(result.value.df_int == 1);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_STRING") {
        const DF_VALUE op1 = {.value = {.df_string = {}}, .type=DF_STRING};
        const DF_VALUE op2 = {.value = {.df_string = {}}, .type=DF_STRING};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_STRING,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_ARRAY") {
        const DF_VALUE op1 = {.value = {.df_array = {}}, .type=DF_ARRAY};
        const DF_VALUE op2 = {.value = {.df_array = {}}, .type=DF_ARRAY};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_ARRAY,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_LIST") {
        const DF_VALUE op1 = {.value = {.df_list = {}}, .type=DF_LIST};
        const DF_VALUE op2 = {.value = {.df_list = {}}, .type=DF_LIST};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_LIST,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_STREAM") {
        const DF_VALUE op1 = {.value = {.df_stream = {}}, .type=DF_STREAM};
        const DF_VALUE op2 = {.value = {.df_stream = {}}, .type=DF_STREAM};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_STREAM,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_RECORD") {
        const DF_VALUE op1 = {.value = {.df_record = {}}, .type=DF_RECORD};
        const DF_VALUE op2 = {.value = {.df_record = {}}, .type=DF_RECORD};
        const DF_VALUE op_list[] = {op1, op2};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_RECORD,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
}

TEST_CASE("logic: neq: five values") {
    const DF_LOGIC_OP logic_operation = DF_LOGIC_NOT_EQUALS;
    const int operand_count = 5;
    DF_VALUE result;
    int return_value;
    SECTION("DF_UNKNOWN") {
        const DF_VALUE op1 = {.value = {}, .type=DF_UNKNOWN};
        const DF_VALUE op2 = {.value = {}, .type=DF_UNKNOWN};
        const DF_VALUE op3 = {.value = {}, .type=DF_UNKNOWN};
        const DF_VALUE op4 = {.value = {}, .type=DF_UNKNOWN};
        const DF_VALUE op5 = {.value = {}, .type=DF_UNKNOWN};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_UNKNOWN,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_BOOLEAN") {
        const DF_VALUE op1 = {.value = {.df_int = 1}, .type=DF_BOOLEAN};
        const DF_VALUE op2 = {.value = {.df_int = 2}, .type=DF_BOOLEAN};
        const DF_VALUE op3 = {.value = {.df_int = 3}, .type=DF_BOOLEAN};
        const DF_VALUE op4 = {.value = {.df_int = 4}, .type=DF_BOOLEAN};
        const DF_VALUE op5 = {.value = {.df_int = 5}, .type=DF_BOOLEAN};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_BOOLEAN,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
    SECTION("DF_BYTE") {
        const DF_VALUE op1 = {.value = {.df_int = 1}, .type=DF_BYTE};
        const DF_VALUE op2 = {.value = {.df_int = 2}, .type=DF_BYTE};
        const DF_VALUE op3 = {.value = {.df_int = 3}, .type=DF_BYTE};
        const DF_VALUE op4 = {.value = {.df_int = 4}, .type=DF_BYTE};
        const DF_VALUE op5 = {.value = {.df_int = 5}, .type=DF_BYTE};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_BYTE,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BOOLEAN);
        REQUIRE(result.value.df_int == 1);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_SHORT") {
        const DF_VALUE op1 = {.value = {.df_int = 1}, .type=DF_SHORT};
        const DF_VALUE op2 = {.value = {.df_int = 2}, .type=DF_SHORT};
        const DF_VALUE op3 = {.value = {.df_int = 3}, .type=DF_SHORT};
        const DF_VALUE op4 = {.value = {.df_int = 4}, .type=DF_SHORT};
        const DF_VALUE op5 = {.value = {.df_int = 5}, .type=DF_SHORT};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_SHORT,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BOOLEAN);
        REQUIRE(result.value.df_int == 1);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_INTEGER") {
        const DF_VALUE op1 = {.value = {.df_int = 1}, .type=DF_INTEGER};
        const DF_VALUE op2 = {.value = {.df_int = 2}, .type=DF_INTEGER};
        const DF_VALUE op3 = {.value = {.df_int = 3}, .type=DF_INTEGER};
        const DF_VALUE op4 = {.value = {.df_int = 4}, .type=DF_INTEGER};
        const DF_VALUE op5 = {.value = {.df_int = 5}, .type=DF_INTEGER};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_INTEGER,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BOOLEAN);
        REQUIRE(result.value.df_int == 1);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_LONG") {
        const DF_VALUE op1 = {.value = {.df_long = 1}, .type=DF_LONG};
        const DF_VALUE op2 = {.value = {.df_long = 2}, .type=DF_LONG};
        const DF_VALUE op3 = {.value = {.df_long = 3}, .type=DF_LONG};
        const DF_VALUE op4 = {.value = {.df_long = 4}, .type=DF_LONG};
        const DF_VALUE op5 = {.value = {.df_long = 5}, .type=DF_LONG};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_LONG,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BOOLEAN);
        REQUIRE(result.value.df_int == 1);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_UNSIGNED_BYTE") {
        const DF_VALUE op1 = {.value = {.df_unsigned_int = 1}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op2 = {.value = {.df_unsigned_int = 2}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op3 = {.value = {.df_unsigned_int = 3}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op4 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op5 = {.value = {.df_unsigned_int = 5}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_UNSIGNED_BYTE,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BOOLEAN);
        REQUIRE(result.value.df_int == 1);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_UNSIGNED_SHORT") {
        const DF_VALUE op1 = {.value = {.df_unsigned_int = 1}, .type=DF_UNSIGNED_SHORT};
        const DF_VALUE op2 = {.value = {.df_unsigned_int = 2}, .type=DF_UNSIGNED_SHORT};
        const DF_VALUE op3 = {.value = {.df_unsigned_int = 3}, .type=DF_UNSIGNED_SHORT};
        const DF_VALUE op4 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_SHORT};
        const DF_VALUE op5 = {.value = {.df_unsigned_int = 5}, .type=DF_UNSIGNED_SHORT};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count,
                                                    DF_UNSIGNED_SHORT, &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BOOLEAN);
        REQUIRE(result.value.df_int == 1);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_UNSIGNED_INTEGER") {
        const DF_VALUE op1 = {.value = {.df_unsigned_int = 1}, .type=DF_UNSIGNED_INTEGER};
        const DF_VALUE op2 = {.value = {.df_unsigned_int = 2}, .type=DF_UNSIGNED_INTEGER};
        const DF_VALUE op3 = {.value = {.df_unsigned_int = 3}, .type=DF_UNSIGNED_INTEGER};
        const DF_VALUE op4 = {.value = {.df_unsigned_int = 4}, .type=DF_UNSIGNED_INTEGER};
        const DF_VALUE op5 = {.value = {.df_unsigned_int = 5}, .type=DF_UNSIGNED_INTEGER};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count,
                                                    DF_UNSIGNED_INTEGER, &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BOOLEAN);
        REQUIRE(result.value.df_int == 1);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_UNSIGNED_LONG") {
        const DF_VALUE op1 = {.value = {.df_unsigned_long = 1}, .type=DF_UNSIGNED_LONG};
        const DF_VALUE op2 = {.value = {.df_unsigned_long = 2}, .type=DF_UNSIGNED_LONG};
        const DF_VALUE op3 = {.value = {.df_unsigned_long = 3}, .type=DF_UNSIGNED_LONG};
        const DF_VALUE op4 = {.value = {.df_unsigned_long = 4}, .type=DF_UNSIGNED_LONG};
        const DF_VALUE op5 = {.value = {.df_unsigned_long = 5}, .type=DF_UNSIGNED_LONG};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_UNSIGNED_LONG,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BOOLEAN);
        REQUIRE(result.value.df_int == 1);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_DOUBLE") {
        const DF_VALUE op1 = {.value = {.df_double = 1}, .type=DF_DOUBLE};
        const DF_VALUE op2 = {.value = {.df_double = 2}, .type=DF_DOUBLE};
        const DF_VALUE op3 = {.value = {.df_double = 3}, .type=DF_DOUBLE};
        const DF_VALUE op4 = {.value = {.df_double = 4}, .type=DF_DOUBLE};
        const DF_VALUE op5 = {.value = {.df_double = 5}, .type=DF_DOUBLE};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_DOUBLE,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BOOLEAN);
        REQUIRE(result.value.df_int == 1);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_DATETIME") {
        const DF_VALUE op1 = {.value = {.df_long = 1}, .type=DF_DATETIME};
        const DF_VALUE op2 = {.value = {.df_long = 2}, .type=DF_DATETIME};
        const DF_VALUE op3 = {.value = {.df_long = 3}, .type=DF_DATETIME};
        const DF_VALUE op4 = {.value = {.df_long = 4}, .type=DF_DATETIME};
        const DF_VALUE op5 = {.value = {.df_long = 5}, .type=DF_DATETIME};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_DATETIME,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BOOLEAN);
        REQUIRE(result.value.df_int == 1);
        REQUIRE(return_value == 1);
    }//
    SECTION("DF_STRING") {
        const DF_VALUE op1 = {.value = {.df_string = {}}, .type=DF_STRING};
        const DF_VALUE op2 = {.value = {.df_string = {}}, .type=DF_STRING};
        const DF_VALUE op3 = {.value = {.df_string = {}}, .type=DF_STRING};
        const DF_VALUE op4 = {.value = {.df_string = {}}, .type=DF_STRING};
        const DF_VALUE op5 = {.value = {.df_string = {}}, .type=DF_STRING};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_STRING,
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
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_ARRAY,
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
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_LIST,
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
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_STREAM,
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
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_RECORD,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(return_value == 0);
    }//
}

TEST_CASE("logic: neq: five different value types") {
    const DF_LOGIC_OP logic_operation = DF_LOGIC_NOT_EQUALS;
    const int operand_count = 5;
    DF_VALUE result;
    int return_value;
    SECTION("DIFFERENT->0") {
        const DF_VALUE op1 = {.value = {.df_int = 6}, .type=DF_BYTE};
        const DF_VALUE op2 = {.value = {.df_unsigned_int = 2}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op3 = {.value = {.df_int = 3}, .type=DF_INTEGER};
        const DF_VALUE op4 = {.value = {.df_long = 4}, .type=DF_LONG};
        const DF_VALUE op5 = {.value = {.df_double = 4}, .type=DF_DOUBLE};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_BOOLEAN,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BOOLEAN);
        REQUIRE(result.value.df_int == 0);
        REQUIRE(return_value == 1);
    }//
    SECTION("DIFFERENT->1") {
        const DF_VALUE op1 = {.value = {.df_int = 6}, .type=DF_BYTE};
        const DF_VALUE op2 = {.value = {.df_unsigned_int = 2}, .type=DF_UNSIGNED_BYTE};
        const DF_VALUE op3 = {.value = {.df_int = 3}, .type=DF_INTEGER};
        const DF_VALUE op4 = {.value = {.df_long = 4}, .type=DF_LONG};
        const DF_VALUE op5 = {.value = {.df_double = 5}, .type=DF_DOUBLE};
        const DF_VALUE op_list[] = {op1, op2, op3, op4, op5};
        return_value = df_logic_operation_with_type(logic_operation, op_list, operand_count, DF_BOOLEAN,
                                                    &result);
        REQUIRE(&result != NULL);
        REQUIRE(result.type == DF_BOOLEAN);
        REQUIRE(result.value.df_int == 1);
        REQUIRE(return_value == 1);
    }//
}