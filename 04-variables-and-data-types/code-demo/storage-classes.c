#include <stdint.h>
#include <stdio.h>

uint32_t g_shared_data = 42U;

static uint32_t s_file_private = 100U;
extern uint32_t g_external_var;

volatile uint32_t *const HARDWARE_REG = (volatile uint32_t *)0x40000000UL;

static void private_function(void) {
  printf("This is a file-private function\n");
}

void demo_register_keyword(void) {
  register uint32_t fast_counter = 0U;

  for (fast_counter = 0U; fast_counter < 10U; fast_counter++) {
  }
  printf("Register variable demo completed\n");
}

void demo_volatile_keyword(void) {
  volatile uint32_t sensor_value = 0U;

  sensor_value = *HARDWARE_REG;
  sensor_value = *HARDWARE_REG;

  printf("Volatile demo: sensor = %u\n", sensor_value);
}

int main(void) {
  printf("=== Storage Classes Demo ===\n\n");

  /* Static keyword demo */
  printf("File-private static variable: %u\n", s_file_private);
  private_function();
  printf("\n");

  /* Register keyword demo */
  demo_register_keyword();
  printf("\n");

  /* Volatile keyword demo */
  printf("Volatile keyword prevents optimization\n");
  demo_volatile_keyword();

  return 0;
}