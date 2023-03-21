//
// Created by lukas on 20.03.2023.
//

#ifndef CSPOT_DF_MACHINE_LEARNING_H
#define CSPOT_DF_MACHINE_LEARNING_H

#include "../type_system/dftype.h"

enum df_machine_learnings_enum
{
    DF_MACHINE_LEARNING_KNN,
    DF_MACHINE_LEARNING_LINREG,
};
typedef enum df_machine_learnings_enum DF_MACHINE_LEARNING;

int df_machine_learning_operation(DF_MACHINE_LEARNING machine_learning_operation,
                                  const DF_VALUE values[],
                                  unsigned int value_count,
                                  DF_VALUE* return_value);

int df_machine_learning_operation_with_type(DF_MACHINE_LEARNING machine_learning_operation,
                                            DF_TYPE operation_type,
                                            const DF_VALUE values[],
                                            unsigned int value_count,
                                            DF_VALUE* return_value);

#endif // CSPOT_DF_MACHINE_LEARNING_H
