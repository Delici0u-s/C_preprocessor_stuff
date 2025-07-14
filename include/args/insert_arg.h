#ifndef D_MACROS_IN_ARG_H
#define D_MACROS_IN_ARG_H

#include <common.h>
#include <args/var_count.h>
#include <args/append_arg.h>
#include <list/list.h>

#define IN_ARG(a0, ...) MAP(_SWAP_, AP_ARG(a0, __VA_ARGS__))

#endif
