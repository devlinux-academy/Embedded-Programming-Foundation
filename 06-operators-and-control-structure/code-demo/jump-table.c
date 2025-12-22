#include <stdio.h>

void case_0(void) { printf("   Executing case 0\n"); }

void case_1(void) { printf("   Executing case 1\n"); }

void case_2(void) { printf("   Executing case 2\n"); }

void case_3(void) { printf("   Executing case 3\n"); }

void default_case(void) { printf("   Executing default case\n"); }

int main(void) {
  void (*jump_table[])(void) = {case_0, case_1, case_2, case_3};

  printf("=== Jump Table Demo ===\n\n");

  printf("1. Using switch-case:\n");
  int value = 2;
  switch (value) {
  case 0:
    printf("   Case 0\n");
    break;
  case 1:
    printf("   Case 1\n");
    break;
  case 2:
    printf("   Case 2\n");
    break;
  case 3:
    printf("   Case 3\n");
    break;
  default:
    printf("   Default\n");
    break;
  }

  printf("\n2. Using jump table:\n");
  if (value >= 0 && value < 4) {
    jump_table[value]();
  } else {
    default_case();
  }

  printf("\n3. Performance comparison:\n");
  printf("   Switch-case: O(n) - checks each case\n");
  printf("   Jump table: O(1) - direct jump\n");

  return 0;
}
