#ifndef MACRO_GENERIC_TABLE_H
#define MACRO_GENERIC_TABLE_H

#include "stdio.h"

#include <common.h>
#include <other/typeID.h>
#include <list/list.h>
#include <args/get_arg.h>
#include <args/REM_F.h>
#include <args/REM_L.h>
#include <args/var_count.h>
#include <other/conditions.h>
#include <math/num_cmp.h>
#include <args/append_arg.h>
#include <math/add1.h>
#include <math/rem1.h>
#include <args/has_n_args.h>

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
#define FN_CREATE(func_name)                                                                                           \
  NIF_ELSE(SAME_NUM(VAR_COUNT(_FN_CREATE(STRIP_PARENS(_CONCAT(func_name, FUNCTION_PARAM_SUFFIX)))), 0),                \
           (_FN_CREATE(STRIP_PARENS(_CONCAT(func_name, FUNCTION_PARAM_SUFFIX))), func_name), (func_name))

#define FN_REDUCE(fn) (REM_F(STRIP_PARENS(fn)))
#define FN_GET_LAST_TYPE(fn) GET_ARG(2, STRIP_PARENS(GET_ARG(1, STRIP_PARENS(fn))))
#define FN_GET_LAST_TYPE_ID(fn) GET_ARG(1, STRIP_PARENS(GET_ARG(1, STRIP_PARENS(fn))))
#define FN_CREATE_LIST(...) _CONCAT(_LISTF_, VAR_COUNT(__VA_ARGS__))(COMMA(), FN_CREATE, __VA_ARGS__)

// VAR_COUNT(__VA_ARGS__))(COMMA(), FN_CREATE, __VA_ARGS__)
#define FN_GET_TYPE_COUNT(fn) REM1(VAR_COUNT fn)

// #define FN_TO_GEN_CALL(fn, next) FN_GET_LAST_TYPE(fn) : next
#define FN_TO_GEN_CALL(fn, next) GET_ARG(2, STRIP_PARENS(GET_ARG(1, fn))) : next
#define FN_END_TO_GEN_CALL(fn) FN_GET_LAST_TYPE(fn) : STRIP_PARENS(FN_REDUCE(fn))

#define FN_SAME_TYPE(fn1, fn2) SAME_NUM(FN_GET_LAST_TYPE_ID(fn1), FN_GET_LAST_TYPE_ID(fn2))
#define _cond_keep_FN_SAME_TYPE(fn1, fn2) IF_ELSE(FN_SAME_TYPE(fn1, fn2), fn2, )
#define _cond_keep_FN_SAME_TYPE_(arg) _cond_keep_FN_SAME_TYPE arg

#define FN_AP_COMMA(fn) (fn COMMA())
#define _FN_RET_IF_CORRECT_ARGS_(num, fn) IF(SAME_NUM(num, FN_GET_TYPE_COUNT(fn)), FN_AP_COMMA(fn))
#define _FN_RET_IF_CORRECT_ARGS(brack) MAP(STRIP_PARENS, _FN_RET_IF_CORRECT_ARGS_ brack)
#define FN_SELECT_ON_ARG_COUNT(num, ...) REML(LISTF(, _FN_RET_IF_CORRECT_ARGS, AP_ARG(num, __VA_ARGS__)))
// #define FN_KEEP_LIST(fn1, ...) MAP(_cond_keep_FN_SAME_TYPE, AP_ARG(fn1, __VA_ARGS__))
#define FN_GET_LIST_N_ARGS(num, funcs) FN_SELECT_ON_ARG_COUNT(num, FN_CREATE_LIST(STRIP_PARENS(funcs)))
// #define FN_SAME_TYPE(fn1, fn2) IF_ELSE(SAME_NUM(FN_GET_LAST_TYPE_ID(fn1), FN_GET_LAST_TYPE_ID(fn2)), true, false)

// __VA_ARGS__ should be GENERIC_CALLS
#define _GENERATE_VAR_LIST_n(a0, ...) _Generic((a0), __VA_ARGS__)

#define GENERATE_GENERIC_0(fns, args) STRIP_PARENS fns()

#define GENERATE_GENERIC_1(fns, args)                                                                                  \
  _GENERATE_VAR_LIST_n(STRIP_PARENS(args), MAP(FN_END_TO_GEN_CALL, STRIP_PARENS(fns)))(STRIP_PARENS(args))

#define GENERATE_GENERIC_2(fns, args) fns | args

// magic function
#define JOIN_FUNCS(funcs, ...)                                                                                         \
  CONCAT(GENERATE_GENERIC_, VAR_COUNT(__VA_ARGS__))((FN_GET_LIST_N_ARGS(VAR_COUNT(__VA_ARGS__), funcs)), (__VA_ARGS__))

//////////////////////////////////////////////////////////////
#define PRINT_STRING(str) printf(" %s", str)
#define PRINT_FUNC(func)                                                                                               \
  FOR_EACH(PRINT_STRING, __PRETTY_FUNCTION__, ":",                                                                     \
           MAP(STRINGIFY, MAP(FN_GET_LAST_TYPE, STRIP_PARENS(_CONCAT(func, FUNCTION_PARAM_SUFFIX)))), "\n")

#define f_no_param_types SET_PARAMETERS()
CREATE_FUNC(void, f_no_param) { puts(" f_no_param"); }

#define foo_types SET_PARAMETERS(P(ID_int_p, x))
CREATE_FUNC(void, foo) { PRINT_FUNC(foo); }

#define foo1_types SET_PARAMETERS(P(ID_int, x))
CREATE_FUNC(void, foo1) { PRINT_FUNC(foo1); }

#define foo2_types SET_PARAMETERS(P(ID_float_p, x))
CREATE_FUNC(void, foo2) { PRINT_FUNC(foo2); }

#define foo3_types SET_PARAMETERS(P(ID_char_p, x))
CREATE_FUNC(void, foo3) { PRINT_FUNC(foo3); }

#define bar_types SET_PARAMETERS(P(ID_int, x), P(ID_float_p, f))
CREATE_FUNC(float, bar) { PRINT_FUNC(bar); }

#define baz_types SET_PARAMETERS(P(ID_int, x), P(ID_float_p, f), P(ID_float, k))
CREATE_FUNC(float, baz) { PRINT_FUNC(baz); }

#define joined(...) JOIN_FUNCS((foo, foo1, foo2, bar, baz, foo3, f_no_param), __VA_ARGS__)

void gen_test() {
  joined();
  joined((int)0);
  joined((int *)0);
  joined((float *)0);
  joined((char *)0);
}

#endif /* GENERIC_TABLE_H */
