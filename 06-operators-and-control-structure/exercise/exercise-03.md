# **Bài tập 3 — Bit Manipulation và Control Flags (Hard)**

## **Mục tiêu**

Thành thạo bit manipulation operators và sử dụng bit flags để quản lý system state trong embedded systems.

## **Bối cảnh**

Bạn đang phát triển firmware cho một sensor module với 8 control flags được pack vào 1 byte. Mỗi bit đại diện cho một tính năng hoặc trạng thái khác nhau. Bạn cần implement các hàm để set, clear, toggle, và check các flags này.

## **Yêu cầu**

Viết chương trình C để:

1. Định nghĩa 8 flags bằng bit masks
2. Implement các hàm bit manipulation:
   - `set_flag()` - Set một flag
   - `clear_flag()` - Clear một flag
   - `toggle_flag()` - Toggle một flag
   - `check_flag()` - Kiểm tra flag có set không
   - `set_multiple()` - Set nhiều flags cùng lúc
   - `clear_multiple()` - Clear nhiều flags cùng lúc
3. In ra trạng thái của tất cả flags dưới dạng binary
4. Validate operations (không cho phép invalid flag combinations)

## **Flag Definitions**

```
Bit 0: SENSOR_ENABLE     - Enable/disable sensor
Bit 1: DATA_READY        - Data ready to read
Bit 2: ERROR_FLAG        - Error occurred
Bit 3: LOW_POWER_MODE    - Low power mode active
Bit 4: CALIBRATION_MODE  - Calibration in progress
Bit 5: INTERRUPT_ENABLE  - Interrupt enabled
Bit 6: DEBUG_MODE        - Debug mode active
Bit 7: RESERVED          - Reserved for future use
```

## **Dữ liệu vào**

Chuỗi các commands:
```
SET SENSOR_ENABLE
SET DATA_READY
CHECK SENSOR_ENABLE
TOGGLE LOW_POWER_MODE
CLEAR DATA_READY
SET_MULTI SENSOR_ENABLE,INTERRUPT_ENABLE
STATUS
```

## **Dữ liệu ra**

```
Set SENSOR_ENABLE
Flags: 0b00000001

Set DATA_READY
Flags: 0b00000011

Check SENSOR_ENABLE: SET

Toggle LOW_POWER_MODE
Flags: 0b00001011

Clear DATA_READY
Flags: 0b00001001

Set multiple: SENSOR_ENABLE, INTERRUPT_ENABLE
Flags: 0b00101001

STATUS:
  SENSOR_ENABLE:     SET
  DATA_READY:        CLEAR
  ERROR_FLAG:        CLEAR
  LOW_POWER_MODE:    SET
  CALIBRATION_MODE:  CLEAR
  INTERRUPT_ENABLE:  SET
  DEBUG_MODE:        CLEAR
  RESERVED:          CLEAR
```

## **Code khởi đầu**

```c
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

/* Bit flag definitions */
#define SENSOR_ENABLE    (1 << 0)
#define DATA_READY       (1 << 1)
#define ERROR_FLAG       (1 << 2)
#define LOW_POWER_MODE   (1 << 3)
#define CALIBRATION_MODE (1 << 4)
#define INTERRUPT_ENABLE (1 << 5)
#define DEBUG_MODE       (1 << 6)
#define RESERVED         (1 << 7)

/* Global flags register */
uint8_t system_flags = 0;

/* TODO: Implement bit manipulation functions */
void set_flag(uint8_t flag) {
    /* Set the specified flag */
}

void clear_flag(uint8_t flag) {
    /* Clear the specified flag */
}

void toggle_flag(uint8_t flag) {
    /* Toggle the specified flag */
}

bool check_flag(uint8_t flag) {
    /* Check if flag is set */
    return false;
}

void set_multiple(uint8_t flags) {
    /* Set multiple flags at once */
}

void clear_multiple(uint8_t flags) {
    /* Clear multiple flags at once */
}

void print_flags_binary(void) {
    /* TODO: Print flags in binary format */
    printf("Flags: 0b");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (system_flags >> i) & 1);
    }
    printf("\n");
}

void print_status(void) {
    /* TODO: Print status of all flags */
}

uint8_t parse_flag(const char *name) {
    /* TODO: Convert flag name to bit mask */
    if (strcmp(name, "SENSOR_ENABLE") == 0) return SENSOR_ENABLE;
    /* Add other flags */
    return 0;
}

int main(void) {
    char command[20], flag_name[30];
    
    while (scanf("%s", command) == 1) {
        if (strcmp(command, "SET") == 0) {
            scanf("%s", flag_name);
            /* TODO: Set flag */
        } else if (strcmp(command, "CLEAR") == 0) {
            scanf("%s", flag_name);
            /* TODO: Clear flag */
        } else if (strcmp(command, "TOGGLE") == 0) {
            scanf("%s", flag_name);
            /* TODO: Toggle flag */
        } else if (strcmp(command, "CHECK") == 0) {
            scanf("%s", flag_name);
            /* TODO: Check flag */
        } else if (strcmp(command, "STATUS") == 0) {
            print_status();
        }
    }
    
    return 0;
}
```

## **Gợi ý**

1. **Set a bit:**
   ```c
   flags |= (1 << bit_position);
   ```

2. **Clear a bit:**
   ```c
   flags &= ~(1 << bit_position);
   ```

3. **Toggle a bit:**
   ```c
   flags ^= (1 << bit_position);
   ```

4. **Check a bit:**
   ```c
   if (flags & (1 << bit_position)) { /* Set */ }
   ```

5. **Set multiple bits:**
   ```c
   flags |= (FLAG1 | FLAG2 | FLAG3);
   ```

## **Validation Rules**

1. Không cho phép set ERROR_FLAG và CALIBRATION_MODE cùng lúc
2. LOW_POWER_MODE và DEBUG_MODE không thể active cùng lúc
3. CALIBRATION_MODE requires SENSOR_ENABLE

## **Bonus Challenge**

1. Implement atomic bit operations (disable interrupts)
2. Add bit field structure alternative
3. Implement flag history (track last 10 changes)
4. Add CRC check cho flags register
5. Implement save/restore flags to EEPROM simulation
