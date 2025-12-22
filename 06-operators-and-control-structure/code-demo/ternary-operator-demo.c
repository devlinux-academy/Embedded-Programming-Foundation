#include <stdio.h>

#define MAX_BAD(a, b) a > b ? a : b
#define MAX_GOOD(a, b) ((a) > (b) ? (a) : (b))

int main(void) {
  printf("=== Ternary Operator Demo ===\n\n");

  printf("1. Correct usage:\n");
  int max = (5 > 10) ? 5 : 10;
  printf("   (5 > 10) ? 5 : 10 = %d\n\n", max);

  printf("2. WRONG macro:\n");
  printf("   MAX_BAD(5 + 1, 10) = %d (Expected: 10)\n", MAX_BAD(5 + 1, 10));
  printf("   Why wrong? Expands to: 5 + 1 > 10 ? 5 + 1 : 10\n\n");

  printf("3. CORRECT macro:\n");
  printf("   MAX_GOOD(5 + 1, 10) = %d\n", MAX_GOOD(5 + 1, 10));

  return 0;
}
