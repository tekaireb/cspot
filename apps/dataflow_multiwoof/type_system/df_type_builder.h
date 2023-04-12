//
// Created by lukas on 24.01.2023.
//

#ifndef CSPOT_DF_TYPE_BUILDER_H
#define CSPOT_DF_TYPE_BUILDER_H

#include "df_types.h"

#ifdef __cplusplus
extern "C" {
#endif

void build_boolean(DF_VALUE* value, bool b);
void build_byte(DF_VALUE* value, int8_t b);
void build_short(DF_VALUE* value, int16_t s);
void build_integer(DF_VALUE* value, int32_t i);
void build_long(DF_VALUE* value, int64_t l);
void build_unsigned_byte(DF_VALUE* value, uint8_t b);
void build_unsigned_short(DF_VALUE* value, uint16_t s);
void build_unsigned_integer(DF_VALUE* value, uint32_t i);
void build_unsigned_long(DF_VALUE* value, uint64_t l);
void build_double(DF_VALUE* value, double d);
void build_datetime(DF_VALUE* value, int64_t d);
void build_string(DF_VALUE* value, const char* s);
void build_array(DF_VALUE* value, DF_TYPE type, void* array, size_t size);
void build_list(DF_VALUE* value, DF_TYPE type, ...);


DF_VALUE* value_from_boolean(bool b);
DF_VALUE* value_from_byte(int8_t b);
DF_VALUE* value_from_short(int16_t s);
DF_VALUE* value_from_integer(int32_t i);
DF_VALUE* value_from_long(int64_t l);
DF_VALUE* value_from_unsigned_byte(uint8_t b);
DF_VALUE* value_from_unsigned_short(uint16_t s);
DF_VALUE* value_from_unsigned_integer(uint32_t i);
DF_VALUE* value_from_unsigned_long(uint64_t l);
DF_VALUE* value_from_double(double d);
DF_VALUE* value_from_datetime(int64_t d);
DF_VALUE* value_from_string(const char* s);
DF_VALUE* value_from_array(DF_TYPE type, void* array, size_t size);
DF_VALUE* value_from_list(DF_TYPE type, ...);
DF_VALUE* value_from_stream(DF_TYPE type, void* s);
DF_VALUE* value_from_record();

int get_boolean(const DF_VALUE* value);
char get_byte(const DF_VALUE* value);
short get_short(const DF_VALUE* value);
int get_integer(const DF_VALUE* value);
long get_long(const DF_VALUE* value);
unsigned char get_unsigned_byte(const DF_VALUE* value);
unsigned short get_unsigned_short(const DF_VALUE* value);
unsigned int get_unsigned_integer(const DF_VALUE* value);
unsigned long get_unsigned_long(const DF_VALUE* value);
double get_double(const DF_VALUE* value);
long get_datetime(const DF_VALUE* value);

char* get_string(const DF_VALUE* value);


#ifdef __cplusplus
}
#endif
#endif // CSPOT_DF_TYPE_BUILDER_H
