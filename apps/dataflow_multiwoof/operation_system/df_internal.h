//
// Created by lukas on 20.03.2023.
//

#ifndef CSPOT_DF_INTERNAL_H
#define CSPOT_DF_INTERNAL_H

#include "../type_system/df_types.h"
#include "df_operations.h"

int df_internal_operation(DF_INTERNAL_OP internal_operation,
                          const DF_VALUE operands[],
                          unsigned int operand_count,
                          DF_VALUE* result);

int df_internal_operation_with_type(DF_INTERNAL_OP internal_operation,
                                    const DF_VALUE operands[],
                                    unsigned int operand_count,
                                    DF_TYPE result_type,
                                    DF_VALUE* result);

#endif // CSPOT_DF_INTERNAL_H
