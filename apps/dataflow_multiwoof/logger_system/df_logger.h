//
// Created by lukas on 03.01.2023.
//

#ifndef CSPOT_DFDEBUG_H
#define CSPOT_DFDEBUG_H

#include "../type_system/df_type.h"

enum LOG_LEVELS
{
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR
};

#ifdef __cplusplus
extern "C" {
#endif

void log_trace(const char* message, ...);
void log_debug(const char* message, ...);
void log_info(const char* message, ...);
void log_warn(const char* message, ...);
void log_error(const char* message, ...);

char* value_as_string(const DF_VALUE* value);
char* values_as_string(const DF_VALUE values[], unsigned int value_count);

#ifdef __cplusplus
}
#endif

#endif // CSPOT_DFDEBUG_H
