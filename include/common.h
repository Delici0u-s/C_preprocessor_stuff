#ifndef D_MACROS_COMMON_H
#define D_MACROS_COMMON_H

// #define NO_WARNING_MODS

#if defined(__clang__) && !defined(NO_WARNING_MODS)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wvariadic-macro-arguments-omitted"
#endif

#define STRINGIFY(x) #x
#define STR(x) STRINGIFY(x)

#define EXPAND(x) x

#define _CONCAT_(a, b) a##b
#define _CONCAT(a, b) _CONCAT_(a, b)

#endif
