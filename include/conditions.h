#ifndef D_MACRO_INCL_ALL_H
#define D_MACRO_INCL_ALL_H

#include "common.h"
#include "concat.h"

// cond as 1 for true, 0 for false
#define IF_ELSE(cond, _true, _false) CONCAT(_IF_, EXPAND(cond))(_true, _false)

#define _IF_1(true_branch, false_branch) true_branch
#define _IF_0(true_branch, false_branch) false_branch

#endif
