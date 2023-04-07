//
// Created by lukas on 09.01.2023.
//
#ifndef CSPOT_DF_OPERATION_H
#define CSPOT_DF_OPERATION_H

#include "../type_system/df_types.h"
#include "df_operations.h"

#ifdef __cplusplus
extern "C" {
#endif

struct df_operation_metadata {};
typedef struct df_operation_metadata DF_OPERATION_METADATA;


/*
int df_operation(DF_OPERATION operation,
                 const DF_VALUE operands[],
                 unsigned int operand_count,
                 DF_VALUE *result);
*/

int df_operation_with_type(DF_OPERATION operation,
                           const DF_VALUE operands[],
                           unsigned int operand_count,
                           DF_TYPE result_type,
                           DF_VALUE* result);

#ifdef __cplusplus
}
#endif

#endif // CSPOT_DF_OPERATION_H
