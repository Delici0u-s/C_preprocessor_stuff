#ifndef D_MACROS_GENERIC_COMMON_H
#define D_MACROS_GENERIC_COMMON_H

#include <common.h>

#define FUNCTION_TYPES_NAME_PREFIX _types_
#define FUNCTION_TYPES_NAME_SUFFIX
#define FUNC_TO_TYPES(name) _CONCAT(FUNCTION_TYPES_NAME_PREFIX, _CONCAT(name, FUNCTION_TYPES_NAME_SUFFIX))

#endif
