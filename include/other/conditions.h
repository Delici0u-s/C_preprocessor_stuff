#ifndef D_MACRO_INCL_ALL_H
#define D_MACRO_INCL_ALL_H

#include <common.h>
#include <other/concat.h>

#define BIT_NOT(x) _BIT_NOT(x)
#define _BIT_NOT(x) __BIT_NOT_##x
#define __BIT_NOT_0 1
#define __BIT_NOT_1 0

// cond as 1 for true, 0 for false
#define IF_ELSE(cond, _true, _false) CONCAT(_IF_ELSE_, cond)(_true, _false)
#define NIF_ELSE(cond, _true, _false) CONCAT(_IF_ELSE_, BIT_NOT(cond))(_true, _false)
#define IF(cond, _true) CONCAT(_IF_, cond)(_true)
#define NIF(cond, _false) CONCAT(_IF_, BIT_NOT(cond))(_false)

#define _IF_ELSE_1(_true, _false) _true
#define _IF_ELSE_0(_true, _false) _false
#define _IF_0(_true)
#define _IF_1(_true) _true

#endif
