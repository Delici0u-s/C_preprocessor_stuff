#include "var_count.h"

#define _CONCAT_(a, b) a##b
#define CONCAT(a, b) _CONCAT_(a, b)

#define D_INTERNAL_NAME_0() first()
#define D_INTERNAL_NAME_1(x) _Generic((x), int: second, int *: third, char *: fourth)(x)
#define D_INTERNAL_NAME_2(x, y)                                                                                        \
  _Generic((x), int: _Generic((y), int: fifth, char: sixt), char: _Generic((y), char: seventh))(x, y)

#define NAME(...) CONCAT(D_INTERNAL_NAME_, VAR_COUNT(__VA_ARGS__))(__VA_ARGS__)

void foo() { NAME(1) }

int first() {
  puts("1");
  return 0;
}
int second(int a) {
  puts("2");
  return 0;
}
int third(int *a) {
  puts("3");
  return 0;
}
int fourth(char *b) {
  puts("4");
  return 0;
}
char fifth(int a, int b) {
  puts("5");
  return 0;
}
char sixt(int a, char b) {
  puts("6");
  return 0;
}
char seventh(char a, char b) {
  puts("7");
  return 0;
}

// Dispatcher macros
#define D_INTERNAL_NAME_0() first()
#define D_INTERNAL_NAME_1(x) _Generic((x), int: second, int *: third, char *: fourth)(x)
#define D_INTERNAL_NAME_2(x, y)                                                                                        \
  _Generic((x), int: _Generic((y), int: fifth, char: sixt), char: _Generic((y), char: seventh))(x, y)

#define test(...) D_INTERNAL_NAME(...) _Generic((GET_ARG(1, __VA_ARGS__)), int: _Generic((GET_ARG(2, __VA_ARGS__), int: fifth, char: sixt, default: second), int*: third, char: _Generic((GET_ARG(2, __VA_ARGS__)), char: seventh), char*: fourth, default: first)(__VA_ARGS__)

#define NAME(...) CONCAT(D_INTERNAL_NAME_, VAR_COUNT(__VA_ARGS__))(__VA_ARGS__)
