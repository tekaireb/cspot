//
// Created by lukas on 20.03.2023.
//

#ifndef CSPOT_DF_MACHINE_LEARNING_H
#define CSPOT_DF_MACHINE_LEARNING_H

#include "../type_system/df_types.h"
#include "df_operations.h"

#ifdef __cplusplus
extern "C" {
#endif

int df_machine_learning_operation(DF_MACHINE_LEARNING_OP machine_learning_operation,
                                  const DF_VALUE operands[],
                                  unsigned int operand_count,
                                  DF_VALUE *result);

int df_machine_learning_operation_with_type(DF_MACHINE_LEARNING_OP machine_learning_operation,
                                            const DF_VALUE operands[],
                                            unsigned int operand_count,
                                            DF_TYPE result_type,
                                            DF_VALUE *result);

#ifdef __cplusplus
}
#endif
#endif // CSPOT_DF_MACHINE_LEARNING_H
