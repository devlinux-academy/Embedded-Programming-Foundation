#include <stdbool.h>
#include <stdio.h>

volatile bool button_pressed = false;
volatile int timer_count = 0;

void button_isr(void) {
  button_pressed = true;
  printf("   [ISR] Button interrupt!\n");
}

void timer_isr(void) {
  timer_count++;
  printf("   [ISR] Timer interrupt! Count: %d\n", timer_count);
}

void simulate_interrupt(void (*isr)(void)) {
  printf("   >>> Interrupt occurred <<<\n");
  isr();
  printf("   >>> ISR completed <<<\n");
}

int main(void) {
  printf("=== Interrupt Mechanism Demo ===\n\n");

  printf("1. Polling (BAD - wastes CPU):\n");
  printf("   while (button_flag == 0) { /* Wait */ }\n");
  printf("   Problem: 100%% CPU usage!\n\n");

  printf("2. Interrupt (GOOD - efficient):\n");
  printf("   Main program running...\n");

  simulate_interrupt(button_isr);

  if (button_pressed) {
    printf("   Main: Button was pressed!\n");
    button_pressed = false;
  }

  printf("\n3. Multiple interrupts:\n");
  printf("   Main program running...\n");

  simulate_interrupt(timer_isr);
  simulate_interrupt(timer_isr);
  simulate_interrupt(button_isr);

  printf("\n4. Interrupt steps:\n");
  printf("   Step 1: Event occurs (button press)\n");
  printf("   Step 2: CPU pauses main program\n");
  printf("   Step 3: Save context (registers)\n");
  printf("   Step 4: Jump to ISR\n");
  printf("   Step 5: Execute ISR (quick!)\n");
  printf("   Step 6: Restore context\n");
  printf("   Step 7: Resume main program\n");

  return 0;
}
