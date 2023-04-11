//
// Created by lukas on 11.04.2023.
//

#ifndef CSPOT_DF_CAST_H
#define CSPOT_DF_CAST_H

#include "../type_system/df_types.h"
#include "df_operations.h"

#ifdef __cplusplus
extern "C" {
#endif

int df_cast_operation(DF_CAST_OP cast_operation,
                      const DF_VALUE operands[],
                      unsigned int operand_count,
                      DF_VALUE* result);

#ifdef __cplusplus
}
#endif

#endif // CSPOT_DF_CAST_H
