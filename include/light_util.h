#ifndef _LIGHT_UTIL_H
#define _LIGHT_UTIL_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#define LIGHT_OK                        (uint8_t) 0x0u
#define LIGHT_INVALID                   (uint8_t) 0x1u
#define LIGHT_NO_MEMORY                 (uint8_t) 0x2u
#define LIGHT_NO_RESOURCE               (uint8_t) 0x3u

extern const uint8_t *light_error_to_string(uint8_t level);

// by default, compile in only INFO level messages and above
#ifndef FILTER_LOG_LEVEL
#       define FILTER_LOG_LEVEL INFO
#endif

#define LOG_TRACE 4
#define LOG_DEBUG 3
#define LOG_INFO 2
#define LOG_WARN 1
#define LOG_ERROR 0

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

extern void light_util_init();
extern const uint8_t *light_log_level_to_string(uint8_t level);
extern void light_log_internal(const uint8_t level,const uint8_t *func, const uint8_t *format, ...);

#endif