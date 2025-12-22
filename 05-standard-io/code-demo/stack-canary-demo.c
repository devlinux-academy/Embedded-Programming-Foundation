#include <stdio.h>
#include <string.h>

void vulnerable_function(void) {
  char buffer[16];
  int is_admin = 0;

  printf("Enter your name: ");
  gets(buffer);

  printf("Hello, %s!\n", buffer);
  printf("Admin status: %d\n", is_admin);

  if (is_admin) {
    printf("Access granted!\n");
  } else {
    printf("Access denied!\n");
  }
}

void safe_function(void) {
  char buffer[16];
  int is_admin = 0;

  printf("Enter your name (safe): ");
  fgets(buffer, sizeof(buffer), stdin);
  buffer[strcspn(buffer, "\n")] = 0;

  printf("Hello, %s!\n", buffer);
  printf("Admin status: %d\n", is_admin);

  if (is_admin) {
    printf("Access granted!\n");
  } else {
    printf("Access denied!\n");
  }
}

int main(void) {
  printf("=== Stack Canary Demo ===\n\n");
  printf("WARNING: This demonstrates buffer overflow vulnerability\n");

  printf("--- Test 1: Vulnerable Function ---\n");
  vulnerable_function();

  printf("\n--- Test 2: Safe Function ---\n");
  safe_function();

  return 0;
}
