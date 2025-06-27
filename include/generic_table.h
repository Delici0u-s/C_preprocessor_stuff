#ifndef MACRO_GENERIC_TABLE_H
#define MACRO_GENERIC_TABLE_H

#include "stdio.h"

#include "common.h"
#include "typeID.h"
#include "list.h"
#include "get_arg.h"
#include "REM_F.h"
#include "var_count.h"
#include "conditions.h"
#include "num_cmp.h"
#include "append_arg.h"

#define FUNCTION_PARAM_SUFFIX _types

#define P(typeID, name) (typeID, name) // Function Parameter argument
#define SET_PARAMETERS(...) (__VA_ARGS__)

#define CREATE_FUNC(_ret_type, _name)                                                                                  \
  _ret_type _name(MAP(PARAM_EXTRACT, STRIP_PARENS(_CONCAT(_name, FUNCTION_PARAM_SUFFIX))))

#define PARAM_EXTRACT_(param) GET_ARG(2, STRIP_PARENS(GET_ARG(1, param))) GET_ARG(2, param)
#define PARAM_EXTRACT(param) PARAM_EXTRACT_(STRIP_PARENS(param)) // (TYPEID, varname) == ((0, int), x) -> int x
#define PARAM_EXTRACT_ID(param) GET_ARG(1, STRIP_PARENS(param))

// Fn structure: (ID1, ID2, ID3, IDn, function_name)
#define _FN_CREATE(...) _CONCAT(_LISTF_, VAR_COUNT(__VA_ARGS__))(COMMA(), PARAM_EXTRACT_ID, __VA_ARGS__)
#define FN_CREATE(func_name) (_FN_CREATE(STRIP_PARENS(_CONCAT(func_name, FUNCTION_PARAM_SUFFIX))), func_name)

#define FN_REDUCE(fn) (REM_F(STRIP_PARENS(fn)))
#define FN_GET_LAST_TYPE(fn) GET_ARG(2, STRIP_PARENS(GET_ARG(1, STRIP_PARENS(fn))))
#define FN_GET_LAST_TYPE_ID(fn) GET_ARG(1, STRIP_PARENS(GET_ARG(1, STRIP_PARENS(fn))))
#define FN_CREATE_LIST(...) _CONCAT(_LISTF_, VAR_COUNT(__VA_ARGS__))(COMMA(), FN_CREATE, __VA_ARGS__)
// #define FN_CREATE_LIST(...) MAP(FN_CREATE, __VA_ARGS__)

// #define FN_TO_GEN_CALL(fn, next) FN_GET_LAST_TYPE(fn) : next
#define FN_TO_GEN_CALL(fn, next) GET_ARG(2, STRIP_PARENS(GET_ARG(1, fn))) : next
#define FN_END_TO_GEN_CALL(fn) FN_GET_LAST_TYPE(fn) : STRIP_PARENS(FN_REDUCE(fn))

#define FN_SAME_TYPE(fn1, fn2) SAME_NUM(FN_GET_LAST_TYPE_ID(fn1), FN_GET_LAST_TYPE_ID(fn2))
#define _cond_keep_FN_SAME_TYPE(fn1, fn2) IF_ELSE(FN_SAME_TYPE(fn1, fn2), fn2, )
#define _cond_keep_FN_SAME_TYPE_(arg) _cond_keep_FN_SAME_TYPE arg
// #define FN_KEEP_LIST(fn1, ...) MAP(_cond_keep_FN_SAME_TYPE, AP_ARG(fn1, __VA_ARGS__))

// #define FN_SAME_TYPE(fn1, fn2) IF_ELSE(SAME_NUM(FN_GET_LAST_TYPE_ID(fn1), FN_GET_LAST_TYPE_ID(fn2)), true, false)

// __VA_ARGS__ should be GENERIC_CALLS
#define _GENERATE_VAR_LIST_n(a0, ...) _Generic((a0), __VA_ARGS__)

#define GENERATE_FUNC_LIST_0(function) function

// With fn list
#define _GENERATE_VAR_LIST_1(a0, ...) _GENERATE_VAR_LIST_n(a0, MAP(FN_END_TO_GEN_CALL, __VA_ARGS__))
// With fundtion names
#define GENERATE_VAR_LIST_1(a0, ...) _GENERATE_VAR_LIST_1(a0, FN_CREATE_LIST(__VA_ARGS__))

#define foo_types SET_PARAMETERS(P(ID_int_p, x))
CREATE_FUNC(void, foo) { ++*x; }

#define foo2_types SET_PARAMETERS(P(ID_float_p, x))
CREATE_FUNC(void, foo2) { ++*x; }

#define foo3_types SET_PARAMETERS(P(ID_char_p, x))
CREATE_FUNC(void, foo3) { ++*x; }

#define bar_types SET_PARAMETERS(P(ID_int, x), P(ID_float_p, f))
CREATE_FUNC(float, bar) { return x * *f; }

#define baz_types SET_PARAMETERS(P(ID_int, x), P(ID_float_p, f), P(ID_float, k))
CREATE_FUNC(float, baz) { return (*f *= x) + k; }

#define test(a0) GENERATE_VAR_LIST_1(a0, foo, foo2, foo3)(a0)

#define test1_types SET_PARAMETERS(P(ID_int, x))
#define test2_types SET_PARAMETERS(P(ID_int_p, x))

#define _FN_KEEP_LIST_(...) _CONCAT(_LISTF_, VAR_COUNT(__VA_ARGS__))(COMMA(), _cond_keep_FN_SAME_TYPE_, __VA_ARGS__)
#define FN_KEEP_LIST(fn1, ...) MAP(_FN_KEEP_LIST_, AP_ARG(fn1, __VA_ARGS__))
// #define FN_KEEP_LIST(fn1, ...)                                                                                         \
// #define FN_KEEP_LIST(fn1, ...) AP_ARG(fn1, __VA_ARGS__)

void gen_test() {
  FN_KEEP_LIST(FN_CREATE_LIST(foo, test1, test2, foo3))

  FN_GET_LAST_TYPE(FN_REDUCE(FN_REDUCE(FN_CREATE(baz)))) f = 2.5;
  // float f = 2.5;
  printf("%f", bar(2, &f));
}

#endif /* GENERIC_TABLE_H */
