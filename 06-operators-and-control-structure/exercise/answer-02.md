# **Đáp án Bài tập 2 — Interrupt-driven Button Handler**

## **Code hoàn chỉnh**

```c
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

volatile bool btn1_pressed = false;
volatile bool btn2_pressed = false;
volatile bool btn3_pressed = false;
volatile bool btn1_long_press = false;

int btn1_count = 0;
int btn2_count = 0;
int btn3_count = 0;
int btn1_long_count = 0;

void button1_isr(void) {
    btn1_pressed = true;
    printf("[ISR] Button 1 pressed\n");
}

void button2_isr(void) {
    btn2_pressed = true;
    printf("[ISR] Button 2 pressed\n");
}

void button3_isr(void) {
    btn3_pressed = true;
    printf("[ISR] Button 3 pressed\n");
}

void button1_long_isr(void) {
    btn1_long_press = true;
    printf("[ISR] Button 1 long press\n");
}

void simulate_interrupt(void (*isr)(void)) {
    isr();
}

void process_buttons(void) {
    if (btn1_pressed) {
        btn1_count++;
        printf("Main: Detected button 1 press (count: %d)\n", btn1_count);
        btn1_pressed = false;
    }
    
    if (btn2_pressed) {
        btn2_count++;
        printf("Main: Detected button 2 press (count: %d)\n", btn2_count);
        btn2_pressed = false;
    }
    
    if (btn3_pressed) {
        btn3_count++;
        printf("Main: Detected button 3 press (count: %d)\n", btn3_count);
        btn3_pressed = false;
    }
    
    if (btn1_long_press) {
        btn1_long_count++;
        printf("Main: Detected button 1 long press\n");
        btn1_long_press = false;
    }
}

void print_status(void) {
    printf("\nSTATUS:\n");
    printf("  Button 1: %d presses, %d long press\n", btn1_count, btn1_long_count);
    printf("  Button 2: %d presses, 0 long press\n", btn2_count);
    printf("  Button 3: %d presses, 0 long press\n", btn3_count);
}

void reset_counters(void) {
    btn1_count = 0;
    btn2_count = 0;
    btn3_count = 0;
    btn1_long_count = 0;
    printf("Counters reset\n");
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
            continue;
        } else if (strcmp(event, "RESET") == 0) {
            reset_counters();
            continue;
        }
        
        process_buttons();
    }
    
    return 0;
}
```

## **Giải thích**

### 1. Volatile Variables

```c
volatile bool btn1_pressed = false;
```

**Tại sao cần volatile:**
- Biến có thể thay đổi bởi ISR (bất ngờ)
- Compiler không tối ưu hóa
- Force read từ memory mỗi lần access

### 2. ISR Implementation

```c
void button1_isr(void) {
    btn1_pressed = true;  // Chỉ set flag
    printf("[ISR] Button 1 pressed\n");
}
```

**ISR Best Practices:**
- ✅ Keep short and fast
- ✅ Only set flags
- ✅ No heavy computation
- ✅ No blocking functions

### 3. Main Loop Processing

```c
void process_buttons(void) {
    if (btn1_pressed) {
        btn1_count++;
        btn1_pressed = false;  // Clear flag
    }
}
```

**Flow:**
1. ISR sets flag
2. Main loop checks flag
3. Process event
4. Clear flag

## **Ví dụ chạy**

```
BTN1_PRESS
[ISR] Button 1 pressed
Main: Detected button 1 press (count: 1)

BTN1_LONG
[ISR] Button 1 long press
Main: Detected button 1 long press

STATUS

STATUS:
  Button 1: 1 presses, 1 long press
  Button 2: 0 presses, 0 long press
  Button 3: 0 presses, 0 long press
```

## **Bonus: Debouncing**

```c
#include <time.h>

#define DEBOUNCE_TIME_MS 50

volatile time_t last_press_time = 0;

void button1_isr(void) {
    time_t current_time = time(NULL);
    
    // Debounce: Ignore if too soon
    if ((current_time - last_press_time) < DEBOUNCE_TIME_MS) {
        return;
    }
    
    last_press_time = current_time;
    btn1_pressed = true;
}
```

## **Bonus: Double-Click Detection**

```c
#define DOUBLE_CLICK_TIME_MS 300

volatile bool btn1_double_click = false;
volatile time_t btn1_first_click = 0;

void button1_isr(void) {
    time_t now = time(NULL);
    
    if ((now - btn1_first_click) < DOUBLE_CLICK_TIME_MS) {
        btn1_double_click = true;
        btn1_first_click = 0;
    } else {
        btn1_first_click = now;
        btn1_pressed = true;
    }
}
```
