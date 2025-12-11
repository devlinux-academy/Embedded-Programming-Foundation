# **Bài tập 2 — State Machine sử dụng Function Pointer (Medium/Hard)**

## **Mục tiêu**

Học cách sử dụng con trỏ hàm (function pointer) để implement state machine cho hệ thống điều khiển thiết bị IoT.

## **Bối cảnh**

Bạn đang phát triển firmware cho một thiết bị IoT có 4 trạng thái hoạt động:
- **IDLE**: Chờ lệnh
- **CONNECTING**: Đang kết nối WiFi
- **SENDING**: Đang gửi dữ liệu
- **ERROR**: Lỗi, cần reset

Mỗi trạng thái có một hàm xử lý riêng. Hệ thống nhận các event và chuyển đổi trạng thái tương ứng.

## **State Transition Table**

| Current State | Event | Next State |
|--------------|-------|------------|
| IDLE | CONNECT | CONNECTING |
| IDLE | ERROR_OCCURRED | ERROR |
| CONNECTING | CONNECTED | SENDING |
| CONNECTING | TIMEOUT | ERROR |
| SENDING | DATA_SENT | IDLE |
| SENDING | ERROR_OCCURRED | ERROR |
| ERROR | RESET | IDLE |
| Any | RESET | IDLE |

## **Yêu cầu**

Implement state machine sử dụng:
- Mảng con trỏ hàm để lưu các state handler
- Bảng chuyển đổi trạng thái (state transition table)
- Mỗi state handler in ra tên trạng thái khi được gọi

## **Dữ liệu vào**

- Dòng 1: Số lượng event N (1 ≤ N ≤ 50)
- N dòng tiếp theo, mỗi dòng chứa một event:
  - `CONNECT` - Yêu cầu kết nối
  - `CONNECTED` - Kết nối thành công
  - `TIMEOUT` - Timeout kết nối
  - `DATA_SENT` - Dữ liệu đã gửi
  - `ERROR_OCCURRED` - Có lỗi xảy ra
  - `RESET` - Reset hệ thống

## **Dữ liệu ra**

Với mỗi event, in ra tên trạng thái sau khi xử lý event đó.

## **Ví dụ Input**

```
8
CONNECT
CONNECTED
DATA_SENT
CONNECT
TIMEOUT
RESET
CONNECT
CONNECTED
```

## **Ví dụ Output**

```
CONNECTING
SENDING
IDLE
CONNECTING
ERROR
IDLE
CONNECTING
SENDING
```

## **Giải thích**

- Ban đầu: IDLE
- Event CONNECT → CONNECTING
- Event CONNECTED → SENDING
- Event DATA_SENT → IDLE
- Event CONNECT → CONNECTING
- Event TIMEOUT → ERROR
- Event RESET → IDLE
- Event CONNECT → CONNECTING
- Event CONNECTED → SENDING

## **Code khởi đầu**

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
    // TODO: Implement state transition logic based on transition table
    // Update current_state based on event
    // Call appropriate state handler using function pointer
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
