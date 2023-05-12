#ifndef _LIGHT_UTIL_H
#define _LIGHT_UTIL_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <assert.h>

#include <light_util_compiler.h>

// -- IMPORTANT - PLEASE NOTE --
// by default, we disable all logging and debug features, as these may create
// performance issues or security vulnerabilities if left enabled accidentally
#ifndef RUN_MODE
#define RUN_MODE PRODUCTION
#endif

#define MODE_PRODUCTION         0
#define MODE_TEST               1
#define MODE_DEVELOPMENT        2
#define MODE_DEBUG              3
#define MODE_TRACE              4

#define _GET_RUN_MODE(mode) MODE_## mode
#define GET_RUN_MODE(mode) _GET_RUN_MODE(mode)

#define LIGHT_RUN_MODE GET_RUN_MODE(RUN_MODE)

// production mode means everything is locked down tight,
// for maximum performance and security
#if (LIGHT_RUN_MODE == MODE_PRODUCTION)
#       ifndef FILTER_LOG_LEVEL
#               define FILTER_LOG_LEVEL DISABLE
#       endif
#       ifndef LIGHT_DEBUG_ENABLE
#               define LIGHT_DEBUG_ENABLE 0
#       endif
#       ifndef LIGHT_TRACE_ENABLE
#               define LIGHT_TRACE_ENABLE 0
#       endif
// testing mode means we want t0 report warnings and errors
// while keeping optimization at (hopefully) near-production levels
#elif (LIGHT_RUN_MODE == MODE_TEST)
#       ifndef FILTER_LOG_LEVEL
#               define FILTER_LOG_LEVEL WARN
#       endif
#       ifndef LIGHT_DEBUG_ENABLE
#               define LIGHT_DEBUG_ENABLE 0
#       endif
#       ifndef LIGHT_TRACE_ENABLE
#               define LIGHT_TRACE_ENABLE 0
#       endif
// development mode means we want readable and informative log messages,
// without noisy debug output
#elif (LIGHT_RUN_MODE == MODE_DEVELOPMENT)
#       ifndef FILTER_LOG_LEVEL
#               define FILTER_LOG_LEVEL INFO
#       endif
#       ifndef LIGHT_DEBUG_ENABLE
#               define LIGHT_DEBUG_ENABLE 0
#       endif
#       ifndef LIGHT_TRACE_ENABLE
#               define LIGHT_TRACE_ENABLE 0
#       endif
// debug mode - verbose diagnostic output, and
// enable sanity checking assertions
#elif (LIGHT_RUN_MODE == MODE_DEBUG)
#       ifndef FILTER_LOG_LEVEL
#               define FILTER_LOG_LEVEL DEBUG
#       endif
#       ifndef LIGHT_DEBUG_ENABLE
#               define LIGHT_DEBUG_ENABLE 1
#       endif
#       ifndef LIGHT_TRACE_ENABLE
#               define LIGHT_TRACE_ENABLE 0
#       endif
// trace mode - maximum logging verbosity
#elif (LIGHT_RUN_MODE == MODE_TRACE)
#       ifndef FILTER_LOG_LEVEL
#               define FILTER_LOG_LEVEL TRACE
#       endif
#       ifndef LIGHT_DEBUG_ENABLE
#               define LIGHT_DEBUG_ENABLE 1
#       endif
#       ifndef LIGHT_TRACE_ENABLE
#               define LIGHT_TRACE_ENABLE 1
#       endif
#endif

#define LOG_TRACE 4
#define LOG_DEBUG 3
#define LOG_INFO 2
#define LOG_WARN 1
#define LOG_ERROR 0
#define LOG_DISABLE -1

#define _GET_LOG_LEVEL(level) LOG_## level
#define GET_LOG_LEVEL(level) _GET_LOG_LEVEL(level)

#define LIGHT_MAX_LOG_LEVEL GET_LOG_LEVEL(FILTER_LOG_LEVEL)

#define LIGHT_LOG_BUFFER_SIZE 128


#if (LIGHT_MAX_LOG_LEVEL >= LOG_TRACE)
#define light_trace(format, ...) light_log_internal(LOG_TRACE, __func__, format, __VA_ARGS__)
#else
#define light_trace(format, ...)
#endif
#if (LIGHT_MAX_LOG_LEVEL >= LOG_DEBUG)
#define light_debug(format, ...) light_log_internal(LOG_DEBUG, __func__, format, __VA_ARGS__)
#else
#define light_debug(format, ...)
#endif
#if (LIGHT_MAX_LOG_LEVEL >= LOG_INFO)
#define light_info(format, ...) light_log_internal(LOG_INFO, __func__, format, __VA_ARGS__)
#else
#define light_info(format, ...)
#endif
#if (LIGHT_MAX_LOG_LEVEL >= LOG_WARN)
#define light_warn(format, ...) light_log_internal(LOG_WARN, __func__, format, __VA_ARGS__)
#else
#define light_warn(format, ...)
#endif
#if (LIGHT_MAX_LOG_LEVEL >= LOG_ERROR)
#define light_error(format, ...) light_log_internal(LOG_ERROR, __func__, format, __VA_ARGS__)
#else
#define light_error(format, ...)
#endif
#define light_fatal(format, ...) \
        do { light_log_internal(LOG_ERROR, __func__, format, __VA_ARGS__); panic(format, __VA_ARGS__); } while(0)

// type manipulation macros shamelessly borrowed from the Linux kernel
#define container_of(ptr, type, member) ({                          \
        void *__mptr = (void *)(ptr);                               \
        static_assert(__same_type(*(ptr), ((type *)0)->member) ||   \
                __same_type(*(ptr), void),                          \
                "pointer type mismatch in container_of()");         \
        ((type *)(__mptr - offsetof(type, member))); })

#ifndef __same_type
# define __same_type(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))
#endif

#define LIGHT_OK                        (uint8_t) 0x0u
#define LIGHT_INVALID                   (uint8_t) 0x1u
#define LIGHT_NO_MEMORY                 (uint8_t) 0x2u
#define LIGHT_NO_RESOURCE               (uint8_t) 0x3u

extern void light_util_init();
extern const uint8_t *light_error_to_string(uint8_t level);
extern const uint8_t *light_run_mode_to_string(uint8_t mode);
extern const uint8_t *light_log_level_to_string(uint8_t level);
extern void light_log_internal(const uint8_t level,const uint8_t *func, const uint8_t *format, ...);

// mapped to default malloc/free routines for platform
extern void *light_alloc(size_t size);
extern void light_free(void *obj);

int16_t light_arraylist_indexof(void *list[], uint8_t count, void *item);
void light_arraylist_delete_at_index(void *list[], uint8_t *count, uint8_t index);
void light_arraylist_delete_item(void *list[], uint8_t *count, void *item);
void light_arraylist_append(void *list[], uint8_t *count, void *item);
void light_arraylist_insert(void *list[], uint8_t *count, void *item, uint8_t index);

#endif