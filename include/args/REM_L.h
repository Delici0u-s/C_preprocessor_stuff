#ifndef D_MACROS_REM_L_H
#define D_MACROS_REM_L_H

#include "args/REM_F.h"
#include "list/util.h"

#define REM_L(...) REVERSE(REM_F(REVERSE(__VA_ARGS__)))


#endif
