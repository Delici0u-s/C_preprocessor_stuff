#ifndef GENERIC_TABLE_H
#define GENERIC_TABLE_H

#include <stdio.h>
#include "list.h"
#include "get_arg.h"
#include "common.h"
#include "concat.h"
#include "conditions.h"
#include "REM_F.h"

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

///////////// INTERFACE ///////////////
#define VAR_LIST(...) __VA_ARGS__
#define VAR(type, name) (type, name)

#define CREATE_FUNC(retType, name) retType name(EXTRACT_TYPES(GET_TYPE_NAME(name)))
//////////////////////////////////////

#define foo1_types VAR_LIST(VAR(int, x))
CREATE_FUNC(void, foo1) { printf("foo1: %d", x); }

#define foo2_types VAR_LIST(VAR(char, x))
CREATE_FUNC(void, foo2) { printf("foo2: %c", x); }

#define foo3_types VAR_LIST(VAR(void *, x), VAR(int, z))
CREATE_FUNC(void, foo3) { printf("foo3: %p, %d", x, z); }

void foo() { //
  foo1(2);
}

#endif /* GENERIC_TABLE_H */
