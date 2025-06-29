#ifndef D_MACROS_CONCAT_H
#define D_MACROS_CONCAT_H

#include <args/var_count.h>
#include <list/nest.h>

#define CONCAT(...) NEST(_CONCAT, __VA_ARGS__)

#endif
