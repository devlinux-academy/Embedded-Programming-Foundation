#include <stdint.h>
#include <stdio.h>

typedef enum {
  STATE_IDLE,
  STATE_RUNNING,
  STATE_PAUSED,
  STATE_ERROR
} SystemState;

typedef enum {
  LED_OFF = 0,
  LED_ON = 1,
  LED_BLINK_SLOW = 100,
  LED_BLINK_FAST = 500
} LEDMode;

typedef enum {
  ERROR_NONE = 0,
  ERROR_TIMEOUT = -1,
  ERROR_INVALID_PARAM = -2,
  ERROR_NO_MEMORY = -3,
  ERROR_HARDWARE_FAULT = -4
} ErrorCode;

const char *get_state_name(SystemState state) {
  switch (state) {
  case STATE_IDLE:
    return "IDLE";
  case STATE_RUNNING:
    return "RUNNING";
  case STATE_PAUSED:
    return "PAUSED";
  case STATE_ERROR:
    return "ERROR";
  default:
    return "UNKNOWN";
  }
}

int main(void) {
  printf("=== Enum Basic Demo ===\n\n");

  SystemState current_state = STATE_IDLE;
  printf("Current state: %s (value = %d)\n", get_state_name(current_state),
         current_state);

  current_state = STATE_RUNNING;
  printf("New state: %s (value = %d)\n\n", get_state_name(current_state),
         current_state);

  LEDMode led_mode = LED_BLINK_FAST;
  printf("LED mode: %d\n", led_mode);
  printf("LED_OFF = %d\n", LED_OFF);
  printf("LED_ON = %d\n", LED_ON);
  printf("LED_BLINK_SLOW = %d\n", LED_BLINK_SLOW);
  printf("LED_BLINK_FAST = %d\n\n", LED_BLINK_FAST);

  ErrorCode error = ERROR_TIMEOUT;
  printf("Error code: %d\n", error);

  if (error != ERROR_NONE) {
    printf("An error occurred!\n");
  }

  return 0;
}