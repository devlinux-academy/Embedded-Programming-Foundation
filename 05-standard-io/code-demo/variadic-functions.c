#include <stdarg.h>
#include <stdio.h>

int sum_integers(int count, ...) {
  va_list args;
  va_start(args, count);

  int total = 0;
  for (int i = 0; i < count; i++) {
    total += va_arg(args, int);
  }

  va_end(args);
  return total;
}

void print_values(const char *format, ...) {
  va_list args;
  va_start(args, format);

  printf("Values: ");
  vprintf(format, args);
  printf("\n");

  va_end(args);
}

int main(void) {
  printf("=== Variadic Functions Demo ===\n\n");

  printf("1. Sum of 3 numbers: %d\n", sum_integers(3, 10, 20, 30));
  printf("2. Sum of 5 numbers: %d\n", sum_integers(5, 1, 2, 3, 4, 5));

  printf("\n");

  print_values("Integer: %d, Float: %.2f, String: %s", 42, 3.14, "Hello");

  return 0;
}