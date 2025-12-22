# **Bài tập 1 — State Machine với Jump Table (Medium)**

## **Mục tiêu**

Hiểu cách sử dụng jump table để implement state machine hiệu quả trong embedded systems.

## **Bối cảnh**

Bạn đang phát triển firmware cho một hệ thống LED có 4 trạng thái: OFF, BLINK_SLOW, BLINK_FAST, và ON. Hệ thống cần chuyển đổi giữa các trạng thái dựa trên input từ button.

## **Yêu cầu**

Viết chương trình C để:

1. Định nghĩa enum cho các trạng thái LED
2. Implement state machine bằng jump table (mảng con trỏ hàm)
3. Mỗi state có hàm xử lý riêng
4. Chuyển đổi state dựa trên command input
5. In ra trạng thái hiện tại sau mỗi lần chuyển đổi

## **Dữ liệu vào**

Chuỗi các command:
```
NEXT    // Chuyển sang state tiếp theo
PREV    // Quay lại state trước
OFF     // Chuyển về state OFF
STATUS  // Hiển thị state hiện tại
```

## **Dữ liệu ra**

```
Current state: OFF
Command: NEXT
Current state: BLINK_SLOW

Command: NEXT
Current state: BLINK_FAST

Command: STATUS
Current state: BLINK_FAST
```

## **Code khởi đầu**

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

/* TODO: Declare state handler functions */
void state_off(void);
void state_blink_slow(void);
void state_blink_fast(void);
void state_on(void);

/* TODO: Create jump table */
void (*state_handlers[])(void) = {
    /* Fill in function pointers */
};

LEDState current_state = STATE_OFF;

void handle_next(void) {
    /* TODO: Move to next state (wrap around) */
}

void handle_prev(void) {
    /* TODO: Move to previous state (wrap around) */
}

void handle_status(void) {
    /* TODO: Print current state */
}

int main(void) {
    char command[20];
    
    printf("Current state: OFF\n");
    
    while (scanf("%s", command) == 1) {
        printf("Command: %s\n", command);
        
        /* TODO: Handle commands */
        
        if (strcmp(command, "NEXT") == 0) {
            handle_next();
        } else if (strcmp(command, "PREV") == 0) {
            handle_prev();
        } else if (strcmp(command, "OFF") == 0) {
            current_state = STATE_OFF;
        } else if (strcmp(command, "STATUS") == 0) {
            handle_status();
        }
        
        /* TODO: Execute current state handler */
    }
    
    return 0;
}
```

## **Gợi ý**

1. **Jump table structure:**
   ```c
   void (*state_handlers[])(void) = {
       state_off,
       state_blink_slow,
       state_blink_fast,
       state_on
   };
   ```

2. **Execute state handler:**
   ```c
   state_handlers[current_state]();
   ```

3. **Wrap around logic:**
   ```c
   current_state = (current_state + 1) % STATE_MAX;
   ```

4. **State names array:**
   ```c
   const char *state_names[] = {
       "OFF", "BLINK_SLOW", "BLINK_FAST", "ON"
   };
   ```

## **Bonus Challenge**

1. Thêm transition validation (không cho phép chuyển từ OFF trực tiếp sang ON)
2. Thêm state entry/exit callbacks
3. Implement timeout cho mỗi state
4. Vẽ state diagram cho state machine
