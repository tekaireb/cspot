//
// Created by Lukas Brand Privat on 30.03.23.
//
#include "df_types.h"

#include <stdlib.h>
#include <string.h>

char* type_to_string(const DF_TYPE type) {
    char* string;
    switch (type) {
        case DF_UNKNOWN: {
            char* temp_string = "UNKNOWN";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        } break;
        case DF_BOOLEAN: {
            char* temp_string = "BOOLEAN";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        } break;
        case DF_BYTE: {
            char* temp_string = "BYTE";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        } break;
        case DF_SHORT: {
            char* temp_string = "SHORT";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        } break;
        case DF_INTEGER: {
            char* temp_string = "INTEGER";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        } break;
        case DF_LONG: {
            char* temp_string = "LONG";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        } break;
        case DF_UNSIGNED_BYTE: {
            char* temp_string = "UNSIGNED BYTE";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        } break;
        case DF_UNSIGNED_SHORT: {
            char* temp_string = "UNSIGNED SHORT";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        } break;
        case DF_UNSIGNED_INTEGER: {
            char* temp_string = "UNSIGNED INTEGER";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        } break;
        case DF_UNSIGNED_LONG: {
            char* temp_string = "UNSIGNED LONG";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        } break;
        case DF_DOUBLE: {
            char* temp_string = "DOUBLE";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        } break;
        case DF_DATETIME: {
            char* temp_string = "DATETIME";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        } break;
        case DF_STRING: {
            char* temp_string = "STRING";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        } break;
        case DF_ARRAY: {
            char* temp_string = "ARRAY";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        } break;
        case DF_LIST: {
            char* temp_string = "LIST";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        } break;
        case DF_STREAM: {
            char* temp_string = "STREAM";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        } break;
        case DF_RECORD: {
            char* temp_string = "RECORD";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        } break;
        default: {
            char* temp_string = "UNRECOGNIZED TYPE";
            string = malloc(sizeof(strlen(temp_string)) + 1);
            strcpy(string, temp_string);
        }
    }
    return string;
}

char* value_to_string(const DF_VALUE* value) {
    char* value_string = NULL;
    size_t value_string_size = 0;
    switch (value->type) {
        case DF_UNKNOWN: {
            value_string_size = snprintf(NULL, 0, "UNKNOWN: UNKNOWN VALUE");
            value_string = malloc(value_string_size + 1);
            const int ret = snprintf(value_string, value_string_size + 1, "UNKNOWN: UNKNOWN VALUE");
            if (ret < 0 || ret > value_string_size) {
                free(value_string);
                return NULL;
            }
            break;
        }
        case DF_BOOLEAN: {
            value_string_size = snprintf(NULL, 0, "BOOLEAN: %d", value->value.df_int);
            value_string = malloc(value_string_size + 1);
            const int ret = snprintf(value_string, value_string_size + 1, "BOOLEAN: %d", value->value.df_int);
            if (ret < 0 || ret > value_string_size) {
                free(value_string);
                return NULL;
            }
            break;
        }
        case DF_BYTE: {
            value_string_size = snprintf(NULL, 0, "BYTE: %d", value->value.df_int);
            value_string = malloc(value_string_size + 1);
            const int ret = snprintf(value_string, value_string_size + 1, "BYTE: %d", value->value.df_int);
            if (ret < 0 || ret > value_string_size) {
                free(value_string);
                return NULL;
            }
            break;
        }
        case DF_SHORT: {
            value_string_size = snprintf(NULL, 0, "SHORT: %d", value->value.df_int);
            value_string = malloc(value_string_size + 1);
            const int ret = snprintf(value_string, value_string_size + 1, "SHORT: %d", value->value.df_int);
            if (ret < 0 || ret > value_string_size) {
                free(value_string);
                return NULL;
            }
            break;
        }
        case DF_INTEGER: {
            value_string_size = snprintf(NULL, 0, "INTEGER: %d", value->value.df_int);
            value_string = malloc(value_string_size + 1);
            const int ret = snprintf(value_string, value_string_size + 1, "INTEGER: %d", value->value.df_int);
            if (ret < 0 || ret > value_string_size) {
                free(value_string);
                return NULL;
            }
            break;
        }
        case DF_LONG: {
            value_string_size = snprintf(NULL, 0, "LONG: %ld", value->value.df_long);
            value_string = malloc(value_string_size + 1);
            const int ret = snprintf(value_string, value_string_size + 1, "LONG: %ld", value->value.df_long);
            if (ret < 0 || ret > value_string_size) {
                free(value_string);
                return NULL;
            }
            break;
        }
        case DF_UNSIGNED_BYTE: {
            value_string_size = snprintf(NULL, 0, "UNSIGNED BYTE: %u", value->value.df_unsigned_int);
            value_string = malloc(value_string_size + 1);
            const int ret =
                snprintf(value_string, value_string_size + 1, "UNSIGNED BYTE: %u", value->value.df_unsigned_int);
            if (ret < 0 || ret > value_string_size) {
                free(value_string);
                return NULL;
            }
            break;
        }
        case DF_UNSIGNED_SHORT: {
            value_string_size = snprintf(NULL, 0, "UNSIGNED SHORT: %u", value->value.df_unsigned_int);
            value_string = malloc(value_string_size + 1);
            const int ret =
                snprintf(value_string, value_string_size + 1, "UNSIGNED SHORT: %u", value->value.df_unsigned_int);
            if (ret < 0 || ret > value_string_size) {
                free(value_string);
                return NULL;
            }
            break;
        }
        case DF_UNSIGNED_INTEGER: {
            value_string_size = snprintf(NULL, 0, "UNSIGNED INTEGER: %u", value->value.df_unsigned_int);
            value_string = malloc(value_string_size + 1);
            const int ret =
                snprintf(value_string, value_string_size + 1, "UNSIGNED INTEGER: %u", value->value.df_unsigned_int);
            if (ret < 0 || ret > value_string_size) {
                free(value_string);
                return NULL;
            }
            break;
        }
        case DF_UNSIGNED_LONG: {
            value_string_size = snprintf(NULL, 0, "UNSIGNED LONG: %lu", value->value.df_unsigned_long);
            value_string = malloc(value_string_size + 1);
            const int ret =
                snprintf(value_string, value_string_size + 1, "UNSIGNED LONG: %lu", value->value.df_unsigned_long);
            if (ret < 0 || ret > value_string_size) {
                free(value_string);
                return NULL;
            }
            break;
        }
        case DF_DOUBLE: {
            value_string_size = snprintf(NULL, 0, "DOUBLE: %f", value->value.df_double);
            value_string = malloc(value_string_size + 1);
            const int ret = snprintf(value_string, value_string_size + 1, "DOUBLE: %f", value->value.df_double);
            if (ret < 0 || ret > value_string_size) {
                free(value_string);
                return NULL;
            }
            break;
        }
        case DF_DATETIME: {
            value_string_size = snprintf(NULL, 0, "DOUBLE: %ld", value->value.df_long);
            value_string = malloc(value_string_size + 1);
            const int ret = snprintf(value_string, value_string_size + 1, "DOUBLE: %ld", value->value.df_long);
            if (ret < 0 || ret > value_string_size) {
                free(value_string);
                return NULL;
            }
            break;
        }
        case DF_STRING: {
            value_string_size = snprintf(NULL, 0, "STRING: %s", value->value.df_string.value);
            value_string = malloc(value_string_size + 1);
            const int ret = snprintf(value_string, value_string_size + 1, "STRING: %s", value->value.df_string.value);
            if (ret < 0 || ret > value_string_size) {
                free(value_string);
                return NULL;
            }
            break;
        }
        case DF_ARRAY:
            // TODO
            break;
        case DF_LIST:
            // TODO
            break;
        case DF_STREAM:
            // TODO
            break;
        case DF_RECORD:
            // TODO
            break;
        default: {
            value_string_size = snprintf(NULL, 0, "UNKNOWN VALUE");
            value_string = malloc(value_string_size + 1);
            const int ret = snprintf(value_string, value_string_size + 1, "UNKNOWN VALUE");
            if (ret < 0 || ret > value_string_size) {
                free(value_string);
                return NULL;
            }
            break;
        }
    }
    return value_string;
}

int deep_copy(const DF_VALUE* src, DF_VALUE* dest) {
    dest->type = src->type;
    switch (src->type) {
        case DF_BOOLEAN:
        case DF_BYTE:
        case DF_SHORT:
        case DF_INTEGER:
            dest->value.df_int = src->value.df_int;
            break;
        case DF_LONG:
            dest->value.df_long = src->value.df_long;
            break;
        case DF_UNSIGNED_BYTE:
        case DF_UNSIGNED_SHORT:
        case DF_UNSIGNED_INTEGER:
            dest->value.df_unsigned_int = src->value.df_unsigned_int;
            break;
        case DF_UNSIGNED_LONG:
            dest->value.df_unsigned_long = src->value.df_unsigned_long;
            break;
        case DF_DOUBLE:
            dest->value.df_double = src->value.df_double;
            break;
        case DF_DATETIME:
            dest->value.df_unsigned_long = src->value.df_unsigned_long;
            break;
        case DF_STRING:
            // TODO
        case DF_ARRAY:
            // TODO
        case DF_LIST:
            // TODO
        case DF_STREAM:
            // TODO
        case DF_RECORD:
            // TODO
        default:
            return 0;
    }
    return 1;
}

int deep_delete(DF_VALUE* value) {
    // TODO
    free(value);
    return 1;
}