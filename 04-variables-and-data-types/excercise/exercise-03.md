# **Bài tập 3 — Multi-Sensor Data Logger với Tagged Union (Medium)**

## **Mục tiêu**

Sử dụng tagged union để quản lý dữ liệu từ nhiều loại cảm biến khác nhau một cách hiệu quả về mặt bộ nhớ.

## **Bối cảnh**

Bạn đang phát triển hệ thống data logger cho IoT device. Hệ thống cần lưu trữ dữ liệu từ nhiều loại cảm biến:
- **Temperature sensor**: Nhiệt độ (float, °C)
- **Humidity sensor**: Độ ẩm (float, %)
- **Pressure sensor**: Áp suất (uint32_t, Pa)
- **GPS sensor**: Vị trí (latitude, longitude - float)
- **Accelerometer**: Gia tốc 3 trục (x, y, z - int16_t)

Sử dụng tagged union để tiết kiệm bộ nhớ thay vì tạo structure riêng cho mỗi loại.

## **Yêu cầu**

Viết chương trình C để:

1. Định nghĩa enum cho các loại cảm biến
2. Định nghĩa tagged union cho sensor readings
3. Implement các hàm:
   - `add_reading()` - Thêm một sensor reading
   - `print_reading()` - In thông tin một reading
   - `print_all_readings()` - In tất cả readings
   - `calculate_memory_usage()` - Tính toán bộ nhớ sử dụng

## **Dữ liệu vào**

- Dòng 1: Số lượng readings N (1 ≤ N ≤ 100)
- N dòng tiếp theo, mỗi dòng chứa:
  - `TEMP <value>` - Temperature reading
  - `HUMID <value>` - Humidity reading
  - `PRESS <value>` - Pressure reading
  - `GPS <lat> <lon>` - GPS reading
  - `ACCEL <x> <y> <z>` - Accelerometer reading

## **Dữ liệu ra**

In ra tất cả readings theo format:
```
Reading #<n>: <sensor_type> = <value>
...
Total readings: <n>
Memory usage: <bytes> bytes
Memory saved vs separate structures: <bytes> bytes
```

## **Ví dụ Input**

```
5
TEMP 25.5
HUMID 65.0
PRESS 101325
GPS 10.762622 106.660172
ACCEL 100 -50 980
```

## **Ví dụ Output**

```
Reading #1: Temperature = 25.50 °C
Reading #2: Humidity = 65.00 %
Reading #3: Pressure = 101325 Pa
Reading #4: GPS = (10.762622, 106.660172)
Reading #5: Accelerometer = (100, -50, 980)

Total readings: 5
Memory usage: 80 bytes
Memory saved vs separate structures: 60 bytes
```

## **Code khởi đầu**

```c
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX_READINGS 100

/* Sensor types */
typedef enum {
    SENSOR_TEMPERATURE,
    SENSOR_HUMIDITY,
    SENSOR_PRESSURE,
    SENSOR_GPS,
    SENSOR_ACCELEROMETER
} SensorType;

/* GPS data */
typedef struct {
    float latitude;
    float longitude;
} GPSData;

/* Accelerometer data */
typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} AccelData;

/* TODO: Define tagged union for sensor reading */
typedef struct {
    SensorType type;
    union {
        /* Define union members here */
    } data;
} SensorReading;

/* Global array of readings */
SensorReading g_readings[MAX_READINGS];
uint32_t g_reading_count = 0;

void add_temperature(float temp) {
    /* TODO: Add temperature reading */
}

void add_humidity(float humid) {
    /* TODO: Add humidity reading */
}

void add_pressure(uint32_t press) {
    /* TODO: Add pressure reading */
}

void add_gps(float lat, float lon) {
    /* TODO: Add GPS reading */
}

void add_accelerometer(int16_t x, int16_t y, int16_t z) {
    /* TODO: Add accelerometer reading */
}

void print_reading(const SensorReading *reading, uint32_t index) {
    printf("Reading #%u: ", index + 1);
    
    switch (reading->type) {
        case SENSOR_TEMPERATURE:
            /* TODO: Print temperature */
            break;
        case SENSOR_HUMIDITY:
            /* TODO: Print humidity */
            break;
        case SENSOR_PRESSURE:
            /* TODO: Print pressure */
            break;
        case SENSOR_GPS:
            /* TODO: Print GPS */
            break;
        case SENSOR_ACCELEROMETER:
            /* TODO: Print accelerometer */
            break;
    }
}

void print_all_readings(void) {
    for (uint32_t i = 0; i < g_reading_count; i++) {
        print_reading(&g_readings[i], i);
    }
}

void calculate_memory_usage(void) {
    /* TODO: Calculate and print memory usage */
}

int main(void) {
    uint32_t n;
    scanf("%u", &n);
    
    for (uint32_t i = 0; i < n; i++) {
        char sensor_type[10];
        scanf("%s", sensor_type);
        
        if (strcmp(sensor_type, "TEMP") == 0) {
            float temp;
            scanf("%f", &temp);
            add_temperature(temp);
        } else if (strcmp(sensor_type, "HUMID") == 0) {
            float humid;
            scanf("%f", &humid);
            add_humidity(humid);
        } else if (strcmp(sensor_type, "PRESS") == 0) {
            uint32_t press;
            scanf("%u", &press);
            add_pressure(press);
        } else if (strcmp(sensor_type, "GPS") == 0) {
            float lat, lon;
            scanf("%f %f", &lat, &lon);
            add_gps(lat, lon);
        } else if (strcmp(sensor_type, "ACCEL") == 0) {
            int16_t x, y, z;
            scanf("%hd %hd %hd", &x, &y, &z);
            add_accelerometer(x, y, z);
        }
    }
    
    printf("\n");
    print_all_readings();
    printf("\n");
    calculate_memory_usage();
    
    return 0;
}
```

## **Gợi ý**

1. Tagged union gồm: type tag + union of data
2. So sánh với cách dùng 5 mảng riêng biệt cho mỗi loại sensor
3. Memory saved = (separate structures size) - (tagged union size)
4. Luôn kiểm tra type tag trước khi truy cập union data
