#ifndef D_MACRO_MATH_GENERAL_H
#define D_MACRO_MATH_GENERAL_H

#include <common.h>
#include <list/RECCALL.h>
#include <math/logic.h>
#include <math/sub1.h>
#include <math/add1.h>
#include <args/get_arg.h>
#include <args/REM_F.h>

#define MATH_MAX 1000
#define MATH_MIN 0

#define M_SQUARE(num) RECCALL(num, ADD1, num)
#define ADD(num1, num2) RECCALL(num1, ADD1, num2)
#define ADD_(batch) ADD batch
// be careful with sub, dont go below 0, so make sure num1 - num2 > 0
#define SUB(num1, num2) RECCALL(num2, SUB1, num1)
#define SUB_(batch) SUB batch

#define IS_NULL(num) SAME_NUM(0, num)

/*
// batch -> (to_continue, num1, num2)
#define _REDUCER_0(cond, num1, num2) (_OR(IS_NULL(SUB1(num1)), IS_NULL(SUB1(num2))), SUB1(num1), SUB1(num2))
#define _REDUCER_1(cond, num1, num2) (1, num1, num2)
#define _REDUCER(batch) _CONCAT(_REDUCER_, GET_ARG(0, STRIP_PARENS(batch))) batch
#define _INIT_REDUCING_(num1, num2) RECCALL(ADD1(num1), _REDUCER, (0, ADD1(num1), ADD1(num2)))
#define _INIT_REDUCING(num1, num2) (REM_F(STRIP_PARENS(_INIT_REDUCING_(num1, num2))))
#define _SELECT_NUM(num1, num2) IS_NULL(num1)
#define _SELECT_NUM_(batch) _SELECT_NUM batch
#define _GET_NUM_POS_0(num1, num2) _SELECT_NUM_(_INIT_REDUCING(num1, num2))
#define _GET_NUM_POS_1(num1, num2) _SELECT_NUM(num1, num2)
#define IS_LESS(num1, num2) _CONCAT(_GET_NUM_POS_, _OR(IS_NULL(num1), IS_NULL(num2)))(num1, num2)
*/

#define _REDUCER_0(cond, num1, num2) (_OR(IS_NULL(SUB1(num1)), IS_NULL(SUB1(num2))), SUB1(num1), SUB1(num2))
#define _REDUCER_1(cond, num1, num2) (1, num1, num2)
#define arg0(a0, ...) a0
#define _REDUCER(batch) _CONCAT(_REDUCER_, arg0 batch) batch
#define _INIT_REDUCING_(num1, num2) RECCALL(ADD1(num1), _REDUCER, (0, ADD1(num1), ADD1(num2)))
#define IS_LESS(num1, num2) IF_ELSE(IS_NULL(GET_ARG(1, STRIP_PARENS(_INIT_REDUCING_(num2, num1)))), 0, 1)

#define MIN(num1, num2) IF_ELSE(IS_LESS(num1, num2), num1, num2)
#define MAX(num1, num2) IF_ELSE(IS_LESS(num1, num2), num2, num1)

#endif
