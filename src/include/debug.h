#ifndef CSPOT_DEBUG_H
#define CSPOT_DEBUG_H

#if defined(__cplusplus)
extern "C" {
#endif

void cspot_print_debug(const char* format, ...);
void cspot_print_fatal(const char* format, ...) __attribute__((noreturn));
void cspot_print_fatal_if(bool val, const char* format, ...);

#undef DEBUG
#ifdef DEBUG
#define DEBUG_LOG(...) cspot_print_debug(__VA_ARGS__)
#define DEBUG_WARN(...) cspot_print_debug(__VA_ARGS__)
#define DEBUG_FATAL(...) cspot_print_fatal(__VA_ARGS__)
#define DEBUG_FATAL_IF(cond, ...) cspot_print_fatal_if(cond, __VA_ARGS__)
#else
#define DEBUG_LOG(...) do { } while (false)
#define DEBUG_WARN(...) do { } while (false)
#define DEBUG_FATAL(...) do { } while (false)
#define DEBUG_FATAL_IF(cond, ...) do { } while (false)

#endif

#if defined(__cplusplus)
}
#endif

#endif