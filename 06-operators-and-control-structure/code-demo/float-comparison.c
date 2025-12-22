#include <math.h>
#include <stdio.h>

#define EPSILON 0.00001f

int main(void) {
  printf("=== Float Comparison Demo ===\n\n");

  printf("1. WRONG: Direct comparison\n");
  float a = 0.1f + 0.2f;
  float b = 0.3f;

  printf("   a = 0.1 + 0.2 = %.20f\n", a);
  printf("   b = 0.3       = %.20f\n", b);

  if (a == b) {
    printf("   a == b: TRUE\n\n");
  } else {
    printf("   a == b: FALSE (WRONG!)\n\n");
  }

  printf("2. CORRECT: Using epsilon\n");
  if (fabs(a - b) < EPSILON) {
    printf("   fabs(a - b) < EPSILON: TRUE\n");
    printf("   Numbers are equal!\n\n");
  } else {
    printf("   fabs(a - b) < EPSILON: FALSE\n\n");
  }

  printf("3. Another example:\n");
  float x = 3.14f;

  if (x == 3.14f) {
    printf("   x == 3.14: TRUE\n");
  } else {
    printf("   x == 3.14: FALSE (May happen!)\n");
  }

  if (fabs(x - 3.14f) < EPSILON) {
    printf("   fabs(x - 3.14) < EPSILON: TRUE (Safe!)\n");
  }

  return 0;
}
