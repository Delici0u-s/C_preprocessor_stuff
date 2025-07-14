#ifndef D_MACROS_GENERIC_FN_H
#define D_MACROS_GENERIC_FN_H

#include <args/append_arg.h>
#include <args/insert_arg.h>
#include <args/get_arg.h>
#include <math/num_cmp.h>
#include <args/var_count.h>
#include <args/REM_L.h>
#include <list/list.h>
#include <list/range.h>
#include <math/logic.h>
#include <common.h>
#include <generic/common.h>
#include <generic/functions_params.h>
#include <generic/test_funcs.h>

#define _FN_EXTRACT_IDS(...) _CONCAT(_LF_, VAR_COUNT(__VA_ARGS__))(S_COMMA, _PARAM_EXTRACT_ID, __VA_ARGS__)
#define FN_CREATE(func)                                                                                                \
  (_FN_EXTRACT_IDS(STRIP_PARENS(FUNC_TO_TYPES(func)))                                                                  \
       IF_ELSE(IS_EMPTY(STRIP_PARENS(FUNC_TO_TYPES(func))), S_NONE, S_COMMA)() func)

#define FN_CREATE_LIST(...) REM_L(_CONCAT(_LF_, VAR_COUNT(__VA_ARGS__, ))(S_COMMA, FN_CREATE, __VA_ARGS__, ))

#define FN_REDUCE(fn) (REM_F fn)
#define FN_REDUCE_N(n, fn) RECCALL(n, FN_REDUCE, fn)
#define FN_REDUCE_N_(packet) FN_REDUCE_N packet

#define FN_LAST_TYPE(fn) GET_ARG(1, STRIP_PARENS(GET_ARG(0, STRIP_PARENS(fn))))
#define FN_LAST_TYPE_NUM(fn) GET_ARG(0, STRIP_PARENS(GET_ARG(0, STRIP_PARENS(fn))))
#define FN_LAST_TYPE_ID(fn) GET_ARG(0, STRIP_PARENS(fn))

#define FN_TYPE_COUNT(fn) SUB1(VAR_COUNT fn)

// fn based on arg count
#define _FN_SELECT_ON_ARG_COUNT(num, fn) IF_ELSE(SAME_NUM(num, FN_TYPE_COUNT(fn)), AP_COMMA, VOID)(fn)
#define _FN_SELECT_ON_ARG_COUNT_(packet) _FN_SELECT_ON_ARG_COUNT packet
#define FN_SELECT_ON_ARG_COUNT(num, ...) REM_L(LISTF(S_NONE, _FN_SELECT_ON_ARG_COUNT_, AP_ARG(num, __VA_ARGS__)))

// fn based on type count of other fn
#define FN_SAME_ARG_COUNT(fn1, fn2) SAME_NUM(FN_TYPE_COUNT(fn1), FN_TYPE_COUNT(fn2))
#define FN_SELECT_FN_ON_SAME_ARG_COUNT(fn1, fn2) IF_ELSE(FN_SAME_ARG_COUNT(fn1, fn2), EXPAND, VOID)(fn2)

#define _FN_SELECT_FN_ON_SAME_ARG_COUNT(fn1, fn2) IF_ELSE(FN_SAME_ARG_COUNT(fn1, fn2), AP_COMMA, VOID)(fn2)
#define _FN_SELECT_FN_ON_SAME_ARG_COUNT_(packet) _FN_SELECT_FN_ON_SAME_ARG_COUNT packet
#define FN_SELECT_ON_SAME_ARG_COUNT(...)                                                                               \
  REM_L(LISTF(S_NONE, _FN_SELECT_FN_ON_SAME_ARG_COUNT_, AP_ARG(GET_ARG(0, __VA_ARGS__), REM_F(__VA_ARGS__))))

// fn keep on same fn first type
#define FN_SAME_TYPE(fn1, fn2) SAME_NUM(FN_LAST_TYPE_NUM(fn1), FN_LAST_TYPE_NUM(fn2))
#define FN_SAME_TYPE_(packet) FN_SAME_TYPE packet

#define _FN_KEEP_SAME_TYPE(fn1, fn2) IF_ELSE(FN_SAME_TYPE(fn1, fn2), AP_COMMA, VOID)(fn2)
#define _FN_KEEP_SAME_TYPE_(packet) _FN_KEEP_SAME_TYPE packet
// basically FN_KEEP_SAME_TYPE(fn1, ...)
#define FN_KEEP_SAME_TYPE(...)                                                                                         \
  REM_L(LISTF(S_NONE, _FN_KEEP_SAME_TYPE_, AP_ARG(GET_ARG(0, __VA_ARGS__), REM_F(__VA_ARGS__))))

// fn remove on same fn first type
#define _FN_REMOVE_SAME_TYPE(fn1, fn2) IF_ELSE(FN_SAME_TYPE(fn1, fn2), VOID, AP_COMMA)(fn2)
#define _FN_REMOVE_SAME_TYPE_(packet) _FN_REMOVE_SAME_TYPE packet
// basically FN_REMOVE_SAME_TYPE(fn1, ...)
#define FN_REMOVE_SAME_TYPE(...)                                                                                       \
  REM_L(LISTF(S_NONE, _FN_REMOVE_SAME_TYPE_, AP_ARG(GET_ARG(0, __VA_ARGS__), REM_F(__VA_ARGS__))))

#define _FN_ORDER_PART(...)                                                                                            \
  (FN_KEEP_SAME_TYPE(GET_ARG(0, __VA_ARGS__), __VA_ARGS__)), (FN_REMOVE_SAME_TYPE(GET_ARG(0, __VA_ARGS__), __VA_ARGS__))

// TODO: COUNT_INDIV_TYPES

void f() { //
  _FN_ORDER_PART(FN_CREATE_LIST(REM_F(TEST_FUNC_LIST)))
}

#endif
