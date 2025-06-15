#include "var_count.h"

#define _CONCAT_(a, b) a##b
#define CONCAT(a, b) _CONCAT_(a, b)

#define D_INTERNAL_NAME_0() first()
#define D_INTERNAL_NAME_1(x) _Generic((x), int: second, int *: third, char *: fourth)(x)
#define D_INTERNAL_NAME_2(x, y)                                                                                        \
  _Generic((x), int: _Generic((y), int: fifth, char: sixt), char: _Generic((y), char: seventh))(x, y)

#define NAME(...) CONCAT(D_INTERNAL_NAME_, VAR_COUNT(__VA_ARGS__))(__VA_ARGS__)

void foo() { NAME(1) }
