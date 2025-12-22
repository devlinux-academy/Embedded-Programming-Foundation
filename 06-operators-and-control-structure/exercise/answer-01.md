# **Đáp án Bài tập 1 — State Machine với Jump Table**

## **Code hoàn chỉnh**

```c
#include <stdio.h>
#include <string.h>

typedef enum {
    STATE_OFF,
    STATE_BLINK_SLOW,
    STATE_BLINK_FAST,
    STATE_ON,
    STATE_MAX
} LEDState;

const char *state_names[] = {
    "OFF",
    "BLINK_SLOW",
    "BLINK_FAST",
    "ON"
};

void state_off(void) {
    printf("Current state: %s\n", state_names[STATE_OFF]);
}

void state_blink_slow(void) {
    printf("Current state: %s\n", state_names[STATE_BLINK_SLOW]);
}

void state_blink_fast(void) {
    printf("Current state: %s\n", state_names[STATE_BLINK_FAST]);
}

void state_on(void) {
    printf("Current state: %s\n", state_names[STATE_ON]);
}

void (*state_handlers[])(void) = {
    state_off,
    state_blink_slow,
    state_blink_fast,
    state_on
};

LEDState current_state = STATE_OFF;

void handle_next(void) {
    current_state = (current_state + 1) % STATE_MAX;
}

void handle_prev(void) {
    current_state = (current_state - 1 + STATE_MAX) % STATE_MAX;
}

void handle_status(void) {
    printf("Current state: %s\n", state_names[current_state]);
}

int main(void) {
    char command[20];
    
    printf("Current state: OFF\n");
    
    while (scanf("%s", command) == 1) {
        printf("Command: %s\n", command);
        
        if (strcmp(command, "NEXT") == 0) {
            handle_next();
        } else if (strcmp(command, "PREV") == 0) {
            handle_prev();
        } else if (strcmp(command, "OFF") == 0) {
            current_state = STATE_OFF;
        } else if (strcmp(command, "STATUS") == 0) {
            handle_status();
            continue;
        }
        
        state_handlers[current_state]();
    }
    
    return 0;
}
```

## **Giải thích**

### 1. Jump Table Structure

```c
void (*state_handlers[])(void) = {
    state_off,
    state_blink_slow,
    state_blink_fast,
    state_on
};
```

- Mảng con trỏ hàm
- Mỗi phần tử trỏ đến một state handler
- Index tương ứng với enum value

### 2. State Transition

**Next state:**
```c
current_state = (current_state + 1) % STATE_MAX;
```
- Tăng state, wrap around về 0 khi đến STATE_MAX

**Previous state:**
```c
current_state = (current_state - 1 + STATE_MAX) % STATE_MAX;
```
- Giảm state, wrap around về STATE_MAX-1 khi < 0

### 3. Execute State Handler

```c
state_handlers[current_state]();
```
- Direct jump đến hàm xử lý - O(1)
- Không cần switch-case

## **Ví dụ chạy**

```
Current state: OFF
Command: NEXT
Current state: BLINK_SLOW
Command: NEXT
Current state: BLINK_FAST
Command: PREV
Current state: BLINK_SLOW
Command: OFF
Current state: OFF
```

## **Bonus: State Transition Validation**

```c
bool is_valid_transition(LEDState from, LEDState to) {
    // Không cho phép OFF → ON trực tiếp
    if (from == STATE_OFF && to == STATE_ON) {
        return false;
    }
    return true;
}

void handle_next(void) {
    LEDState next = (current_state + 1) % STATE_MAX;
    if (is_valid_transition(current_state, next)) {
        current_state = next;
    } else {
        printf("Invalid transition!\n");
    }
}
```
