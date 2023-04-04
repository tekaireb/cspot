//
// Created by Lukas Brand Privat on 30.03.23.
//
#include "df_types.h"

#include <stdlib.h>
#include <string.h>

char *type_to_string(const DF_TYPE type) {
    char *string;
    switch (type) {
        case DF_UNKNOWN: {
            char *temp_string = "UNKNOWN";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        }
            break;
        case DF_BOOLEAN: {
            char *temp_string = "BOOLEAN";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        }
            break;
        case DF_BYTE: {
            char *temp_string = "BYTE";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        }
            break;
        case DF_SHORT: {
            char *temp_string = "SHORT";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        }
            break;
        case DF_INTEGER: {
            char *temp_string = "INTEGER";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        }
            break;
        case DF_LONG: {
            char *temp_string = "LONG";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        }
            break;
        case DF_UNSIGNED_BYTE: {
            char *temp_string = "UNSIGNED BYTE";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        }
            break;
        case DF_UNSIGNED_SHORT: {
            char *temp_string = "UNSIGNED SHORT";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        }
            break;
        case DF_UNSIGNED_INTEGER: {
            char *temp_string = "UNSIGNED INTEGER";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        }
            break;
        case DF_UNSIGNED_LONG: {
            char *temp_string = "UNSIGNED LONG";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        }
            break;
        case DF_DOUBLE: {
            char *temp_string = "DOUBLE";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        }
            break;
        case DF_DATETIME: {
            char *temp_string = "DATETIME";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        }
            break;
        case DF_STRING: {
            char *temp_string = "STRING";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        }
            break;
        case DF_ARRAY: {
            char *temp_string = "ARRAY";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        }
            break;
        case DF_LIST: {
            char *temp_string = "LIST";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        }
            break;
        case DF_STREAM: {
            char *temp_string = "STREAM";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        }
            break;
        case DF_RECORD: {
            char *temp_string = "RECORD";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        }
            break;
        default: {
            char *temp_string = "UNRECOGNIZED TYPE";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        }
    }
    return string;
}

char *value_to_string(const DF_VALUE value) {
    char **value_string = NULL;
    size_t value_string_size = 0;
    switch (value.type) {
        case DF_UNKNOWN:
            value_string_size = asprintf(value_string, "UNKNOWN: UNKNOWN VALUE");
            break;
        case DF_BOOLEAN:
            value_string_size = asprintf(value_string, "BOOLEAN: %d", value.value.df_int);
            break;
        case DF_BYTE:
            value_string_size = asprintf(value_string, "BYTE: %d", value.value.df_int);
            break;
        case DF_SHORT:
            value_string_size = asprintf(value_string, "SHORT: %d", value.value.df_int);
            break;
        case DF_INTEGER:
            value_string_size = asprintf(value_string, "INTEGER: %d", value.value.df_int);
            break;
        case DF_LONG:
            value_string_size = asprintf(value_string, "LONG: %ld", value.value.df_long);
            break;
        case DF_UNSIGNED_BYTE:
            value_string_size = asprintf(value_string, "UNSIGNED BYTE: %u", value.value.df_unsigned_int);
            break;
        case DF_UNSIGNED_SHORT:
            value_string_size = asprintf(value_string, "UNSIGNED SHORT: %u", value.value.df_unsigned_int);
            break;
        case DF_UNSIGNED_INTEGER:
            value_string_size = asprintf(value_string, "UNSIGNED INTEGER: %u", value.value.df_unsigned_int);
            break;
        case DF_UNSIGNED_LONG:
            value_string_size = asprintf(value_string, "UNSIGNED LONG: %lu", value.value.df_unsigned_long);
            break;
        case DF_DOUBLE:
            value_string_size = asprintf(value_string, "DOUBLE: %f", value.value.df_double);
            break;
        case DF_DATETIME:
            value_string_size = asprintf(value_string, "DOUBLE: %ld", value.value.df_long);
            break;
        case DF_STRING:
            value_string_size = asprintf(value_string, "STRING: %s", value.value.df_string.value);
            break;
        case DF_ARRAY:
            break;
        case DF_LIST:
            break;
        case DF_STREAM:
            break;
        case DF_RECORD:
            break;
        default:
            value_string_size = asprintf(value_string, "UNKNOWN VALUE");
    }
    char *return_string = malloc(value_string_size + 1);
    strcpy(return_string, *value_string);
    return return_string;
}

int deep_copy(const DF_VALUE *src, DF_VALUE *dest) {
    //TODO
    return 0;
}

int deep_delete(DF_VALUE *value) {
    free(value);
    return 1;
}