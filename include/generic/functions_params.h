#ifndef D_MACROS_F_P_H
#define D_MACROS_F_P_H

#include "args/var_count.h"
#include "math/logic.h"
#include <list/list.h>
#include <args/get_arg.h>
#include <common.h>
#include <generic/common.h>
#include <other/typeID.h>

#define P(typeID, var_name) (typeID, var_name)
#define F_PARAM(...) (__VA_ARGS__)

#define _PARAM_EXTRACT_ID(param) GET_ARG(0, STRIP_PARENS(param))
#define _PARAM_EXTRACT_VAR(param) GET_ARG(1, STRIP_PARENS(param))
#define _PARAM_TO_FUNC_PARAM(param) ID_GET_TYPE(_PARAM_EXTRACT_ID(param)) _PARAM_EXTRACT_VAR(param)

#define CREATE_FUNC_(_ret_type, _name) _ret_type _name(MAP(_PARAM_TO_FUNC_PARAM, STRIP_PARENS(FUNC_TO_TYPES(_name))))
#define CREATE_FUNC(_ret_typeID, _name) CREATE_FUNC_(ID_GET_TYPE(_ret_typeID), _name)

// MACRO_DEBUG
#include <stdio.h>
#define PRINT_STRING(str) printf(" - %s", str)
#define PRINT_FUNC_0(func) FOR_EACH(PRINT_STRING, __PRETTY_FUNCTION__, "\n")
#define PRINT_FUNC_1(func)                                                                                             \
  FOR_EACH(PRINT_STRING, __PRETTY_FUNCTION__,                                                                          \
           MAP(STRINGIFY, MAP(_PARAM_TO_FUNC_PARAM, STRIP_PARENS(FUNC_TO_TYPES(func)))), "\n")

#define PRINT_FUNC(func) IF_ELSE(IS_EMPTY FUNC_TO_TYPES(func), PRINT_FUNC_0, PRINT_FUNC_1)(func)

#define CREATE_FUNC_TEST(_ret_typeID, _name)                                                                           \
  CREATE_FUNC(_ret_typeID, _name) { PRINT_FUNC(_name); }

#endif
