# **Bài tập 1 — Tối ưu hóa Structure Padding (Medium)**

## **Mục tiêu**

Hiểu cách padding và alignment ảnh hưởng đến kích thước structure và cách tối ưu hóa bộ nhớ trong embedded systems.

## **Bối cảnh**

Bạn đang phát triển firmware cho một MCU có RAM hạn chế (chỉ 8KB). Bạn cần lưu trữ thông tin của nhiều cảm biến, mỗi cảm biến được biểu diễn bằng một structure. Việc tối ưu hóa kích thước structure sẽ giúp tiết kiệm bộ nhớ đáng kể.

## **Yêu cầu**

Cho một structure định nghĩa như sau:

```c
typedef struct {
    uint8_t  sensor_id;      /* 1 byte */
    uint32_t timestamp;      /* 4 bytes */
    uint8_t  status;         /* 1 byte */
    uint16_t value;          /* 2 bytes */
    uint8_t  checksum;       /* 1 byte */
} SensorData;
```

**Nhiệm vụ:**
1. Tính toán kích thước thực tế của structure trên (bao gồm padding)
2. Vẽ sơ đồ bộ nhớ cho structure, chỉ rõ vị trí padding bytes
3. Sắp xếp lại các thành viên để tối ưu hóa kích thước
4. Viết chương trình C để:
   - In ra kích thước của structure gốc
   - In ra offset của từng thành viên
   - In ra kích thước của structure đã tối ưu
   - Tính toán bộ nhớ tiết kiệm được khi lưu 100 cảm biến

## **Dữ liệu vào**

Không có input từ người dùng.

## **Dữ liệu ra**

```
Original Structure:
  sizeof(SensorData) = ? bytes
  offsetof(sensor_id) = ?
  offsetof(timestamp) = ?
  offsetof(status) = ?
  offsetof(value) = ?
  offsetof(checksum) = ?

Optimized Structure:
  sizeof(SensorDataOptimized) = ? bytes
  offsetof(timestamp) = ?
  offsetof(value) = ?
  offsetof(sensor_id) = ?
  offsetof(status) = ?
  offsetof(checksum) = ?

Memory saved for 100 sensors: ? bytes
```

## **Gợi ý**

1. Sử dụng `sizeof()` để lấy kích thước structure
2. Sử dụng `offsetof()` (từ `<stddef.h>`) để lấy offset của thành viên
3. Quy tắc alignment:
   - `uint8_t`: 1-byte alignment
   - `uint16_t`: 2-byte alignment
   - `uint32_t`: 4-byte alignment
4. Structure alignment = alignment của thành viên lớn nhất
5. Sắp xếp thành viên từ lớn đến nhỏ để giảm padding

## **Code khởi đầu**

```c
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

/* Original structure */
typedef struct {
    uint8_t  sensor_id;
    uint32_t timestamp;
    uint8_t  status;
    uint16_t value;
    uint8_t  checksum;
} SensorData;

/* TODO: Define optimized structure */
typedef struct {
    /* Rearrange members here */
} SensorDataOptimized;

int main(void) {
    printf("Original Structure:\n");
    printf("  sizeof(SensorData) = %zu bytes\n", sizeof(SensorData));
    printf("  offsetof(sensor_id) = %zu\n", offsetof(SensorData, sensor_id));
    printf("  offsetof(timestamp) = %zu\n", offsetof(SensorData, timestamp));
    printf("  offsetof(status) = %zu\n", offsetof(SensorData, status));
    printf("  offsetof(value) = %zu\n", offsetof(SensorData, value));
    printf("  offsetof(checksum) = %zu\n\n", offsetof(SensorData, checksum));
    
    /* TODO: Print optimized structure info */
    
    /* TODO: Calculate memory saved */
    
    return 0;
}
```

## **Bonus Challenge**

1. Sử dụng `__attribute__((packed))` để loại bỏ hoàn toàn padding
2. So sánh hiệu năng truy cập giữa packed và aligned structure
3. Giải thích khi nào nên dùng packed structure và khi nào không nên
