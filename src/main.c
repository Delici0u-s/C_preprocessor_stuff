#include <stdio.h>
#include <concat.h>
#include <common.h>

int main(void) {
  // CONCAT(a, b, c)(a, b, c);
  // puts(STR(VAR_COUNT(1)));
  puts(STR(CONCAT(1, 2, 3, 4, 5, 6, 7)));
  puts(STR(done));

  return 0;
}
