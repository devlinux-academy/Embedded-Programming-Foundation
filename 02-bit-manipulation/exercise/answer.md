# Đáp án các bài tập Bit Manipulation

## **Bài tập 1 — Điều khiển LED Matrix 8x8**

### **Giải thích**

Bài tập này yêu cầu sử dụng 4 phép toán bit cơ bản:
1. **Set bit** (bật LED): Sử dụng OR với mask `(1 << position)`
2. **Clear bit** (tắt LED): Sử dụng AND với mask đảo `~(1 << position)`
3. **Toggle bit** (đảo LED): Sử dụng XOR với mask `(1 << position)`
4. **Check bit** (kiểm tra LED): Sử dụng AND và shift để lấy giá trị bit

### **Code đáp án**

```c
#include <stdio.h>
#include <stdint.h>

void set_led(uint8_t *port, uint8_t position) {
    *port |= (1 << position);
}

void clear_led(uint8_t *port, uint8_t position) {
    *port &= ~(1 << position);
}

void toggle_led(uint8_t *port, uint8_t position) {
    *port ^= (1 << position);
}

uint8_t check_led(uint8_t port, uint8_t position) {
    return (port >> position) & 1;
}

int main() {
    uint8_t led_port;
    int n;
    
    scanf("%hhu", &led_port);
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        char cmd;
        uint8_t pos;
        scanf(" %c %hhu", &cmd, &pos);
        
        if (cmd == 'S') {
            set_led(&led_port, pos);
        } else if (cmd == 'C') {
            clear_led(&led_port, pos);
        } else if (cmd == 'T') {
            toggle_led(&led_port, pos);
        } else if (cmd == 'Q') {
            printf("%u\n", check_led(led_port, pos));
        }
    }
    
    printf("%u\n", led_port);
    return 0;
}
```

### **Giải thích chi tiết**

#### **1. Set LED (Bật bit)**
```c
*port |= (1 << position);
```
- `(1 << position)`: Tạo mask có bit 1 tại vị trí `position`
- `|=`: OR với port để bật bit đó lên, không ảnh hưởng các bit khác

**Ví dụ**: Set bit 3 trong `0b00000000`
```
  0b00000000  (port ban đầu)
| 0b00001000  (1 << 3)
= 0b00001000  (kết quả)
```

#### **2. Clear LED (Tắt bit)**
```c
*port &= ~(1 << position);
```
- `(1 << position)`: Tạo mask có bit 1 tại vị trí `position`
- `~`: Đảo ngược mask → tất cả bit là 1, trừ vị trí `position` là 0
- `&=`: AND với port để tắt bit đó, không ảnh hưởng các bit khác

**Ví dụ**: Clear bit 3 trong `0b00001001`
```
  0b00001001  (port ban đầu)
& 0b11110111  (~(1 << 3))
= 0b00000001  (kết quả)
```

#### **3. Toggle LED (Đảo bit)**
```c
*port ^= (1 << position);
```
- `(1 << position)`: Tạo mask có bit 1 tại vị trí `position`
- `^=`: XOR với port để đảo bit đó (0→1, 1→0)

**Ví dụ**: Toggle bit 0 trong `0b00001001`
```
  0b00001001  (port ban đầu)
^ 0b00000001  (1 << 0)
= 0b00001000  (kết quả: bit 0 từ 1→0)
```

#### **4. Check LED (Kiểm tra bit)**
```c
return (port >> position) & 1;
```
- `port >> position`: Dịch bit cần kiểm tra về vị trí 0
- `& 1`: Lấy bit cuối cùng (mask với 0b00000001)

**Ví dụ**: Check bit 3 trong `0b00001000`
```
0b00001000 >> 3 = 0b00000001
0b00000001 & 1  = 1 (bit đang bật)
```

---

## **Bài tập 2 — Đóng gói dữ liệu cảm biến IoT**

### **Giải thích**

Bài tập này yêu cầu đóng gói 4 giá trị vào 3 bytes (24 bits):
- Battery: 7 bits (0-127)
- Temperature: 7 bits (offset +20 để lưu giá trị âm)
- Humidity: 7 bits (0-127)
- Status: 2 bits (0-3)

**Layout 24 bits:**
```
Byte 2: [Status:2][Humidity:6]
Byte 1: [Humidity:1][Temperature:7]
Byte 0: [Battery:7][Reserved:1]
```

### **Code đáp án**

```c
#include <stdio.h>
#include <stdint.h>

void pack_sensor_data(uint8_t battery, int8_t temp, uint8_t humidity, 
                      uint8_t status, uint8_t *byte0, uint8_t *byte1, uint8_t *byte2) {
    // Convert temperature to offset (add 20 to handle negative values)
    uint8_t temp_offset = (uint8_t)(temp + 20);
    
    // Byte 0: [Battery:7][Reserved:1]
    *byte0 = (battery & 0x7F) << 1;
    
    // Byte 1: [Humidity:1][Temperature:7]
    *byte1 = (temp_offset & 0x7F);
    *byte1 |= ((humidity & 0x01) << 7);
    
    // Byte 2: [Status:2][Humidity:6]
    *byte2 = ((humidity >> 1) & 0x3F);
    *byte2 |= ((status & 0x03) << 6);
}

void unpack_sensor_data(uint8_t byte0, uint8_t byte1, uint8_t byte2,
                        uint8_t *battery, int8_t *temp, uint8_t *humidity, uint8_t *status) {
    // Extract battery from byte 0
    *battery = (byte0 >> 1) & 0x7F;
    
    // Extract temperature from byte 1
    uint8_t temp_offset = byte1 & 0x7F;
    *temp = (int8_t)(temp_offset - 20);
    
    // Extract humidity from byte 1 and byte 2
    uint8_t humidity_low = (byte1 >> 7) & 0x01;
    uint8_t humidity_high = byte2 & 0x3F;
    *humidity = (humidity_high << 1) | humidity_low;
    
    // Extract status from byte 2
    *status = (byte2 >> 6) & 0x03;
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

### **Giải thích chi tiết**

#### **Packing (Đóng gói)**

**Input**: `battery=85, temp=25, humidity=60, status=1`

**Bước 1: Chuyển đổi temperature**
```c
temp_offset = 25 + 20 = 45 = 0b0101101
```

**Bước 2: Pack vào Byte 0**
```c
byte0 = (85 & 0x7F) << 1
      = 0b1010101 << 1
      = 0b10101010
      = 0xAA
```

**Bước 3: Pack vào Byte 1**
```c
// Temperature (7 bits thấp)
byte1 = 45 & 0x7F = 0b0101101

// Humidity bit thấp nhất (bit 7 của byte1)
byte1 |= (60 & 0x01) << 7
      = 0b0101101 | 0b00000000
      = 0b01011010
      = 0x5A
```

**Bước 4: Pack vào Byte 2**
```c
// Humidity 6 bits cao (bits 0-5 của byte2)
byte2 = (60 >> 1) & 0x3F
      = 30 & 0x3F
      = 0b0011110

// Status (bits 6-7 của byte2)
byte2 |= (1 & 0x03) << 6
      = 0b0011110 | 0b01000000
      = 0b01011100
      = 0x5C
```

**Kết quả**: `0xAA 0x5A 0x5C`

#### **Unpacking (Giải nén)**

**Input**: `byte0=0xAA, byte1=0x5A, byte2=0x5C`

**Bước 1: Extract Battery**
```c
battery = (0xAA >> 1) & 0x7F
        = 0b01010101 & 0x7F
        = 85
```

**Bước 2: Extract Temperature**
```c
temp_offset = 0x5A & 0x7F = 45
temp = 45 - 20 = 25
```

**Bước 3: Extract Humidity**
```c
humidity_low = (0x5A >> 7) & 0x01 = 0
humidity_high = 0x5C & 0x3F = 0b0011110 = 30
humidity = (30 << 1) | 0 = 60
```

**Bước 4: Extract Status**
```c
status = (0x5C >> 6) & 0x03
       = 0b01 = 1
```

**Kết quả**: `battery=85, temp=25, humidity=60, status=1` ✓

---

## **Kiến thức cần nhớ**

### **Các phép toán bit cơ bản**

1. **Set bit**: `value |= (1 << n)`
2. **Clear bit**: `value &= ~(1 << n)`
3. **Toggle bit**: `value ^= (1 << n)`
4. **Check bit**: `(value >> n) & 1`
5. **Extract bits**: `(value >> shift) & mask`
6. **Insert bits**: `value |= (data & mask) << shift`

### **Mask thông dụng**

- `0x01` = `0b00000001` - 1 bit
- `0x03` = `0b00000011` - 2 bits
- `0x07` = `0b00000111` - 3 bits
- `0x0F` = `0b00001111` - 4 bits
- `0x1F` = `0b00011111` - 5 bits
- `0x3F` = `0b00111111` - 6 bits
- `0x7F` = `0b01111111` - 7 bits
- `0xFF` = `0b11111111` - 8 bits
