# Bit Manipulation

Tài liệu này cung cấp kiến thức nền tảng về thao tác bit (bit manipulation) trong ngôn ngữ lập trình C cho hệ thống nhúng (embedded systems), bao gồm các ví dụ code demo và bài tập thực hành.

## 📑 Mục lục

[1. 📁 Mô tả Code Demo](#-1-mô-tả-code-demo)

[1.1. Shift Operators](#11-shift-operators-shift-operatorsc)

[1.2. Bit Manipulation](#12-bit-manipulation-bit-manipulationc)

[1.3. Pack Data](#13-pack-data-pack-datac)

[2. 📚 Documentation](#-2-documentation)

[2.1. Các phép toán bit cơ bản](#21-các-phép-toán-bit-cơ-bản)

[2.2. Ứng dụng trong Embedded Systems](#22-ứng-dụng-trong-embedded-systems)

[2.3. Best Practices](#23-best-practices)

[3. 💪 Bài tập thực hành](#-3-bài-tập-thực-hành)

---

## 📁 1. Mô tả Code Demo

Thư mục `code-demo` chứa các ví dụ minh họa các kỹ thuật bit manipulation trong C:

### 1.1. Shift Operators (`shift-operators.c`)
**Mục đích:** Minh họa phép dịch bit trái (left shift) và dịch phải (right shift)

**Mô tả:** 
- Sử dụng giá trị 128 để demo
- **Left Shift (`<<`)**: Dịch bit sang trái, tương đương nhân với 2^n
- **Right Shift (`>>`)**: Dịch bit sang phải, tương đương chia cho 2^n
- Hiển thị kết quả dưới dạng binary để dễ quan sát

**Ví dụ:**
```c
uint8_t value = 128;  // 0b10000000
value << 2;           // 0b00000000 (overflow)
value >> 2;           // 0b00100000 (32)
```

### 1.2. Bit Manipulation (`bit-manipulation.c`)
**Mục đích:** Minh họa 4 phép toán bit cơ bản

**Mô tả:**
- **Set bit (OR)**: Bật một bit lên 1 mà không ảnh hưởng các bit khác
  ```c
  register |= (1 << position);
  ```
- **Clear bit (AND)**: Tắt một bit xuống 0 mà không ảnh hưởng các bit khác
  ```c
  register &= ~(1 << position);
  ```
- **Toggle bit (XOR)**: Đảo trạng thái bit (0→1, 1→0)
  ```c
  register ^= (1 << position);
  ```
- **Check bit (AND)**: Kiểm tra giá trị của một bit
  ```c
  if (register & (1 << position)) { /* bit is set */ }
  ```

### 1.3. Pack Data (`pack-data.c`)
**Mục đích:** Minh họa kỹ thuật đóng gói dữ liệu (data packing)

**Mô tả:**
- Đóng gói nhiều giá trị vào ít byte để tiết kiệm bộ nhớ và băng thông
- Ví dụ: Đóng gói 3 giá trị (mode: 3 bits, temp: 6 bits, error: 4 bits) vào 16 bits
- Sử dụng bit shifting và masking để pack/unpack dữ liệu
- Ứng dụng: Truyền dữ liệu qua giao thức IoT, lưu trữ cấu hình compact

**Layout ví dụ:**
```
16-bit packet: [error:4][temp:6][mode:3][reserved:3]
```

---

## 📚 2. Documentation

### 2.1. Các phép toán bit cơ bản

#### **A. Bitwise AND (`&`)**

**Công dụng:**
- Tắt (clear) các bit cụ thể
- Kiểm tra (check) giá trị bit
- Tạo mask để lọc dữ liệu

**Bảng chân trị:**
```
A | B | A & B
--|---|------
0 | 0 |   0
0 | 1 |   0
1 | 0 |   0
1 | 1 |   1
```

**Ví dụ:**
```c
// Clear bit 3
uint8_t reg = 0b11111111;
reg &= ~(1 << 3);  // Result: 0b11110111

// Check if bit 5 is set
if (reg & (1 << 5)) {
    printf("Bit 5 is set\n");
}
```

#### **B. Bitwise OR (`|`)**

**Công dụng:**
- Bật (set) các bit cụ thể
- Kết hợp nhiều flags

**Bảng chân trị:**
```
A | B | A | B
--|---|------
0 | 0 |   0
0 | 1 |   1
1 | 0 |   1
1 | 1 |   1
```

**Ví dụ:**
```c
// Set bit 2 and bit 4
uint8_t reg = 0b00000000;
reg |= (1 << 2);  // 0b00000100
reg |= (1 << 4);  // 0b00010100

// Combine flags
#define FLAG_A (1 << 0)
#define FLAG_B (1 << 1)
uint8_t flags = FLAG_A | FLAG_B;
```

#### **C. Bitwise XOR (`^`)**

**Công dụng:**
- Đảo (toggle) bit
- So sánh hai giá trị
- Mã hóa đơn giản

**Bảng chân trị:**
```
A | B | A ^ B
--|---|------
0 | 0 |   0
0 | 1 |   1
1 | 0 |   1
1 | 1 |   0
```

**Ví dụ:**
```c
// Toggle bit 3
uint8_t reg = 0b00001000;
reg ^= (1 << 3);  // 0b00000000 (toggle off)
reg ^= (1 << 3);  // 0b00001000 (toggle on)

// Simple encryption
uint8_t data = 0x42;
uint8_t key = 0xFF;
uint8_t encrypted = data ^ key;
uint8_t decrypted = encrypted ^ key;  // Back to 0x42
```

#### **D. Bitwise NOT (`~`)**

**Công dụng:**
- Đảo tất cả các bit
- Tạo mask đảo ngược

**Ví dụ:**
```c
uint8_t value = 0b00001111;
uint8_t inverted = ~value;  // 0b11110000
```

#### **E. Left Shift (`<<`)**

**Công dụng:**
- Nhân với 2^n
- Tạo bit mask
- Đóng gói dữ liệu

**Ví dụ:**
```c
uint8_t value = 5;      // 0b00000101
value = value << 2;     // 0b00010100 (20 = 5 * 2^2)

// Create mask for bit 3
uint8_t mask = (1 << 3);  // 0b00001000
```

#### **F. Right Shift (`>>`)**

**Công dụng:**
- Chia cho 2^n
- Trích xuất bits cao
- Giải nén dữ liệu

**Ví dụ:**
```c
uint8_t value = 20;     // 0b00010100
value = value >> 2;     // 0b00000101 (5 = 20 / 2^2)

// Extract high nibble
uint8_t data = 0xAB;
uint8_t high = (data >> 4) & 0x0F;  // 0x0A
```

---

### 2.2. Ứng dụng trong Embedded Systems

#### **A. Điều khiển thanh ghi phần cứng**

```c
// GPIO Register example
#define GPIOA_ODR  *((volatile uint32_t*)0x40020014)

// Set pin 5 high
GPIOA_ODR |= (1 << 5);

// Set pin 3 low
GPIOA_ODR &= ~(1 << 3);

// Toggle pin 7
GPIOA_ODR ^= (1 << 7);
```

#### **B. Cấu hình thiết bị ngoại vi**

```c
// UART Configuration Register
#define UART_CR1 *((volatile uint32_t*)0x40004400)

// Enable UART, TX, RX
UART_CR1 |= (1 << 13);  // UE: UART Enable
UART_CR1 |= (1 << 3);   // TE: Transmitter Enable
UART_CR1 |= (1 << 2);   // RE: Receiver Enable

// Set word length to 9 bits
UART_CR1 |= (1 << 12);  // M: Word length
```

#### **C. Đọc trạng thái cảm biến**

```c
// Sensor status register
uint8_t status = read_sensor_status();

// Check individual flags
bool data_ready = (status & (1 << 0)) != 0;
bool overrun = (status & (1 << 1)) != 0;
bool error = (status & (1 << 7)) != 0;

if (data_ready && !error) {
    read_sensor_data();
}
```

#### **D. Đóng gói dữ liệu truyền thông**

```c
// Pack sensor data into 2 bytes
typedef struct {
    uint16_t temperature : 10;  // 10 bits: 0-1023
    uint16_t humidity : 6;      // 6 bits: 0-63
} __attribute__((packed)) SensorData;

// Manual packing
uint16_t pack_data(uint16_t temp, uint8_t humidity) {
    uint16_t packet = 0;
    packet |= (temp & 0x3FF);           // Temperature in bits 0-9
    packet |= ((humidity & 0x3F) << 10); // Humidity in bits 10-15
    return packet;
}
```

#### **E. Tối ưu hóa bộ nhớ với bit fields**

```c
// LED control structure (only 1 byte instead of 8 bytes)
typedef struct {
    uint8_t led0 : 1;
    uint8_t led1 : 1;
    uint8_t led2 : 1;
    uint8_t led3 : 1;
    uint8_t led4 : 1;
    uint8_t led5 : 1;
    uint8_t led6 : 1;
    uint8_t led7 : 1;
} LEDControl;

LEDControl leds = {0};
leds.led3 = 1;  // Turn on LED 3
```

---

### 2.3. Best Practices

#### **1. Sử dụng macro cho bit positions**

```c
// ❌ Bad: Magic numbers
register |= (1 << 5);
register &= ~(1 << 3);

// ✅ Good: Named constants
#define LED_PIN 5
#define BUTTON_PIN 3

register |= (1 << LED_PIN);
register &= ~(1 << BUTTON_PIN);
```

#### **2. Sử dụng stdint.h cho portable code**

```c
// ✅ Good: Explicit size
#include <stdint.h>

uint8_t  reg8;   // Always 8 bits
uint16_t reg16;  // Always 16 bits
uint32_t reg32;  // Always 32 bits
```

#### **3. Sử dụng volatile cho hardware registers**

```c
// ✅ Good: Prevent compiler optimization
#define GPIO_ODR *((volatile uint32_t*)0x40020014)

// Compiler won't optimize away this read
uint32_t status = GPIO_ODR;
```

#### **4. Mask khi extract bits**

```c
// ❌ Bad: May include unwanted bits
uint8_t value = (data >> 3);

// ✅ Good: Mask to ensure clean data
uint8_t value = (data >> 3) & 0x0F;  // Only 4 bits
```

#### **5. Sử dụng parentheses trong macros**

```c
// ❌ Bad: Can cause unexpected behavior
#define SET_BIT(reg, bit) reg |= 1 << bit

// ✅ Good: Safe with parentheses
#define SET_BIT(reg, bit) ((reg) |= (1U << (bit)))
```

#### **6. Kiểm tra bit position hợp lệ**

```c
void set_bit(uint8_t *reg, uint8_t pos) {
    if (pos < 8) {  // Validate position
        *reg |= (1U << pos);
    }
}
```

#### **7. Sử dụng suffix U cho unsigned literals**

```c
// ✅ Good: Avoid signed/unsigned issues
#define BIT_MASK (1U << 7)  // Unsigned literal

// Especially important for bit 31 in 32-bit systems
#define BIT31 (1U << 31)  // Correct
// #define BIT31 (1 << 31)   // May cause undefined behavior
```

---

## 💪 3. Bài tập thực hành

Thư mục `exercise` chứa các bài tập để rèn luyện kỹ năng bit manipulation:

### **Bài tập 1: Điều khiển LED Matrix 8x8**
- **Độ khó:** Medium
- **Nội dung:** Implement các hàm set, clear, toggle, check bit để điều khiển LED
- **Kỹ năng:** Bit manipulation cơ bản, thao tác thanh ghi

### **Bài tập 2: Đóng gói dữ liệu cảm biến IoT**
- **Độ khó:** Medium/Hard
- **Nội dung:** Đóng gói 4 giá trị cảm biến vào 3 bytes để tiết kiệm băng thông
- **Kỹ năng:** Data packing, bit shifting phức tạp, masking

**File đáp án:** `exercise/answer.md` chứa giải pháp chi tiết và giải thích

---

## 🎯 Kết luận

Bit manipulation là kỹ năng quan trọng trong embedded programming:
- ✅ Hiểu rõ các phép toán bit: AND, OR, XOR, NOT, Shift
- ✅ Biết cách điều khiển thanh ghi phần cứng
- ✅ Tối ưu hóa bộ nhớ và băng thông
- ✅ Viết code portable và an toàn
- ✅ Sử dụng macro và constant hợp lý

**Nguyên tắc vàng:**
> "Luôn sử dụng mask khi extract bits và validate bit position!"

---

## 📖 Tài liệu tham khảo

- Code demo trong `code-demo/` để thực hành
- Bài tập trong `exercise/` để rèn luyện kỹ năng
- MISRA C Guidelines cho embedded systems
- ARM Cortex-M Programming Manual
