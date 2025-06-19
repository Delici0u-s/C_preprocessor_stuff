#ifndef GENERIC_TABLE_H
#define GENERIC_TABLE_H

#include <stdio.h>
#include "list.h"
#include "get_arg.h"
#include "common.h"
#include "concat.h"
#include "conditions.h"

void first() { puts("1"); }
void second(int a) { puts("2"); }
void third(int *a) { puts("3"); }
void fourth(char *b) { puts("4"); }
void fifth(int a, int b) { puts("5"); }
void sixt(int a, char b) { puts("6"); }
void seventh(char a, char b) { puts("7"); }

typedef float vec2[2];

// #define EXTRACT_TYPE(input) __typeof__(input)
// #define SAVE_NAME(name) CONCAT(_INTERNAL_D_, name)
// #define CREAT_SAVEP(name, ...) \
//   typedef struct SAVE_NAME(name) { \
//     FOR_EACH(EXPAND, __VA_ARGS__); \
//   } SAVE_NAME(name)

// #define CREATE_FUNC(ret_type, name, ...)                                                                               \
//   CREAT_SAVEP(name, __VA_ARGS__);                                                                                      \
//   ret_type name(__VA_ARGS__)

// clang-format off
#define GENERIC_TYPE_STATEMENT(type, statement) type: statement
// clang-format on

// FN format: (type1, type2, type3, name_of_func)
#define ex(x) EXPAND x

#define GET_TYPE(input) __typeof__(input)
#define GET_TYPE_(input) __typeof__ input
#define GET_ASSOSIATE_TYPES_DEF_NAME(name) CONCAT(name, _types)

#define EXTRACT_TYPES(argl) MAP(GET_TYPE, UNPACK argl)

#define EXTRACT_FN_POS_1(pos, fn) GET_ARG(pos, UNPACK fn)

#define EXTRACT_sFN_POS(pos, fn) (EXTRACT_FN_POS_1(pos, fn), EXTRACT_FN_POS_1(VAR_COUNT(UNPACK fn), fn))

#define GET_FN(name) (EXTRACT_TYPES(MAP(PARENTISIZE, GET_ASSOSIATE_TYPES_DEF_NAME(name))), name)

// #define GENERATE_GENERIC_1(a0, ...) _Generic((a0), MAP(GENERIC_TYPE_STATEMENT_1, __VA_ARGS__))
#define COMBINE_FUNCS_1(a0, ...) _Generic((a0), MAP(GENERIC_TYPE_STATEMENT_1, MAP(GET_FN, __VA_ARGS__)))(a0)

#define CREATE_FUNC(ret_type, name, types) ret_type name(types)
#define ASSOCIATE_TYPES(...) (__VA_ARGS__)

#define foo1_types int
// CREATE_FUNC(void, foo1, (int x, char y))) { puts("foo1"); }
void foo1(int x, char y) { puts("foo1"); }

#define foo2_types void *
// CREATE_FUNC(void, foo2, foo2_types) { puts("foo2"); }
void foo2(void *x) { puts("foo2"); }

#define foo3_types char x
CREATE_FUNC(void, foo3, foo3_types) { puts("foo3"); }

#define joined_1(x) COMBINE_FUNCS_1(x, foo1, foo2, foo3)

// #define FN(name, ...) (name, __VA_ARGS__)
// #define GRAB_TYPE(fn, pos) GET_ARG(pos, CALL_BRACE(UNPACK, fn))

// #define TO_GENERIC_STATEMENT_1_(name, type)                                                                            \
//   type:                                                                                                                \
//   name

// #define TO_GENERIC_STATEMENT_1(uin) TO_GENERIC_STATEMENT_1_ uin

// #define CREATE_GENERIC_1(a0, ...) _Generic((a0), MAP(TO_GENERIC_STATEMENT_1, __VA_ARGS__))

// #define COMBINE_FUNCS_1(a0, ...) CREATE_GENERIC_1(a0, __VA_ARGS__)(a0)

// #define bla(a0) COMBINE_FUNCS_1(a0, FN(second, int), FN(third, int *), FN(fourth, char *))

// Extractors

// #define bla2(a0, a1) COMBINE_FUNCS_2(a0, a1, FN(fifth, int, int), FN(sixt, int, char), FN(seventh, char, char))

// bla(1);

// Example function
// int add(int a, int b);

// #define bla(a0) GENERIC_TABLE_1((a0), CONVERT(second), (int *, third), (char *, fourth))
// #define bla(a0) GENERIC_TABLE_1((a0), (int, second), (int *, third), (char *, fourth))
// #define kekw(func) (func) __FUNC__

void foo() {
  //
  // foo2(1, (void *)1, 3);
  // TEST(())

  // MASK_FN(foo2)
  int te = 2;
  EXTRACT_FN_POS_1(1, GET_FN(foo1)) x = te;
  // MAP(GENERIC_TYPE_STATEMENT_1, foo2_types)
  // bla(1)
  printf("%d\n", x);

  //
}

#endif /* GENERIC_TABLE_H */
