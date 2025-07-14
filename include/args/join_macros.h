#ifndef D_MACROS_ARGS_MACRO_JOIN_H
#define D_MACROS_ARGS_MACRO_JOIN_H

#include <args/var_count.h>
#include <math/logic.h>
#include <math/general.h>
#include <math/add1.h>
#include <common.h>

#undef def
#define JOIN_MACROS(NAME, min_args, max_args, ...)                                                                     \
  IF_ELSE(OR(IS_LESS(ADD1(VAR_COUNT(__VA_ARGS__)), min_args), IS_LESS(ADD1(max_args), VAR_COUNT(__VA_ARGS__))),        \
          _CONCAT(NAME, def), _CONCAT(NAME, VAR_COUNT(__VA_ARGS__)))(__VA_ARGS__)

#define JOIN_MACROS_SIMPL(NAME, ...) _CONCAT(NAME, VAR_COUNT(__VA_ARGS__))(__VA_ARGS__)
/*
JOIN_MACROS concatinates NAME with the amount of args, if the amount of args is in the given range.
    for example: joined(1, 2 ,3) _NAME_3(1, 2, 3) but only if min_args <= 3, and max_args >= 3
Else it evaluates to NAME_def(__VA_ARGS__)

#define _MACRO_JOIN_EXAMPLE_def(...) "OUT_OF_RANGE"
#define _MACRO_JOIN_EXAMPLE_2(a0, a1) "TWO ARGS"
#define _MACRO_JOIN_EXAMPLE_3(a0, a1, a2) "THREE ARGS"
#define _MACRO_JOIN_EXAMPLE_4(a0, a1, a2, a3) "FOUR ARGS"

#define JOIN_MACRO_EXAMPLE(...) JOIN_MACROS(_MACRO_JOIN_EXAMPLE_, 2, 4, __VA_ARGS__)


  JOIN_MACRO_EXAMPLE() -> "OUT_OF_RANGE"
  JOIN_MACRO_EXAMPLE(1) -> "OUT_OF_RANGE"
  JOIN_MACRO_EXAMPLE(1, 2) -> "TWO ARGS"
  JOIN_MACRO_EXAMPLE(1, 2, 3) ->  "THREE ARGS"
  JOIN_MACRO_EXAMPLE(1, 2, 3, 4) -> "FOUR ARGS"
  JOIN_MACRO_EXAMPLE(1, 2, 3, 4, 5) -> "OUT_OF_RANGE"
  JOIN_MACRO_EXAMPLE(1, 2, 3, 4, 5, 6) -> "OUT_OF_RANGE"
*/
#endif
