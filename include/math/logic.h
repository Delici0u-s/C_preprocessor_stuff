#ifndef D_MACRO_MATH_LOGIC_H
#define D_MACRO_MATH_LOGIC_H

#include <common.h>
#include <other/concat.h>
#include <math/num_cmp.h>
#include <math/SUB1.h>
#include <list/list.h>
#include <list/nest.h>
#include <list/RECCALL.h>
#include <args/append_arg.h>
#include <args/REM_F.h>

// cond as 1 for true, 0 for false
#define TRUE 1
#define FALSE 0

#define BIT_NOT(x) _BIT_NOT(x)
#define _BIT_NOT(x) __BIT_NOT_##x
#define __BIT_NOT_0 TRUE
#define __BIT_NOT_1 FALSE

#define REDUCE_TO_BOOL(num) _IF_ELSE(SAME_NUM(num, FALSE), FALSE, TRUE)

#define IS_BOOL(num) OR(SAME_NUM(num, TRUE), SAME_NUM(num, FALSE))
#define IS_TRUE(_bool) SAME_NUM(REDUCE_TO_BOOL(_bool), TRUE)
#define IS_FALSE(_bool) SAME_NUM(REDUCE_TO_BOOL(_bool), FALSE)

#define _IF_ELSE(cond, _true, _false) CONCAT(_IF_ELSE_, cond)(_true, _false)
#define IF_ELSE(cond, _true, _false) CONCAT(_IF_ELSE_, REDUCE_TO_BOOL(cond))(_true, _false)
#define _NIF_ELSE(cond, _true, _false) CONCAT(_IF_ELSE_, BIT_NOT(cond))(_true, _false)
#define NIF_ELSE(cond, _true, _false) CONCAT(_IF_ELSE_, BIT_NOT(REDUCE_TO_BOOL(cond)))(_true, _false)
#define _IF(cond, _true) CONCAT(_IF_, cond)(_true)
#define IF(cond, _true) CONCAT(_IF_, REDUCE_TO_BOOL(cond))(_true)
#define _NIF(cond, _false) CONCAT(_IF_, BIT_NOT(cond))(_false)
#define NIF(cond, _false) CONCAT(_IF_, BIT_NOT(REDUCE_TO_BOOL(cond)))(_false)

#define _IF_ELSE_1(_true, _false) _true
#define _IF_ELSE_0(_true, _false) _false
#define _IF_0(_true)
#define _IF_1(_true) _true

// #define AND(bool1, bool2) IF_ELSE(IS_TRUE(bool1), IF_ELSE(IS_TRUE(bool2), TRUE, FALSE), FALSE)
#define _AND(bool1, bool2) IF_ELSE(IS_TRUE(bool1), IF_ELSE(IS_TRUE(bool2), TRUE, FALSE), FALSE)
#define _OR(bool1, bool2) IF_ELSE(IS_TRUE(bool1), TRUE, IF_ELSE(IS_TRUE(bool2), TRUE, FALSE))
#define _NOT(bool1) BIT_NOT(REDUCE_TO_BOOL(bool1))

#define NOT(...) MAP(_NOT, __VA_ARGS__)

#define _AND_PART_two(a0, a1, ...) NIF_ELSE(SAME_NUM(VAR_COUNT(__VA_ARGS__), 0), S_COMMA, S_NONE)() __VA_ARGS__
#define _AND_PART_one(a0, a1, ...) _AND(a0, a1)
#define _AND_PART(packet) (_AND_PART_one packet _AND_PART_two packet)
#define _AND_NO_ARGS(...)
#define _AND_ONE_ARGS(a0) REDUCE_TO_BOOL(a0)
#define _AND_ANY_ARGS(...) STRIP_PARENS(RECCALL(SUB1(VAR_COUNT(__VA_ARGS__)), _AND_PART, (__VA_ARGS__)))
#define AND(...)                                                                                                       \
  IF_ELSE(SAME_NUM(VAR_COUNT(__VA_ARGS__), 0), _AND_NO_ARGS,                                                           \
          IF_ELSE(SAME_NUM(VAR_COUNT(__VA_ARGS__), 1), _AND_ONE_ARGS, _AND_ANY_ARGS))(__VA_ARGS__)

#define _OR_PART_two(a0, a1, ...) NIF_ELSE(SAME_NUM(VAR_COUNT(__VA_ARGS__), 0), S_COMMA, S_NONE)() __VA_ARGS__
#define _OR_PART_one(a0, a1, ...) _OR(a0, a1)
#define _OR_PART(packet) (_OR_PART_one packet _OR_PART_two packet)
#define _OR_NO_ARGS(...)
#define _OR_ONE_ARGS(a0) REDUCE_TO_BOOL(a0)
#define _OR_ANY_ARGS(...) STRIP_PARENS(RECCALL(SUB1(VAR_COUNT(__VA_ARGS__)), _OR_PART, (__VA_ARGS__)))
#define OR(...)                                                                                                        \
  IF_ELSE(SAME_NUM(VAR_COUNT(__VA_ARGS__), 0), _OR_NO_ARGS,                                                            \
          IF_ELSE(SAME_NUM(VAR_COUNT(__VA_ARGS__), 1), _OR_ONE_ARGS, _OR_ANY_ARGS))(__VA_ARGS__)

#define NAND(...) NOT(AND(__VA_ARGS__))
#define NOR(...) NOT(OR(__VA_ARGS__))
#define XOR(bool1, bool2) OR(AND(bool1, NOT(bool2)), AND(NOT(bool1), bool2))
#define XNOR(bool1, bool2) NOT(XOR(bool1, bool2))
#define IMPLIES(bool1, bool2) OR(NOT(bool1), bool2)
#define CIMPLIES(bool1, bool2) OR(bool1, NOT(bool2))

#endif
