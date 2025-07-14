#ifndef D_MACROS_REM_F_H
#define D_MACROS_REM_F_H

#include <common.h>
#include <args/var_count.h>

#define _REM_F_0(a0, ...) __VA_ARGS__
#define _REM_F_1()
#define REM_F(...) _CONCAT(_REM_F_, IS_EMPTY(__VA_ARGS__))(__VA_ARGS__)

#endif
