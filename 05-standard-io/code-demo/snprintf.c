#include <stdio.h>
#include <string.h>

int main(void) {
  char buffer[50];
  int result;

  printf("=== snprintf Demo ===\n\n");

  result =
      snprintf(buffer, sizeof(buffer), "Hello, %s! Number: %d", "World", 42);
  printf("1. Basic usage:\n");
  printf("   Buffer: \"%s\"\n", buffer);
  printf("   Return value: %d\n", result);
  printf("   Buffer size: %zu\n\n", sizeof(buffer));

  result =
      snprintf(buffer, 10, "This is a very long string that will be truncated");
  printf("2. Truncation example:\n");
  printf("   Buffer (size 10): \"%s\"\n", buffer);
  printf("   Return value: %d (characters that would be written)\n", result);
  printf("   Actual length: %zu\n\n", strlen(buffer));

  result =
      snprintf(buffer, sizeof(buffer), "Pi = %.2f, Integer = %d", 3.14159, 100);
  printf("3. Multiple format specifiers:\n");
  printf("   Buffer: \"%s\"\n", buffer);
  printf("   Return value: %d\n\n", result);

  if (result >= 0 && result < (int)sizeof(buffer)) {
    printf("4. Safe check: String fits in buffer!\n");
  } else {
    printf("4. Warning: String was truncated!\n");
  }

  return 0;
}
