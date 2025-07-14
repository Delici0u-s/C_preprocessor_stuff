#ifndef D_MACROS_F_P_T_H
#define D_MACROS_F_P_T_H

#include <generic/functions_params.h>

#define _types_f0 F_PARAM()
CREATE_FUNC_TEST(ID_void, f0)

#define _types_f1 F_PARAM(P(ID_int, x))
CREATE_FUNC_TEST(ID_void, f1)

#define _types_f2 F_PARAM(P(ID_int, x), P(ID_float_p, y))
CREATE_FUNC_TEST(ID_void, f2)

#define _types_f3 F_PARAM(P(ID_int, x), P(ID_float_p, y), P(ID_char_p, z[]))
CREATE_FUNC_TEST(ID_void, f3)

#define _types_f4 F_PARAM(P(ID_int, x), P(ID_float_p, y), P(ID_char_p, z[]), P(ID_int_p, i))
CREATE_FUNC_TEST(ID_void, f4)

#define _types_f5 F_PARAM(P(ID_int, x), P(ID_float_p, y), P(ID_char_p, z[]), P(ID_int_p, i), P(ID_int_p, j))
CREATE_FUNC_TEST(ID_void, f5)

// New test cases below:

// One parameter: pointer type
#define _types_f6 F_PARAM(P(ID_double_p, dp))
CREATE_FUNC_TEST(ID_void, f6)

// Swapped type order: float* first
#define _types_f7 F_PARAM(P(ID_float_p, y), P(ID_int, x))
CREATE_FUNC_TEST(ID_void, f7)

// Three parameters, all same type
#define _types_f8 F_PARAM(P(ID_int, a), P(ID_int, b), P(ID_int, c))
CREATE_FUNC_TEST(ID_void, f8)

// Mix of scalar and pointer types
#define _types_f9 F_PARAM(P(ID_char_p, str), P(ID_int, len), P(ID_float_p, buffer))
CREATE_FUNC_TEST(ID_void, f9)

// Nested pointer: char**
#define _types_f10 F_PARAM(P(ID_char_p_p, argv), P(ID_int, argc))
CREATE_FUNC_TEST(ID_void, f10)

// Repetition of pointer types in different positions
#define _types_f11 F_PARAM(P(ID_int_p, a), P(ID_int, b), P(ID_int_p, c))
CREATE_FUNC_TEST(ID_void, f11)

// void* as generic pointer
#define _types_f12 F_PARAM(P(ID_void_p, data), P(ID_int, size))
CREATE_FUNC_TEST(ID_void, f12)

// Five parameters, alternating types
#define _types_f13 F_PARAM(P(ID_int, a), P(ID_float, b), P(ID_int, c), P(ID_float, d), P(ID_char, e))
CREATE_FUNC_TEST(ID_void, f13)

// Function returning non-void
#define _types_f14 F_PARAM(P(ID_double, x), P(ID_double, y))
CREATE_FUNC_TEST(ID_double, f14)

#define TEST_FUNC_LIST f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14

#endif
