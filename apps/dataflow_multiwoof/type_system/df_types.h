//
// Created by Lukas Brand on 29.03.23.
//

#ifndef CSPOT_DF_TYPES_H
#define CSPOT_DF_TYPES_H

#include <stdio.h>
#include <uuid/uuid.h>

enum df_types_enum
{
    DF_UNKNOWN = 0,

    // Simple Types
    DF_BOOLEAN = 1,
    DF_BYTE = 10,
    DF_SHORT = 11,
    DF_INTEGER = 12,
    DF_LONG = 13,
    DF_UNSIGNED_BYTE = 20,
    DF_UNSIGNED_SHORT = 21,
    DF_UNSIGNED_INTEGER = 22,
    DF_UNSIGNED_LONG = 23,
    DF_DOUBLE = 30,
    DF_DATETIME,

    // Compound Types
    DF_STRING,
    DF_ARRAY,
    DF_LIST,
    DF_STREAM,
    DF_RECORD,
    // TODO
};
typedef enum df_types_enum DF_TYPE;


struct df_storage_system {
    uuid_t id;
};
typedef struct df_storage_system DF_STORAGE_SYSTEM;

/* **************** STRING **************** */
struct df_value_string {
    struct df_storage_system storage_system;
    const char* value;
};
typedef struct df_value_string DF_VALUE_STRING;

/* **************** ARRAY **************** */
struct df_value_array {
    struct df_storage_system storage_system;
    size_t size;
    enum df_types_enum type;
    const void* value;
};
typedef struct df_value_array DF_VALUE_ARRAY;


/* **************** RECORD **************** */
struct df_record_element {
    char identifier[21];
    enum df_types_enum type;
    struct df_types_struct* value;
};
typedef struct df_record_element DF_RECORD_ELEMENTS;

struct df_value_record {
    struct df_storage_system storage_system;
    struct df_record_element element;
};
typedef struct df_value_record DF_VALUE_RECORD;


/* **************** NODE VALUE **************** */
union df_values_union {
    unsigned int df_unsigned_int;
    unsigned long df_unsigned_long;
    int df_int;
    long df_long;
    double df_double;
    struct df_value_string df_string;
    struct df_value_array df_array;
    struct df_value_array df_list;   // TODO
    struct df_value_array df_stream; // TODO
    struct df_value_record df_record;
};
typedef union df_values_union DF_TYPE_VALUE;

struct df_types_struct {
    union df_values_union value;
    enum df_types_enum type;
};
typedef struct df_types_struct DF_VALUE;


#ifdef __cplusplus
extern "C" {
#endif

char* type_to_string(DF_TYPE type);
char* value_to_string(const DF_VALUE* value);


int deep_copy(const DF_VALUE* src, DF_VALUE* dest);
int deep_delete(DF_VALUE* value);

#ifdef __cplusplus
}
#endif

#endif // CSPOT_DF_TYPES_H
