# **Bài tập 2 — Interrupt-driven Button Handler (Medium)**

## **Mục tiêu**

Hiểu cách sử dụng volatile variables và implement interrupt service routine (ISR) cho button handling.

## **Bối cảnh**

Bạn đang phát triển firmware cho một embedded device với 3 buttons. Mỗi button có ISR riêng để xử lý sự kiện nhấn. Main program cần phát hiện và xử lý các button press events.

## **Yêu cầu**

Viết chương trình C để:

1. Sử dụng `volatile` variables để chia sẻ dữ liệu giữa ISR và main
2. Simulate ISR cho 3 buttons
3. Implement debouncing logic
4. Đếm số lần nhấn mỗi button
5. Phát hiện long press (giữ button > 2 giây)

## **Dữ liệu vào**

Chuỗi các events:
```
BTN1_PRESS      // Button 1 pressed
BTN2_PRESS      // Button 2 pressed
BTN1_LONG       // Button 1 long press
STATUS          // Show button statistics
RESET           // Reset all counters
```

## **Dữ liệu ra**

```
[ISR] Button 1 pressed
Main: Detected button 1 press (count: 1)

[ISR] Button 1 long press
Main: Detected button 1 long press

STATUS:
  Button 1: 2 presses, 1 long press
  Button 2: 0 presses, 0 long press
  Button 3: 0 presses, 0 long press
```

## **Code khởi đầu**

```c
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* Volatile variables for ISR communication */
volatile bool btn1_pressed = false;
volatile bool btn2_pressed = false;
volatile bool btn3_pressed = false;
volatile bool btn1_long_press = false;

/* Button statistics */
int btn1_count = 0;
int btn2_count = 0;
int btn3_count = 0;
int btn1_long_count = 0;

/* ISR functions */
void button1_isr(void) {
    /* TODO: Set flag and print ISR message */
}

void button2_isr(void) {
    /* TODO: Set flag and print ISR message */
}

void button3_isr(void) {
    /* TODO: Set flag and print ISR message */
}

void button1_long_isr(void) {
    /* TODO: Set long press flag */
}

/* Simulate interrupt */
void simulate_interrupt(void (*isr)(void)) {
    isr();
}

void process_buttons(void) {
    /* TODO: Check flags and update counters */
    /* TODO: Clear flags after processing */
}

void print_status(void) {
    /* TODO: Print button statistics */
}

void reset_counters(void) {
    /* TODO: Reset all counters */
}

int main(void) {
    char event[20];
    
    while (scanf("%s", event) == 1) {
        if (strcmp(event, "BTN1_PRESS") == 0) {
            simulate_interrupt(button1_isr);
        } else if (strcmp(event, "BTN2_PRESS") == 0) {
            simulate_interrupt(button2_isr);
        } else if (strcmp(event, "BTN3_PRESS") == 0) {
            simulate_interrupt(button3_isr);
        } else if (strcmp(event, "BTN1_LONG") == 0) {
            simulate_interrupt(button1_long_isr);
        } else if (strcmp(event, "STATUS") == 0) {
            print_status();
        } else if (strcmp(event, "RESET") == 0) {
            reset_counters();
        }
        
        process_buttons();
    }
    
    return 0;
}
```

## **Gợi ý**

1. **Volatile keyword:**
   ```c
   volatile bool flag = false;  // Can be changed by ISR
   ```

2. **ISR best practices:**
   - Keep ISR short and fast
   - Only set flags, don't do heavy processing
   - Use volatile for shared variables

3. **Flag checking:**
   ```c
   if (btn1_pressed) {
       btn1_count++;
       btn1_pressed = false;  // Clear flag
   }
   ```

4. **Debouncing:**
   - Ignore multiple presses within short time
   - Use timestamp or counter

## **Bonus Challenge**

1. Implement double-click detection
2. Add button combination detection (BTN1 + BTN2)
3. Implement software debouncing với timer
4. Add priority levels cho interrupts
