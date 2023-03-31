//
// Created by lukas on 20.03.2023.
//

#ifndef CSPOT_DF_ARITHMETIC_H
#define CSPOT_DF_ARITHMETIC_H

#include "../type_system/df_types.h"
#include "df_operations.h"


int df_arithmetic_operation(DF_ARITHMETIC_OP arithmetic_operation,
                            const DF_VALUE operands[],
                            unsigned int operand_count,
                            DF_VALUE* result);

int df_arithmetic_operation_with_type(DF_ARITHMETIC_OP arithmetic_operation,
                                      const DF_VALUE operands[],
                                      unsigned int operand_count,
                                      DF_TYPE result_type,
                                      DF_VALUE* result);

#endif // CSPOT_DF_ARITHMETIC_H
