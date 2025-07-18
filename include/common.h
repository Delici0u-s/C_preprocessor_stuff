#ifndef D_MACROS_COMMON_H
#define D_MACROS_COMMON_H

// #define NO_WARNING_MODS

// #if defined(__clang__) && !defined(NO_WARNING_MODS)
// #pragma clang diagnostic push
// #pragma clang diagnostic ignored "-Wvariadic-macro-arguments-omitted"
// #endif
#if defined(_MSC_VER)
#error D_MACROS MIGHT NOT WORK
#endif

#define STRINGIFY(x) #x
#define STR(x) STRINGIFY(x)

#define EXPAND(...) __VA_ARGS__
#define PARENTISIZE(...) (__VA_ARGS__)
#define STRIP_PARENS(x) _STRIP_PARENS_ x
#define _STRIP_PARENS_(...) __VA_ARGS__
#define CALL_BRACE(f, x) f x
#define VOID(...)
#define AP_COMMA(...) __VA_ARGS__,
#define IS_COMMA(...) , __VA_ARGS__

#define _CONCAT_(a, b) a##b
#define _CONCAT(a, b) _CONCAT_(a, b)

#define GET_TYPE(x) __typeof__(x)
#define GET_TYPE_(x) __typeof__ x

#define SWAP(arg1, arg2) arg2, arg1
#define SWAP_(packet) SWAP packet
#define _SWAP_(packet) (SWAP packet)

// Force macro evaluation
#define _EVAL(a0) EXPAND a0
#define EVAL(...) _EVAL((__VA_ARGS__))

#endif
