# **Đáp án các bài tập về Pointer**

## **Bài tập 1 — Quản lý Buffer Ring sử dụng Con trỏ**

### **Giải thích thuật toán**

Ring buffer sử dụng 2 con trỏ:
- **head**: Vị trí ghi dữ liệu mới
- **tail**: Vị trí đọc dữ liệu

Khi con trỏ đến cuối buffer, nó quay về đầu (circular).

### **Code hoàn chỉnh**

```c
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_BUFFER_SIZE 100

typedef struct {
    uint8_t buffer[MAX_BUFFER_SIZE];
    uint8_t *head;
    uint8_t *tail;
    uint8_t *buffer_start;
    uint8_t *buffer_end;
    uint8_t size;
    uint8_t count;
} RingBuffer;

void buffer_init(RingBuffer *rb, uint8_t size) {
    rb->size = size;
    rb->count = 0;
    rb->buffer_start = rb->buffer;
    rb->buffer_end = rb->buffer + size;
    rb->head = rb->buffer_start;
    rb->tail = rb->buffer_start;
}

void buffer_write(RingBuffer *rb, uint8_t data) {
    *rb->head = data;
    
    // Move head pointer forward
    rb->head++;
    
    // Wrap around if reached end
    if (rb->head >= rb->buffer_end) {
        rb->head = rb->buffer_start;
    }
    
    // Update count
    if (rb->count < rb->size) {
        rb->count++;
    } else {
        // Buffer full, overwrite mode - move tail forward
        rb->tail++;
        if (rb->tail >= rb->buffer_end) {
            rb->tail = rb->buffer_start;
        }
    }
}

bool buffer_read(RingBuffer *rb, uint8_t *data) {
    if (rb->count == 0) {
        return false;
    }
    
    *data = *rb->tail;
    
    // Move tail pointer forward
    rb->tail++;
    
    // Wrap around if reached end
    if (rb->tail >= rb->buffer_end) {
        rb->tail = rb->buffer_start;
    }
    
    rb->count--;
    return true;
}

uint8_t buffer_available(RingBuffer *rb) {
    return rb->count;
}

bool buffer_is_empty(RingBuffer *rb) {
    return (rb->count == 0);
}

int main() {
    RingBuffer rb;
    uint8_t size;
    int m;
    
    scanf("%hhu", &size);
    buffer_init(&rb, size);
    
    scanf("%d", &m);
    
    for (int i = 0; i < m; i++) {
        char cmd;
        scanf(" %c", &cmd);
        
        if (cmd == 'W') {
            uint8_t value;
            scanf("%hhu", &value);
            buffer_write(&rb, value);
        } else if (cmd == 'R') {
            uint8_t data;
            if (buffer_read(&rb, &data)) {
                printf("%u\n", data);
            } else {
                printf("-1\n");
            }
        } else if (cmd == 'A') {
            printf("%u\n", buffer_available(&rb));
        } else if (cmd == 'E') {
            printf("%u\n", buffer_is_empty(&rb) ? 1 : 0);
        }
    }
    
    return 0;
}
```

### **Điểm chính**

1. **Pointer Arithmetic**: Sử dụng `ptr++` để di chuyển con trỏ
2. **Wrap Around**: Kiểm tra `if (ptr >= buffer_end)` để quay về đầu
3. **Overwrite Mode**: Khi buffer đầy, di chuyển cả head và tail

---

## **Bài tập 2 — State Machine sử dụng Function Pointer**

### **Giải thích thuật toán**

State machine sử dụng:
- Mảng function pointers để lưu state handlers
- Logic chuyển đổi trạng thái dựa trên bảng transition

### **Code hoàn chỉnh**

```c
#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef enum {
    STATE_IDLE = 0,
    STATE_CONNECTING,
    STATE_SENDING,
    STATE_ERROR,
    STATE_MAX
} State;

typedef enum {
    EVENT_CONNECT = 0,
    EVENT_CONNECTED,
    EVENT_TIMEOUT,
    EVENT_DATA_SENT,
    EVENT_ERROR_OCCURRED,
    EVENT_RESET,
    EVENT_MAX
} Event;

// Function pointer type for state handlers
typedef void (*StateHandler)(void);

// Current state
State current_state = STATE_IDLE;

// State handler functions
void state_idle_handler(void) {
    printf("IDLE\n");
}

void state_connecting_handler(void) {
    printf("CONNECTING\n");
}

void state_sending_handler(void) {
    printf("SENDING\n");
}

void state_error_handler(void) {
    printf("ERROR\n");
}

// Array of state handlers (function pointers)
StateHandler state_handlers[STATE_MAX] = {
    state_idle_handler,
    state_connecting_handler,
    state_sending_handler,
    state_error_handler
};

// State transition function
void handle_event(Event event) {
    State next_state = current_state;
    
    // RESET event can happen from any state
    if (event == EVENT_RESET) {
        next_state = STATE_IDLE;
    } else {
        // State transition logic based on current state and event
        switch (current_state) {
            case STATE_IDLE:
                if (event == EVENT_CONNECT) {
                    next_state = STATE_CONNECTING;
                } else if (event == EVENT_ERROR_OCCURRED) {
                    next_state = STATE_ERROR;
                }
                break;
                
            case STATE_CONNECTING:
                if (event == EVENT_CONNECTED) {
                    next_state = STATE_SENDING;
                } else if (event == EVENT_TIMEOUT) {
                    next_state = STATE_ERROR;
                }
                break;
                
            case STATE_SENDING:
                if (event == EVENT_DATA_SENT) {
                    next_state = STATE_IDLE;
                } else if (event == EVENT_ERROR_OCCURRED) {
                    next_state = STATE_ERROR;
                }
                break;
                
            case STATE_ERROR:
                // Already handled by RESET check above
                break;
                
            default:
                break;
        }
    }
    
    // Update state
    current_state = next_state;
    
    // Call state handler using function pointer
    state_handlers[current_state]();
}

Event parse_event(const char *event_str) {
    if (strcmp(event_str, "CONNECT") == 0) return EVENT_CONNECT;
    if (strcmp(event_str, "CONNECTED") == 0) return EVENT_CONNECTED;
    if (strcmp(event_str, "TIMEOUT") == 0) return EVENT_TIMEOUT;
    if (strcmp(event_str, "DATA_SENT") == 0) return EVENT_DATA_SENT;
    if (strcmp(event_str, "ERROR_OCCURRED") == 0) return EVENT_ERROR_OCCURRED;
    if (strcmp(event_str, "RESET") == 0) return EVENT_RESET;
    return EVENT_MAX;
}

int main() {
    int n;
    char event_str[20];
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%s", event_str);
        Event event = parse_event(event_str);
        
        if (event != EVENT_MAX) {
            handle_event(event);
        }
    }
    
    return 0;
}
```

### **Điểm chính**

1. **Function Pointer Array**: `StateHandler state_handlers[STATE_MAX]`
2. **Dynamic Function Call**: `state_handlers[current_state]()`
3. **State Transition Table**: Implement bằng switch-case
4. **Scalability**: Dễ dàng thêm state mới

---

## **Bài tập 3 — Callback System cho Sensor Events**

### **Giải thích thuật toán**

Callback system cho phép:
- Đăng ký nhiều callback cho mỗi sensor
- Khi event xảy ra, gọi tất cả callbacks đã đăng ký
- Sử dụng mảng function pointers để lưu callbacks

### **Code hoàn chỉnh**

```c
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_CALLBACKS 3
#define MAX_SENSORS 3

typedef enum {
    SENSOR_TEMP = 0,
    SENSOR_HUM,
    SENSOR_MOTION
} SensorType;

// Callback function type
typedef void (*SensorCallback)(int value);

// Callback storage
typedef struct {
    SensorCallback callbacks[MAX_CALLBACKS];
    uint8_t count;
} CallbackList;

CallbackList sensor_callbacks[MAX_SENSORS];

// Callback action functions
void callback_log(int value) {
    printf("Logging event\n");
}

void callback_alert(int value) {
    printf("Sending alert\n");
}

void callback_record(int value) {
    printf("Recording data\n");
}

// Get callback function by action ID
SensorCallback get_callback_by_action(int action_id) {
    switch (action_id) {
        case 1:
            return callback_log;
        case 2:
            return callback_alert;
        case 3:
            return callback_record;
        default:
            return NULL;
    }
}

// Register a callback for a sensor
void register_callback(SensorType sensor, SensorCallback callback) {
    if (sensor >= MAX_SENSORS) {
        return;
    }
    
    CallbackList *list = &sensor_callbacks[sensor];
    
    // Check if there's space
    if (list->count < MAX_CALLBACKS) {
        list->callbacks[list->count] = callback;
        list->count++;
    }
}

// Trigger event and call all registered callbacks
void trigger_event(SensorType sensor, int value) {
    if (sensor >= MAX_SENSORS) {
        return;
    }
    
    // Print sensor type and value
    printf("[%s] Value: %d\n", sensor_name(sensor), value);
    
    CallbackList *list = &sensor_callbacks[sensor];
    
    // Check if there are any callbacks
    if (list->count == 0) {
        printf("No callbacks registered\n");
        return;
    }
    
    // Call all registered callbacks
    for (int i = 0; i < list->count; i++) {
        if (list->callbacks[i] != NULL) {
            list->callbacks[i](value);
        }
    }
}

SensorType parse_sensor(const char *sensor_str) {
    if (strcmp(sensor_str, "TEMP") == 0) return SENSOR_TEMP;
    if (strcmp(sensor_str, "HUM") == 0) return SENSOR_HUM;
    if (strcmp(sensor_str, "MOTION") == 0) return SENSOR_MOTION;
    return SENSOR_TEMP;
}

const char* sensor_name(SensorType sensor) {
    switch(sensor) {
        case SENSOR_TEMP: return "TEMP";
        case SENSOR_HUM: return "HUM";
        case SENSOR_MOTION: return "MOTION";
        default: return "UNKNOWN";
    }
}

int main() {
    int n;
    char cmd[10], sensor_str[10];
    
    // Initialize callback lists
    for (int i = 0; i < MAX_SENSORS; i++) {
        sensor_callbacks[i].count = 0;
    }
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%s", cmd);
        
        if (strcmp(cmd, "REG") == 0) {
            int action_id;
            scanf("%s %d", sensor_str, &action_id);
            
            SensorType sensor = parse_sensor(sensor_str);
            SensorCallback callback = get_callback_by_action(action_id);
            
            if (callback != NULL) {
                register_callback(sensor, callback);
            }
        } else if (strcmp(cmd, "TRIGGER") == 0) {
            int value;
            scanf("%s %d", sensor_str, &value);
            
            SensorType sensor = parse_sensor(sensor_str);
            trigger_event(sensor, value);
        }
    }
    
    return 0;
}
```

### **Điểm chính**

1. **Callback Registration**: Lưu function pointers vào mảng
2. **Multiple Callbacks**: Mỗi sensor có thể có nhiều callbacks
3. **Dynamic Invocation**: Gọi callbacks trong vòng lặp
4. **Null Check**: Kiểm tra callback != NULL trước khi gọi

---

## **Tổng kết**

### **Kỹ năng đã học**

1. **Pointer Arithmetic**
   - Di chuyển con trỏ trong buffer
   - Wrap around trong circular buffer

2. **Function Pointers**
   - Khai báo và sử dụng function pointer
   - Mảng function pointers
   - Callback pattern

3. **Embedded Patterns**
   - Ring buffer cho UART
   - State machine cho IoT
   - Event-driven programming

### **Best Practices**

- ✅ Luôn kiểm tra NULL pointer
- ✅ Kiểm tra boundary conditions
- ✅ Sử dụng typedef cho function pointers
- ✅ Initialize callbacks trước khi sử dụng
- ✅ Comment rõ ràng logic phức tạp
