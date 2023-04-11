//
// Created by lukas on 09.01.2023.
//
#ifndef CSPOT_DF_TYPE_H
#define CSPOT_DF_TYPE_H

#include "../woofc.h"
#include "df_types.h"

#ifdef __cplusplus
extern "C" {
#endif

unsigned long write_value(const DF_VALUE* value);

unsigned long write_value_woof(const char* woof, const DF_VALUE* value);

unsigned long read_value(DF_VALUE* value);

unsigned long read_value_woof(const char* woof, unsigned long sequence_number, DF_VALUE* value);

int is_primitive(const DF_VALUE* value);

int is_number(const DF_VALUE* value);

#ifdef __cplusplus
}
#endif

#endif // CSPOT_DF_TYPE_H
