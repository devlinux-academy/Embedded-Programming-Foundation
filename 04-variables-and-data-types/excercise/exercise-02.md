# **Bài tập 2 — Hardware Register Control với Bit Fields (Hard)**

## **Mục tiêu**

Sử dụng bit fields và union để ánh xạ và điều khiển hardware registers trong embedded systems.

## **Bối cảnh**

Bạn đang viết driver cho một Timer peripheral. Timer control register (32-bit) có cấu trúc như sau:

```
Bits 0-1:   MODE (00=Disabled, 01=OneShot, 10=Periodic, 11=PWM)
Bit 2:      ENABLE (0=Disabled, 1=Enabled)
Bit 3:      INTERRUPT_ENABLE (0=Disabled, 1=Enabled)
Bits 4-7:   PRESCALER (0-15, divides clock by 2^PRESCALER)
Bits 8-15:  DUTY_CYCLE (0-255, for PWM mode only)
Bits 16-31: RESERVED (must be 0)
```

## **Yêu cầu**

Viết chương trình C để:

1. Định nghĩa structure với bit fields cho timer control register
2. Định nghĩa union để có thể truy cập register dưới dạng:
   - 32-bit value (để đọc/ghi toàn bộ register)
   - Bit fields (để truy cập từng field)
3. Implement các hàm:
   - `timer_init()` - Khởi tạo timer
   - `timer_set_mode()` - Thiết lập chế độ
   - `timer_enable()` - Bật/tắt timer
   - `timer_set_prescaler()` - Thiết lập prescaler
   - `timer_set_pwm_duty()` - Thiết lập duty cycle cho PWM
   - `timer_print_config()` - In cấu hình hiện tại

## **Dữ liệu vào**

Một chuỗi các lệnh:
```
INIT
SET_MODE <mode>        // 0=Disabled, 1=OneShot, 2=Periodic, 3=PWM
ENABLE <0|1>
SET_PRESCALER <value>  // 0-15
SET_PWM_DUTY <value>   // 0-255
PRINT
```

## **Dữ liệu ra**

Với mỗi lệnh PRINT, in ra:
```
Timer Configuration:
  Register Value: 0x????????
  Mode: <mode_name>
  Enabled: <Yes|No>
  Interrupt: <Enabled|Disabled>
  Prescaler: <value> (Clock / <divisor>)
  PWM Duty: <value> (<percentage>%)
```

## **Ví dụ Input**

```
INIT
SET_MODE 3
ENABLE 1
SET_PRESCALER 4
SET_PWM_DUTY 128
PRINT
```

## **Ví dụ Output**

```
Timer Configuration:
  Register Value: 0x0000800C
  Mode: PWM
  Enabled: Yes
  Interrupt: Disabled
  Prescaler: 4 (Clock / 16)
  PWM Duty: 128 (50%)
```

## **Code khởi đầu**

```c
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* Timer modes */
typedef enum {
    TIMER_MODE_DISABLED = 0,
    TIMER_MODE_ONESHOT = 1,
    TIMER_MODE_PERIODIC = 2,
    TIMER_MODE_PWM = 3
} TimerMode;

/* TODO: Define bit field structure */
typedef struct {
    /* Define bit fields here */
} TimerControlBits;

/* TODO: Define union for register access */
typedef union {
    uint32_t reg;
    TimerControlBits bits;
} TimerControl;

/* Global timer control register */
TimerControl g_timer_ctrl;

void timer_init(void) {
    /* TODO: Initialize timer */
}

void timer_set_mode(TimerMode mode) {
    /* TODO: Set timer mode */
}

void timer_enable(uint8_t enable) {
    /* TODO: Enable/disable timer */
}

void timer_set_prescaler(uint8_t prescaler) {
    /* TODO: Set prescaler (0-15) */
}

void timer_set_pwm_duty(uint8_t duty) {
    /* TODO: Set PWM duty cycle (0-255) */
}

void timer_print_config(void) {
    /* TODO: Print timer configuration */
}

int main(void) {
    char cmd[20];
    
    while (scanf("%s", cmd) == 1) {
        if (strcmp(cmd, "INIT") == 0) {
            timer_init();
        } else if (strcmp(cmd, "SET_MODE") == 0) {
            uint32_t mode;
            scanf("%u", &mode);
            timer_set_mode((TimerMode)mode);
        } else if (strcmp(cmd, "ENABLE") == 0) {
            uint32_t enable;
            scanf("%u", &enable);
            timer_enable((uint8_t)enable);
        } else if (strcmp(cmd, "SET_PRESCALER") == 0) {
            uint32_t prescaler;
            scanf("%u", &prescaler);
            timer_set_prescaler((uint8_t)prescaler);
        } else if (strcmp(cmd, "SET_PWM_DUTY") == 0) {
            uint32_t duty;
            scanf("%u", &duty);
            timer_set_pwm_duty((uint8_t)duty);
        } else if (strcmp(cmd, "PRINT") == 0) {
            timer_print_config();
        }
    }
    
    return 0;
}
```

## **Gợi ý**

1. Bit fields được đánh số từ LSB (bit 0) đến MSB
2. Sử dụng union để truy cập cả register value và bit fields
3. Prescaler divides clock by 2^value (e.g., prescaler=4 → divisor=16)
4. PWM duty cycle: percentage = (duty / 255) * 100
