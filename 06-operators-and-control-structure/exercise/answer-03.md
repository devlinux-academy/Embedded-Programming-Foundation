# **Đáp án Bài tập 3 — Bit Manipulation và Control Flags**

## **Code hoàn chỉnh**

```c
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define SENSOR_ENABLE    (1 << 0)
#define DATA_READY       (1 << 1)
#define ERROR_FLAG       (1 << 2)
#define LOW_POWER_MODE   (1 << 3)
#define CALIBRATION_MODE (1 << 4)
#define INTERRUPT_ENABLE (1 << 5)
#define DEBUG_MODE       (1 << 6)
#define RESERVED         (1 << 7)

uint8_t system_flags = 0;

void set_flag(uint8_t flag) {
    system_flags |= flag;
}

void clear_flag(uint8_t flag) {
    system_flags &= ~flag;
}

void toggle_flag(uint8_t flag) {
    system_flags ^= flag;
}

bool check_flag(uint8_t flag) {
    return (system_flags & flag) != 0;
}

void set_multiple(uint8_t flags) {
    system_flags |= flags;
}

void clear_multiple(uint8_t flags) {
    system_flags &= ~flags;
}

void print_flags_binary(void) {
    printf("Flags: 0b");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (system_flags >> i) & 1);
    }
    printf("\n");
}

const char *flag_names[] = {
    "SENSOR_ENABLE",
    "DATA_READY",
    "ERROR_FLAG",
    "LOW_POWER_MODE",
    "CALIBRATION_MODE",
    "INTERRUPT_ENABLE",
    "DEBUG_MODE",
    "RESERVED"
};

void print_status(void) {
    printf("\nSTATUS:\n");
    for (int i = 0; i < 8; i++) {
        printf("  %-20s %s\n", 
               flag_names[i], 
               (system_flags & (1 << i)) ? "SET" : "CLEAR");
    }
}

uint8_t parse_flag(const char *name) {
    if (strcmp(name, "SENSOR_ENABLE") == 0) return SENSOR_ENABLE;
    if (strcmp(name, "DATA_READY") == 0) return DATA_READY;
    if (strcmp(name, "ERROR_FLAG") == 0) return ERROR_FLAG;
    if (strcmp(name, "LOW_POWER_MODE") == 0) return LOW_POWER_MODE;
    if (strcmp(name, "CALIBRATION_MODE") == 0) return CALIBRATION_MODE;
    if (strcmp(name, "INTERRUPT_ENABLE") == 0) return INTERRUPT_ENABLE;
    if (strcmp(name, "DEBUG_MODE") == 0) return DEBUG_MODE;
    if (strcmp(name, "RESERVED") == 0) return RESERVED;
    return 0;
}

bool validate_flags(void) {
    // Rule 1: ERROR_FLAG và CALIBRATION_MODE không cùng lúc
    if (check_flag(ERROR_FLAG) && check_flag(CALIBRATION_MODE)) {
        printf("Error: Cannot have ERROR_FLAG and CALIBRATION_MODE together\n");
        return false;
    }
    
    // Rule 2: LOW_POWER_MODE và DEBUG_MODE không cùng lúc
    if (check_flag(LOW_POWER_MODE) && check_flag(DEBUG_MODE)) {
        printf("Error: Cannot have LOW_POWER_MODE and DEBUG_MODE together\n");
        return false;
    }
    
    // Rule 3: CALIBRATION_MODE requires SENSOR_ENABLE
    if (check_flag(CALIBRATION_MODE) && !check_flag(SENSOR_ENABLE)) {
        printf("Error: CALIBRATION_MODE requires SENSOR_ENABLE\n");
        return false;
    }
    
    return true;
}

int main(void) {
    char command[20], flag_name[30];
    
    while (scanf("%s", command) == 1) {
        if (strcmp(command, "SET") == 0) {
            scanf("%s", flag_name);
            uint8_t flag = parse_flag(flag_name);
            set_flag(flag);
            printf("Set %s\n", flag_name);
            print_flags_binary();
            
        } else if (strcmp(command, "CLEAR") == 0) {
            scanf("%s", flag_name);
            uint8_t flag = parse_flag(flag_name);
            clear_flag(flag);
            printf("Clear %s\n", flag_name);
            print_flags_binary();
            
        } else if (strcmp(command, "TOGGLE") == 0) {
            scanf("%s", flag_name);
            uint8_t flag = parse_flag(flag_name);
            toggle_flag(flag);
            printf("Toggle %s\n", flag_name);
            print_flags_binary();
            
        } else if (strcmp(command, "CHECK") == 0) {
            scanf("%s", flag_name);
            uint8_t flag = parse_flag(flag_name);
            printf("Check %s: %s\n", flag_name, 
                   check_flag(flag) ? "SET" : "CLEAR");
            
        } else if (strcmp(command, "SET_MULTI") == 0) {
            scanf("%s", flag_name);
            char *token = strtok(flag_name, ",");
            uint8_t flags = 0;
            
            printf("Set multiple: ");
            while (token != NULL) {
                flags |= parse_flag(token);
                printf("%s ", token);
                token = strtok(NULL, ",");
            }
            printf("\n");
            
            set_multiple(flags);
            print_flags_binary();
            
        } else if (strcmp(command, "STATUS") == 0) {
            print_status();
            
        } else if (strcmp(command, "VALIDATE") == 0) {
            if (validate_flags()) {
                printf("Validation: PASSED\n");
            } else {
                printf("Validation: FAILED\n");
            }
        }
    }
    
    return 0;
}
```

## **Giải thích**

### 1. Bit Manipulation Operations

**Set a bit:**
```c
flags |= (1 << bit_position);
// Example: flags |= SENSOR_ENABLE;
```

**Clear a bit:**
```c
flags &= ~(1 << bit_position);
// Example: flags &= ~SENSOR_ENABLE;
```

**Toggle a bit:**
```c
flags ^= (1 << bit_position);
// Example: flags ^= SENSOR_ENABLE;
```

**Check a bit:**
```c
if (flags & (1 << bit_position)) { /* Set */ }
// Example: if (flags & SENSOR_ENABLE) { ... }
```

### 2. Multiple Flags Operations

**Set multiple:**
```c
flags |= (FLAG1 | FLAG2 | FLAG3);
```

**Clear multiple:**
```c
flags &= ~(FLAG1 | FLAG2 | FLAG3);
```

### 3. Binary Representation

```c
void print_flags_binary(void) {
    printf("Flags: 0b");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (system_flags >> i) & 1);
    }
    printf("\n");
}
```

## **Ví dụ chạy**

```
SET SENSOR_ENABLE
Set SENSOR_ENABLE
Flags: 0b00000001

SET DATA_READY
Set DATA_READY
Flags: 0b00000011

TOGGLE LOW_POWER_MODE
Toggle LOW_POWER_MODE
Flags: 0b00001011

CHECK SENSOR_ENABLE
Check SENSOR_ENABLE: SET

STATUS

STATUS:
  SENSOR_ENABLE        SET
  DATA_READY           SET
  ERROR_FLAG           CLEAR
  LOW_POWER_MODE       SET
  CALIBRATION_MODE     CLEAR
  INTERRUPT_ENABLE     CLEAR
  DEBUG_MODE           CLEAR
  RESERVED             CLEAR
```

## **Validation Rules**

```c
bool validate_flags(void) {
    // Rule 1: ERROR_FLAG và CALIBRATION_MODE conflict
    if (check_flag(ERROR_FLAG) && check_flag(CALIBRATION_MODE)) {
        return false;
    }
    
    // Rule 2: LOW_POWER_MODE và DEBUG_MODE conflict
    if (check_flag(LOW_POWER_MODE) && check_flag(DEBUG_MODE)) {
        return false;
    }
    
    // Rule 3: CALIBRATION_MODE requires SENSOR_ENABLE
    if (check_flag(CALIBRATION_MODE) && !check_flag(SENSOR_ENABLE)) {
        return false;
    }
    
    return true;
}
```

## **Bonus: Bit Field Alternative**

```c
typedef struct {
    uint8_t sensor_enable    : 1;
    uint8_t data_ready       : 1;
    uint8_t error_flag       : 1;
    uint8_t low_power_mode   : 1;
    uint8_t calibration_mode : 1;
    uint8_t interrupt_enable : 1;
    uint8_t debug_mode       : 1;
    uint8_t reserved         : 1;
} SystemFlags;

SystemFlags flags = {0};

// Usage
flags.sensor_enable = 1;
if (flags.data_ready) { ... }
```

**Trade-offs:**
- ✅ More readable
- ✅ Type-safe
- ❌ Less portable (bit order depends on compiler)
- ❌ Cannot take address of bit field
