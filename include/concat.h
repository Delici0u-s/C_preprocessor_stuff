#ifndef D_MACROS_CONCAT_H
#define D_MACROS_CONCAT_H

#include "var_count.h"
#include "nest.h"

#define CONCAT(...) NEST(_CONCAT, __VA_ARGS__)

#endif
