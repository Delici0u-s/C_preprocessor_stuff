#ifndef MACRO_GENERIC_TABLE_H
#define MACRO_GENERIC_TABLE_H

#include <stdio.h>
#include "conditions.h"
#include "has_n_args.h"
#include "list.h"
#include "get_arg.h"
#include "common.h"
#include "concat.h"
#include "REM_F.h"
#include "append_arg.h"
// #include "PPLISP.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void first() { puts("1"); }
void second(int a) { puts("2"); }
void third(int *a) { puts("3"); }
void fourth(char *b) { puts("4"); }
void fifth(int a, int b) { puts("5"); }
void sixt(int a, char b) { puts("6"); }
void seventh(char a, char b) { puts("7"); }
#pragma GCC diagnostic pop

#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
#error "This code requires at least C11. Please use a C11-compliant compiler with -std=c11 or later."
#endif

#define VAR_E_(type, name) type name
#define VAR_E(VAR_) VAR_E_ VAR_
#define VAR_T_(type, name) type
#define VAR_T(VAR_) VAR_T_ VAR_

#define GET_TYPE_NAME(name) CONCAT(name, _types)

#define EXTRACT_TYPES(list) MAP(VAR_E, list)     // int x, int y, char z
#define EXTRACT_TYPE_LIST(list) MAP(VAR_T, list) // int, int, char

#define FN_GEN_LIST(name) (EXTRACT_TYPE_LIST(GET_TYPE_NAME(name)), name)
#define FN_REDUCE(fn) (REMF fn)
#define FN_REDUCE_LIST(...) _CONCAT(_LISTF_, VAR_COUNT(__VA_ARGS__))(COMMA(), FN_REDUCE, __VA_ARGS__)
#define FN_GET_TYPE(fn) GET_ARG(1, UNPACK fn)
#define FN_GET_TYPE_LAST(fn) (GET_ARG(1, UNPACK fn), GET_ARG(VAR_COUNT(UNPACK fn), UNPACK fn))
#define FN_GEN_LIST_ON_NAMES(...)                                                                                      \
  IF_ELSE(HAS_N_ARGS(2, __VA_ARGS__),                                                                                  \
          ((MAP(VAR_T, GET_TYPE_NAME(GET_ARG(1, __VA_ARGS__))), GET_ARG(1, __VA_ARGS__)),                              \
           (MAP(VAR_T, GET_TYPE_NAME(GET_ARG(2, __VA_ARGS__))), GET_ARG(2, __VA_ARGS__))),                             \
          (_CONCAT(_LISTF_, VAR_COUNT(__VA_ARGS__))(COMMA(), FN_GEN_LIST, __VA_ARGS__)))

#define GEN_GENERIC_CALL(type, call)                                                                                   \
  type:                                                                                                                \
  call
#define GEN_GENERIC_CALL_(arg) GEN_GENERIC_CALL arg

#define GENERATE_VAR_LIST_0(func) func()

// expects fn list
#define _GENERATE_VAR_LIST_n(a0, ...) _Generic((a0), MAP(GEN_GENERIC_CALL_, MAP(FN_GET_TYPE_LAST, __VA_ARGS__)))(a0)

// expects function name list
#define _GENERATE_VAR_LIST_1_(a0, ...) _GENERATE_VAR_LIST_n(a0, STRIP_PARENS(__VA_ARGS__))
#define GENERATE_VAR_LIST_1(a0, ...) _GENERATE_VAR_LIST_1_(a0, FN_GEN_LIST_ON_NAMES(__VA_ARGS__))

// needs to combine VA_ARG_LIST based on type, so all same type1 call _GEN_VAR_LIST_1_ for type2
#define _GENERATE_VAR_LIST_2_(a0, a1, ...)                                                                             \
  _GENERATE_VAR_LIST_n(a0, MAP(_GENERATE_VAR_LIST_1_, AP_ARG(a1, MAP(FN_REDUCE, __VA_ARGS__))))
#define GENERATE_VAR_LIST_2(a0, a1, ...) _GENERATE_VAR_LIST_2_(a0, a1, FN_GEN_LIST_ON_NAMES(__VA_ARGS__))

///////////// INTERFACE ///////////////
#define VAR_LIST(...) __VA_ARGS__
#define VAR(type, name) (type, name)

#define CREATE_FUNC(retType, name) retType name(EXTRACT_TYPES(GET_TYPE_NAME(name)))
//////////////////////////////////////

#define foo1_types VAR_LIST(VAR(int, x), VAR(int, y))
CREATE_FUNC(void, foo1) { printf("foo1: %d, %d\n", x, y); }

#define foo2_types VAR_LIST(VAR(int, x), VAR(char, y))
CREATE_FUNC(void, foo2) { printf("foo2: %d, %c\n", x, y); }

#define foo3_types VAR_LIST(VAR(char, x), VAR(int, y))
CREATE_FUNC(void, foo3) { printf("foo3: %c, %d\n", x, y); }

#define foo4_types VAR_LIST(VAR(char, x), VAR(char, y))
CREATE_FUNC(void, foo4) { printf("foo4: %c, %c\n", x, y); }

#define joined(a0, a1) GENERATE_VAR_LIST_2(a0, a1, foo1, foo2, foo3, foo4)

// #define foo1_types VAR_LIST(VAR(int, x))
// CREATE_FUNC(void, foo1) { printf("foo1: %d\n", x); }

// #define foo2_types VAR_LIST(VAR(char, x))
// CREATE_FUNC(void, foo2) { printf("foo2: %c\n", x); }

// #define foo3_types VAR_LIST(VAR(void *, x))
// CREATE_FUNC(void, foo3) { printf("foo3: %p, %d\n", x, *(int *)x); }

// typedef struct {
//   float x, y;
// } vec2;
// #define foo4_types VAR_LIST(VAR(vec2, x))
// CREATE_FUNC(void, foo4) { printf("foo4: %f, %f\n", x.x, x.y); }

// #define joined(a0) GENERATE_VAR_LIST_1(a0, foo1, foo2, foo3, foo4)

// TODO: IMPLEMENT TYPE BREAK MAKERS, like to tell when which function input type changes
// Usage:
void foo() { //
  puts("Hi");
}

#endif /* GENERIC_TABLE_H */
