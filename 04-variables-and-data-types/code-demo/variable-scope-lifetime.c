#include <stdint.h>
#include <stdio.h>

uint32_t g_counter = 0U;

void demo_local_variable(void) {
  uint32_t local_var = 10U;
  printf("Local variable: %u\n", local_var);
  local_var++;
}

void demo_static_variable(void) {
  static uint32_t static_var = 0U;
  static_var++;
  printf("Static variable: %u\n", static_var);
  /* static_var retains its value between function calls */
}

int main(void) {
  printf("=== Variable Scope and Lifetime Demo ===\n\n");

  printf("Global variable: %u\n", g_counter);
  g_counter = 100U;
  printf("Modified global: %u\n\n", g_counter);

  printf("Calling demo_local_variable() twice:\n");
  demo_local_variable();
  demo_local_variable();
  printf("\n");

  printf("Calling demo_static_variable() three times:\n");
  demo_static_variable();
  demo_static_variable();
  demo_static_variable();

  return 0;
}
