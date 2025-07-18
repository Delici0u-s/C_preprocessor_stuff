#ifndef D_MACROS_GENERIC_FN_H
#define D_MACROS_GENERIC_FN_H

#include <args/append_arg.h>
#include <args/insert_arg.h>
#include <args/get_arg.h>
#include <math/num_cmp.h>
#include <args/var_count.h>
#include <args/REM_L.h>
#include <args/REM_F.h>
#include <list/list.h>
#include <list/range.h>
#include <list/nest.h>
#include <list/RECCALL.h>
#include <math/logic.h>
#include <common.h>
#include <generic/common.h>
#include <generic/functions_params.h>
#include <generic/test_funcs.h>

#define _FN_EXTRACT_IDS(...) _CONCAT(_LF_, VAR_COUNT(__VA_ARGS__))(S_COMMA, _PARAM_EXTRACT_ID, __VA_ARGS__)
#define FN_CREATE_(func)                                                                                               \
  (_FN_EXTRACT_IDS(STRIP_PARENS(FUNC_TO_TYPES(func)))                                                                  \
       _IF_ELSE(IS_EMPTY(STRIP_PARENS(FUNC_TO_TYPES(func))), S_NONE, S_COMMA)() func)
#define FN_CREATE(func) _IF_ELSE(IS_EMPTY(func), VOID, FN_CREATE_)(func)

#define FN_CREATE_LIST(...) REM_L(REM_L(_CONCAT(_LF_, VAR_COUNT(__VA_ARGS__, , ))(S_COMMA, FN_CREATE, __VA_ARGS__, , )))

#define FN_REDUCE(fn) (REM_F fn)
#define FN_REDUCE_N(n, fn) RECCALL(n, FN_REDUCE, fn)
#define FN_REDUCE_N_(packet) FN_REDUCE_N packet

#define FN_LAST_TYPE(fn) GET_ARG(1, STRIP_PARENS(GET_ARG(0, STRIP_PARENS(fn))))
#define FN_LAST_TYPE_NUM(fn) GET_ARG(0, STRIP_PARENS(GET_ARG(0, STRIP_PARENS(fn))))
#define FN_LAST_TYPE_ID(fn) GET_ARG(0, STRIP_PARENS(fn))

#define FN_TYPE_COUNT(fn) SUB1(VAR_COUNT fn)

// fn based on arg count
#define _FN_SELECT_ON_ARG_COUNT(num, fn) _IF_ELSE(SAME_NUM(num, FN_TYPE_COUNT(fn)), AP_COMMA, VOID)(fn)
#define _FN_SELECT_ON_ARG_COUNT_(packet) _FN_SELECT_ON_ARG_COUNT packet
#define FN_SELECT_ON_ARG_COUNT(num, ...) REM_L(LISTF(S_NONE, _FN_SELECT_ON_ARG_COUNT_, AP_ARG(num, __VA_ARGS__)))

// fn based on type count of other fn
#define FN_SAME_ARG_COUNT(fn1, fn2) SAME_NUM(FN_TYPE_COUNT(fn1), FN_TYPE_COUNT(fn2))
#define FN_SELECT_FN_ON_SAME_ARG_COUNT(fn1, fn2) _IF_ELSE(FN_SAME_ARG_COUNT(fn1, fn2), EXPAND, VOID)(fn2)

#define _FN_SELECT_FN_ON_SAME_ARG_COUNT(fn1, fn2) _IF_ELSE(FN_SAME_ARG_COUNT(fn1, fn2), AP_COMMA, VOID)(fn2)
#define _FN_SELECT_FN_ON_SAME_ARG_COUNT_(packet) _FN_SELECT_FN_ON_SAME_ARG_COUNT packet
#define FN_SELECT_ON_SAME_ARG_COUNT(...)                                                                               \
  REM_L(LISTF(S_NONE, _FN_SELECT_FN_ON_SAME_ARG_COUNT_, AP_ARG(GET_ARG(0, __VA_ARGS__), REM_F(__VA_ARGS__))))

// fn keep on same fn first type
#define FN_SAME_TYPE(fn1, fn2) SAME_NUM(FN_LAST_TYPE_NUM(fn1), FN_LAST_TYPE_NUM(fn2))
#define FN_SAME_TYPE_(packet) FN_SAME_TYPE packet

#define _FN_KEEP_SAME_TYPE(fn1, fn2) _IF_ELSE(FN_SAME_TYPE(fn1, fn2), AP_COMMA, VOID)(fn2)
#define _FN_KEEP_SAME_TYPE_(packet) _FN_KEEP_SAME_TYPE packet
// basically FN_KEEP_SAME_TYPE(fn1, ...)
#define FN_KEEP_SAME_TYPE(...)                                                                                         \
  REM_L(LISTF(S_NONE, _FN_KEEP_SAME_TYPE_, AP_ARG(GET_ARG(0, __VA_ARGS__), REM_F(__VA_ARGS__))))

// fn remove on same fn first type
#define _FN_REMOVE_SAME_TYPE(fn1, fn2) _IF_ELSE(FN_SAME_TYPE(fn1, fn2), VOID, AP_COMMA)(fn2)
#define _FN_REMOVE_SAME_TYPE_(packet) _FN_REMOVE_SAME_TYPE packet
// basically FN_REMOVE_SAME_TYPE(fn1, ...)
#define FN_REMOVE_SAME_TYPE(...)                                                                                       \
  REM_L(LISTF(S_NONE, _FN_REMOVE_SAME_TYPE_, AP_ARG(GET_ARG(0, __VA_ARGS__), REM_F(__VA_ARGS__))))

#define _FN_ORDER_PART_get(...) FN_KEEP_SAME_TYPE(GET_ARG(0, __VA_ARGS__), __VA_ARGS__)
#define _FN_ORDER_PART_rem(...) FN_REMOVE_SAME_TYPE(GET_ARG(0, __VA_ARGS__), __VA_ARGS__)

#define AP_BRACKET(bracket, ...)                                                                                       \
  (STRIP_PARENS(bracket) _IF_ELSE(IS_EMPTY(__VA_ARGS__), VOID,                                                         \
                                  _IF_ELSE(IS_EMPTY(STRIP_PARENS(bracket)), EXPAND, IS_COMMA))(__VA_ARGS__))

#define arg0(a0, ...) a0
#define narg0(a0, ...) __VA_ARGS__

#define _FN_REDUCE_RECCALL_COUNTER(...) ADD1(VAR_COUNT(__VA_ARGS__))

#define _FN_REDUCE_SELECT_STEP_0(cond, prev, todo)                                                                     \
  (_OR(SAME_NUM(VAR_COUNT(_FN_ORDER_PART_rem todo), 1), IS_EMPTY(_FN_ORDER_PART_rem todo)),                            \
   AP_BRACKET(prev, (_FN_ORDER_PART_get todo)), (_FN_ORDER_PART_rem todo))
#define _FN_REDUCE_SELECT_STEP_1(cond, prev, todo) (1, prev, todo)
#define _FN_REDUCE_SELECT_STEP_(cond, prev, todo) _CONCAT(_FN_REDUCE_SELECT_STEP_, cond)(cond, prev, todo)
#define _FN_REDUCE_SELECT_STEP(batch) _FN_REDUCE_SELECT_STEP_ batch
// #define _FN_REDUCE_INIT_STEPPING(fns) RECCALL(2, _FN_REDUCE_SELECT_STEP, (0, (), EXPAND(fns)))
#define _FN_REDUCE_INIT_STEPPING(fns) _CONCAT(_RC_, ADD1(VAR_COUNT fns))(_FN_REDUCE_SELECT_STEP, (0, (), fns))

#define _REMOVE_EMPTY(...) _IF_ELSE(IS_EMPTY(__VA_ARGS__), VOID, AP_COMMA)(__VA_ARGS__)
#define _REMOVE_EMPTY_(a0) _IF_ELSE(IS_EMPTY a0, VOID, AP_COMMA)(a0)
#define REMOVE_EMPTY(...) REM_L(_CONCAT(_LF_, VAR_COUNT(__VA_ARGS__))(S_NONE, _REMOVE_EMPTY, __VA_ARGS__))
#define REMOVE_EMPTY_(...) REM_L(_CONCAT(_LF_, VAR_COUNT(__VA_ARGS__))(S_NONE, _REMOVE_EMPTY_, __VA_ARGS__))
// expects fns args >= 1
#define _FN_TYPE_SEPERATE(...) REMOVE_EMPTY_(STRIP_PARENS(AP_BRACKET(REM_F _FN_REDUCE_INIT_STEPPING((__VA_ARGS__)))))
#define FN_TYPE_SEPERATE(...) _IF_ELSE(IS_EMPTY(__VA_ARGS__), VOID, _FN_TYPE_SEPERATE)(__VA_ARGS__)

void foo() { // clang-format off
  FN_LAST_TYPE(GET_ARG(0, EVAL(REM_F _FN_TYPE_SEPERATE(FN_CREATE_LIST(f1, f2, f3))))) g = 4;
  // FN_LAST_TYPE(GET_ARG(0, STRIP_PARENS(GET_ARG(0, FN_TYPE_SEPERATE(FN_CREATE_LIST(TEST_FUNC_LIST_)))))) g = 3;
  printf("%i\n", g);
  // clang-format on
}

#endif
