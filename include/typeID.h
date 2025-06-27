#ifndef D_MACROS_TYPE_ID_H
#define D_MACROS_TYPE_ID_H

#include "common.h"
#include "concat.h"
#include "get_arg.h"

#define _ID(type) (__COUNTER__, type)
#define L(...) __VA_ARGS__

// other logic will likely break after 1000 args cuz of num_cmp.h
#define ID_int _ID(int)
#define ID_int_p _ID(int *)
#define ID_float _ID(float)
#define ID_char _ID(char)
#define ID_char_arr _ID(char[])

#define TYPE_TABLE L(ID_int, ID_int_p, ID_float, ID_char, ID_char_arr)

#define ID_GET_ID(_ID) GET_ARG(1, STRIP_PARENS(_ID))
#define ID_GET_TYPE(_ID) GET_ARG(2, STRIP_PARENS(_ID))

#endif // D_MACROS_TYPE_ID_H
