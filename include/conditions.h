#ifndef D_MACRO_INCL_ALL_H
#define D_MACRO_INCL_ALL_H

#include "common.h"
#include "concat.h"

// cond as 1 for true, 0 for false
#define IF_ELSE(cond, _true, _false) CONCAT(_IF_, cond)(_true, _false)

#define _IF_1(_true, _false) _true
#define _IF_0(_true, _false) _false

#endif
