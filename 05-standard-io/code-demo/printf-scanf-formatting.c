#include <stdio.h>

int main(void) {
  int number = 123;
  float pi = 3.14159f;

  printf("=== Printf Formatting Demo ===\n\n");

  printf("1. Right-justify (default):\n");
  printf("   printf(\"[%%10d]\", %d);\n", number);
  printf("   Result: [%10d]\n\n", number);

  printf("2. Left-justify:\n");
  printf("   printf(\"[%%-10d]\", %d);\n", number);
  printf("   Result: [%-10d]\n\n", number);

  printf("3. Zero-padding:\n");
  printf("   printf(\"[%%08d]\", %d);\n", number);
  printf("   Result: [%08d]\n\n", number);

  printf("4. Precision (floating-point):\n");
  printf("   printf(\"%%.2f\", %.5f);\n", pi);
  printf("   Result: %.2f\n\n", pi);

  printf("=== Scanf Formatting Demo ===\n\n");

  int input_num;
  float input_float;

  printf("Enter an integer: ");
  if (scanf("%d", &input_num) == 1) {
    printf("You entered: %d\n", input_num);
  }

  printf("Enter a floating-point number: ");
  if (scanf("%f", &input_float) == 1) {
    printf("You entered: %.2f\n", input_float);
  }

  return 0;
}