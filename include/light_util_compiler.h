#ifndef _LIGHT_UTIL_COMPILER_H
#define _LIGHT_UTIL_COMPILER_H

#ifdef _Static_assert
#define static_assert(cond, msg) static_assert(cond, msg)
#else
// TODO provide an implementation of static_assert for non-C11 programs
#endif

#endif
