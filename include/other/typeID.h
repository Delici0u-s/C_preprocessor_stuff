#ifndef D_MACROS_TYPE_ID_H
#define D_MACROS_TYPE_ID_H

#include <common.h>
#include <args/get_arg.h>

#define _ID(num, type) (num, type)
#define L(...) __VA_ARGS__

#define ID_GET_ID(_ID) GET_ARG(0, STRIP_PARENS(_ID))
#define ID_GET_TYPE(_ID) GET_ARG(1, STRIP_PARENS(_ID))

// other logic will likely break after 1000 args cuz of num_cmp.h
#define ID_void _ID(0, void)
#define ID_int _ID(1, int)
#define ID_int_p _ID(2, int *)
#define ID_float _ID(3, float)
#define ID_float_p _ID(4, float *)
#define ID_char _ID(5, char)
#define ID_char_p _ID(6, char *)
#define ID_char_p_p _ID(7, char **)
#define ID_double _ID(8, double)
#define ID_double_p _ID(9, double *)
#define ID_void_p _ID(10, void *)

#endif // D_MACROS_TYPE_ID_H
