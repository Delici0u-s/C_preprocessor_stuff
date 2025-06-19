#ifndef D_MACROS_COMMON_H
#define D_MACROS_COMMON_H

// #define NO_WARNING_MODS

#if defined(__clang__) && !defined(NO_WARNING_MODS)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wvariadic-macro-arguments-omitted"
#endif
#if defined(_MSC_VER)
#error D_MACROS MIGHT NOT WORK
#endif

#define STRINGIFY(x) #x
#define STR(x) STRINGIFY(x)

#define EXPAND(x) x
#define PARENTISIZE(x) (x)
#define CALL_BRACE(f, x) f x

#define _CONCAT_(a, b) a##b
#define _CONCAT(a, b) _CONCAT_(a, b)

#define GET_TYPE(x) __typeof__(x)
#define GET_TYPE_(x) __typeof__ x

#endif
