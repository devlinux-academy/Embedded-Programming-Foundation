# **Bài tập 2 — Đóng gói dữ liệu cảm biến IoT (Medium/Hard)**

## **Mục tiêu**

Học cách đóng gói nhiều giá trị vào một byte/word để tiết kiệm băng thông truyền dữ liệu trong hệ thống IoT.

## **Bối cảnh**

Bạn đang phát triển firmware cho một cảm biến IoT chạy pin. Để tiết kiệm năng lượng và băng thông, bạn cần đóng gói nhiều thông tin vào ít byte nhất có thể.

Một gói dữ liệu cảm biến cần chứa:
- **Battery level**: 0-100 (cần 7 bits)
- **Temperature**: -20 đến 50°C, độ phân giải 1°C (cần 7 bits, lưu giá trị offset +20)
- **Humidity**: 0-100% (cần 7 bits)
- **Status**: 0-3 (2 bits: 0=OK, 1=Warning, 2=Error, 3=Critical)

Tổng cộng: 23 bits → có thể đóng gói vào 3 bytes (24 bits)

## **Yêu cầu**

Viết hai hàm:
1. `pack_sensor_data()` - Đóng gói 4 giá trị vào 3 bytes
2. `unpack_sensor_data()` - Giải nén 3 bytes ra 4 giá trị ban đầu

**Layout 24 bits:**
```
Byte 2: [Status:2][Humidity:6]
Byte 1: [Humidity:1][Temperature:7]
Byte 0: [Battery:7][Reserved:1]
```

## **Dữ liệu vào**

Một dòng chứa 4 số nguyên cách nhau bởi khoảng trắng:
```
battery temperature humidity status
```

Trong đó:
- `battery`: 0-100
- `temperature`: -20 đến 50
- `humidity`: 0-100
- `status`: 0-3

## **Dữ liệu ra**

- Dòng 1: 3 bytes đã đóng gói (dạng hex, cách nhau bởi khoảng trắng)
- Dòng 2-5: Các giá trị sau khi giải nén (để verify)

## **Ví dụ Input**

```
85 25 60 1
```

## **Ví dụ Output**

```
0xAA 0x5A 0x5C
85
25
60
1
```

## **Giải thích**

- Battery: 85 → `0b1010101` (7 bits)
- Temperature: 25 → offset = 25+20 = 45 → `0b0101101` (7 bits)
- Humidity: 60 → `0b0111100` (7 bits)
- Status: 1 → `0b01` (2 bits)

Đóng gói:
- Byte 0: `[1010101][0]` = 0xAA
- Byte 1: `[0][0101101]` = 0x5A
- Byte 2: `[01][0111100]` = 0x5C

## **Code khởi đầu**

```c
#include <stdio.h>
#include <stdint.h>

void pack_sensor_data(uint8_t battery, int8_t temp, uint8_t humidity, 
                      uint8_t status, uint8_t *byte0, uint8_t *byte1, uint8_t *byte2) {
    // TODO: Implement packing logic
    // Layout:
    // Byte 2: [Status:2][Humidity:6]
    // Byte 1: [Humidity:1][Temperature:7]
    // Byte 0: [Battery:7][Reserved:1]
}

void unpack_sensor_data(uint8_t byte0, uint8_t byte1, uint8_t byte2,
                        uint8_t *battery, int8_t *temp, uint8_t *humidity, uint8_t *status) {
    // TODO: Implement unpacking logic
}

int main() {
    uint8_t battery, humidity, status;
    int8_t temperature;
    
    scanf("%hhu %hhd %hhu %hhu", &battery, &temperature, &humidity, &status);
    
    uint8_t byte0, byte1, byte2;
    pack_sensor_data(battery, temperature, humidity, status, &byte0, &byte1, &byte2);
    
    printf("0x%02X 0x%02X 0x%02X\n", byte0, byte1, byte2);
    
    // Verify by unpacking
    uint8_t unpacked_battery, unpacked_humidity, unpacked_status;
    int8_t unpacked_temp;
    
    unpack_sensor_data(byte0, byte1, byte2, &unpacked_battery, &unpacked_temp, 
                       &unpacked_humidity, &unpacked_status);
    
    printf("%u\n%d\n%u\n%u\n", unpacked_battery, unpacked_temp, 
           unpacked_humidity, unpacked_status);
    
    return 0;
}
```
