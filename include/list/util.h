#ifndef D_MACRO_LIST_UTIL_H
#define D_MACRO_LIST_UTIL_H

#include <common.h>
#include <list/nest.h>

#define REVERSE(...) NEST(SWAP, __VA_ARGS__)

#endif
