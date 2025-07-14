#ifndef D_MACROS_LIST_RANGE_H
#define D_MACROS_LIST_RANGE_H

#include <list/RECCALL.h>
#include "args/get_arg.h"
#include "math/sub1.h"
#include <args/var_count.h>
#include <args/append_arg.h>
#include <args/REM_F.h>
#include <math/logic.h>
#include <math/general.h>
#include <list/list.h>
#include <list/util.h>
#include <common.h>

// fuck c preprocessor
#define _RECCALL_RANGE(amount, function, arg) _CONCAT(_RC_, amount)(function, arg)

#define _RANGE_STEP(x) (GET_ARG(0, STRIP_PARENS(x)), MAP(ADD1, STRIP_PARENS(x)))
#define _RANGE_1_else(n) STRIP_PARENS(_RECCALL_RANGE(SUB1(n), _RANGE_STEP, (1)))
#define _RANGE_1_zero(n)

#define _RANGE_0(...) "no args"
#define _RANGE_1(end) IF_ELSE(SAME_NUM(0, end), _RANGE_1_zero, _RANGE_1_else)(end)

#ifdef SMART_RANGE
#define _RANGE_2_norm(start, end) MAP(ADD_, AP_ARG(start, MAP(SUB1, _RANGE_1(SUB(ADD1(end), start)))))
#define _RANGE_2_inverse(start, end) REVERSE(_RANGE_2_norm(end, start))
#define _RANGE_2(start, end) IF_ELSE(IS_LESS(end, start), _RANGE_2_inverse, _RANGE_2_norm)(start, end)
#else
#define _RANGE_2(start, end) MAP(ADD_, AP_ARG(start, MAP(SUB1, _RANGE_1(SUB(ADD1(end), start)))))
#endif

#define RANGE(...) _CONCAT(_RANGE_, IF_ELSE(IS_EMPTY(__VA_ARGS__), 0, VAR_COUNT(__VA_ARGS__)))(__VA_ARGS__)

#endif
