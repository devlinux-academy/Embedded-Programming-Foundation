# **Bài tập 3 — Callback System cho Sensor Events (Hard)**

## **Mục tiêu**

Hiểu cách sử dụng function pointer để implement callback system cho xử lý sự kiện từ nhiều cảm biến trong hệ thống embedded.

## **Bối cảnh**

Bạn đang phát triển firmware cho một hệ thống giám sát có nhiều cảm biến:
- **Temperature Sensor**: Cảnh báo khi nhiệt độ vượt ngưỡng
- **Humidity Sensor**: Cảnh báo khi độ ẩm vượt ngưỡng
- **Motion Sensor**: Phát hiện chuyển động

Mỗi cảm biến có thể đăng ký nhiều callback functions để xử lý sự kiện. Khi cảm biến phát hiện event, tất cả callbacks đã đăng ký sẽ được gọi.

## **Yêu cầu**

Implement callback system với các chức năng:
- `register_callback()` - Đăng ký callback cho một loại sensor
- `trigger_event()` - Kích hoạt event từ sensor, gọi tất cả callbacks đã đăng ký
- Hỗ trợ tối đa 3 callbacks cho mỗi loại sensor

## **Sensor Types**

- `TEMP` - Temperature sensor (ID = 0)
- `HUM` - Humidity sensor (ID = 1)
- `MOTION` - Motion sensor (ID = 2)

## **Callback Actions**

Mỗi callback có một action ID:
- Action 1: `LOG` - In ra "Logging event"
- Action 2: `ALERT` - In ra "Sending alert"
- Action 3: `RECORD` - In ra "Recording data"

## **Dữ liệu vào**

- Dòng 1: Số lượng lệnh N
- N dòng tiếp theo, mỗi dòng chứa:
  - `REG sensor_type action_id` - Đăng ký callback
    - sensor_type: TEMP, HUM, hoặc MOTION
    - action_id: 1, 2, hoặc 3
  - `TRIGGER sensor_type value` - Kích hoạt event
    - sensor_type: TEMP, HUM, hoặc MOTION
    - value: Giá trị đo được

## **Dữ liệu ra**

Khi trigger event, in ra:
- Dòng 1: Tên sensor và giá trị (format: `[SENSOR_TYPE] Value: XX`)
- Các dòng tiếp theo: Kết quả từ mỗi callback đã đăng ký (theo thứ tự đăng ký)
- Nếu không có callback nào: In ra `No callbacks registered`

## **Ví dụ Input**

```
7
REG TEMP 1
REG TEMP 2
REG HUM 3
TRIGGER TEMP 35
TRIGGER HUM 80
REG MOTION 2
TRIGGER MOTION 1
```

## **Ví dụ Output**

```
[TEMP] Value: 35
Logging event
Sending alert
[HUM] Value: 80
Recording data
[MOTION] Value: 1
Sending alert
```

## **Giải thích**

- Đăng ký callback action 1 (LOG) cho TEMP
- Đăng ký callback action 2 (ALERT) cho TEMP
- Đăng ký callback action 3 (RECORD) cho HUM
- Trigger TEMP với value 35 → gọi 2 callbacks (LOG, ALERT)
- Trigger HUM với value 80 → gọi 1 callback (RECORD)
- Đăng ký callback action 2 (ALERT) cho MOTION
- Trigger MOTION với value 1 → gọi 1 callback (ALERT)

## **Code khởi đầu**

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
    // TODO: Return appropriate callback function based on action_id
    // 1 -> callback_log
    // 2 -> callback_alert
    // 3 -> callback_record
    return NULL;
}

// Register a callback for a sensor
void register_callback(SensorType sensor, SensorCallback callback) {
    // TODO: Add callback to sensor's callback list
    // Check if there's space (MAX_CALLBACKS)
}

// Trigger event and call all registered callbacks
void trigger_event(SensorType sensor, int value) {
    // TODO: Print sensor type and value
    // Call all registered callbacks for this sensor
    // If no callbacks, print "No callbacks registered"
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
