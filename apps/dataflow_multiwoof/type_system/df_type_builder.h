//
// Created by lukas on 24.01.2023.
//

#ifndef CSPOT_DF_TYPE_BUILDER_H
#define CSPOT_DF_TYPE_BUILDER_H

#include "df_types.h"

#ifdef __cplusplus
extern "C" {
#endif

DF_VALUE default_df_value();

DF_VALUE *build_boolean(int b);
DF_VALUE *build_byte(char b);
DF_VALUE *build_short(short s);
DF_VALUE *build_integer(int i);
DF_VALUE *build_long(long l);
DF_VALUE *build_unsigned_byte(unsigned char b);
DF_VALUE *build_unsigned_short(unsigned short s);
DF_VALUE *build_unsigned_integer(unsigned int i);
DF_VALUE *build_unsigned_long(unsigned long l);
DF_VALUE *build_double(double d);
DF_VALUE *build_datetime(char *d);

DF_VALUE *build_string(const char *s);
DF_VALUE *build_array(DF_TYPE type, void *array, size_t size);
DF_VALUE *build_list(DF_TYPE type, void *l);
DF_VALUE *build_stream(DF_TYPE type, void *s);
DF_VALUE *build_record();

int get_boolean(DF_VALUE value);
char get_byte(DF_VALUE value);
short get_short(DF_VALUE value);
int get_integer(DF_VALUE value);
long get_long(DF_VALUE value);


#ifdef __cplusplus
}
#endif
#endif // CSPOT_DF_TYPE_BUILDER_H
