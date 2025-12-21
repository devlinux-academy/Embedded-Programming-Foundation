# Variables and Data Types in C

Tài liệu này cung cấp kiến thức nền tảng về biến (variables) và các kiểu dữ liệu (data types) trong ngôn ngữ lập trình C cho hệ thống nhúng (embedded systems), bao gồm các ví dụ code demo và kiến thức chuyên sâu về cách tổ chức và tối ưu hóa dữ liệu.

## 📑 Mục lục

[1. 📁 Mô tả Code Demo](#-1-mô-tả-code-demo)

[1.1. Variable Scope and Lifetime](#11-variable-scope-and-lifetime-variable-scope-lifetimec)

[1.2. Storage Classes](#12-storage-classes-storage-classesc)

[1.3. Structure Padding and Alignment](#13-structure-padding-and-alignment-struct-padding-alignmentc)

[1.4. Union Type Punning](#14-union-type-punning-union-type-punningc)

[1.5. Tagged Union](#15-tagged-union-union-taggedc)

[1.6. Enum Basic](#16-enum-basic-enum-basicc)

[2. 📚 Documentation](#-2-documentation)

[2.1. Giới thiệu biến và các kiểu dữ liệu](#21-giới-thiệu-biến-và-các-kiểu-dữ-liệu)

[2.2. Các thuộc tính của biến](#22-các-thuộc-tính-của-biến)

[2.3. Biến Local và Global](#23-biến-local-và-global)

[2.4. Từ khóa static, extern, volatile, register](#24-từ-khóa-static-extern-volatile-register)

[2.5. Structure](#25-structure)

[2.6. Union](#26-union)

[2.7. Enum](#27-enum)

[2.8. Best Practices](#28-best-practices)

---

## 📁 1. Mô tả Code Demo

Thư mục `code-demo` chứa các ví dụ minh họa các khái niệm về biến và kiểu dữ liệu trong C:

### 1.1. Variable Scope and Lifetime (`variable-scope-lifetime.c`)
**Mục đích:** Minh họa phạm vi hoạt động và vòng đời của biến

**Mô tả:**
- **Biến local**: Tồn tại trong phạm vi hàm, bị hủy khi hàm kết thúc
- **Biến global**: Tồn tại trong suốt chương trình, truy cập từ mọi nơi
- **Biến static local**: Giữ giá trị giữa các lần gọi hàm

**Ví dụ:**
```c
void demo_static_variable(void) {
    static uint32_t static_var = 0U;  /* Khởi tạo 1 lần */
    static_var++;  /* Giữ giá trị giữa các lần gọi */
}
```

### 1.2. Storage Classes (`storage-classes.c`)
**Mục đích:** Minh họa các từ khóa storage class

**Mô tả:**
- **static**: Hạn chế phạm vi file, giữ giá trị giữa các lần gọi
- **extern**: Khai báo biến được định nghĩa ở file khác
- **volatile**: Ngăn compiler tối ưu hóa (dùng cho hardware register)
- **register**: Gợi ý compiler lưu biến trong CPU register

**Ví dụ:**
```c
volatile uint32_t *const HARDWARE_REG = (volatile uint32_t *)0x40000000UL;
static uint32_t s_file_private = 100U;  /* File scope only */
```

### 1.3. Structure Padding and Alignment (`struct-padding-alignment.c`)
**Mục đích:** Minh họa padding và alignment trong structure

**Mô tả:**
- Compiler thêm padding bytes để đảm bảo alignment
- Thứ tự thành viên ảnh hưởng đến kích thước structure
- Sắp xếp từ lớn đến nhỏ để tối ưu bộ nhớ
- Attribute `packed` loại bỏ padding (có trade-off về hiệu năng)

**Ví dụ:**
```c
/* Unoptimized: 16 bytes */
struct { uint8_t a; uint32_t b; uint8_t c; uint16_t d; };

/* Optimized: 8 bytes */
struct { uint32_t b; uint16_t d; uint8_t a; uint8_t c; };
```

### 1.4. Union Type Punning (`union-type-punning.c`)
**Mục đích:** Minh họa kỹ thuật type punning với union

**Mô tả:**
- Union cho phép xem cùng một vùng nhớ dưới nhiều kiểu khác nhau
- Hữu ích cho chuyển đổi kiểu dữ liệu
- Ứng dụng: Float to bytes, IP address manipulation

**Ví dụ:**
```c
typedef union {
    float    float_value;
    uint32_t uint_value;
    uint8_t  bytes[4];
} FloatConverter;
```

### 1.5. Tagged Union (`union-tagged.c`)
**Mục đích:** Minh họa tagged union để tiết kiệm bộ nhớ

**Mô tả:**
- Tagged union = type tag + union
- Lưu trữ nhiều kiểu dữ liệu khác nhau trong cùng một vùng nhớ
- Tiết kiệm bộ nhớ đáng kể so với nhiều structure riêng biệt

**Ví dụ:**
```c
typedef struct {
    SensorType type;
    union {
        float temperature;
        float humidity;
        uint32_t pressure;
    } data;
} SensorReading;
```

### 1.6. Enum Basic (`enum-basic.c`)
**Mục đích:** Minh họa cú pháp và sử dụng enum cơ bản

**Mô tả:**
- Enum định nghĩa tập hợp các hằng số có tên
- Tự động gán giá trị tuần tự (0, 1, 2, ...)
- Có thể gán giá trị tùy chỉnh
- Tăng tính đọc hiểu code

**Ví dụ:**
```c
typedef enum {
    STATE_IDLE,      /* 0 */
    STATE_RUNNING,   /* 1 */
    STATE_PAUSED,    /* 2 */
    STATE_ERROR      /* 3 */
} SystemState;
```



---

## 📚 2. Documentation

### 2.1. Giới thiệu biến và các kiểu dữ liệu

#### **A. Biến là gì?**

**Biến (variable)** là một vùng nhớ được đặt tên, dùng để lưu trữ dữ liệu trong chương trình. Mỗi biến có:
- **Tên**: Định danh duy nhất
- **Kiểu dữ liệu**: Xác định kích thước và cách diễn giải dữ liệu
- **Địa chỉ**: Vị trí trong bộ nhớ
- **Giá trị**: Dữ liệu được lưu trữ

#### **B. Các kiểu dữ liệu cơ bản**

**Kiểu số nguyên:**

| Kiểu | Kích thước | Phạm vi (signed) | Phạm vi (unsigned) |
|------|------------|------------------|-------------------|
| `char` | 1 byte | -128 đến 127 | 0 đến 255 |
| `short` | 2 bytes | -32,768 đến 32,767 | 0 đến 65,535 |
| `int` | 4 bytes | -2³¹ đến 2³¹-1 | 0 đến 2³²-1 |
| `long` | 4/8 bytes | Phụ thuộc hệ thống | Phụ thuộc hệ thống |

**Kiểu số thực:**

| Kiểu | Kích thước | Độ chính xác |
|------|------------|--------------|
| `float` | 4 bytes | ~7 chữ số thập phân |
| `double` | 8 bytes | ~15 chữ số thập phân |

**Kiểu stdint.h (Embedded Systems):**

```c
#include <stdint.h>

uint8_t   u8;   /* Unsigned 8-bit: 0 to 255 */
int8_t    i8;   /* Signed 8-bit: -128 to 127 */
uint16_t  u16;  /* Unsigned 16-bit: 0 to 65535 */
int16_t   i16;  /* Signed 16-bit: -32768 to 32767 */
uint32_t  u32;  /* Unsigned 32-bit */
int32_t   i32;  /* Signed 32-bit */
```

**Lợi ích của stdint.h:**
- Kích thước cố định, không phụ thuộc platform
- Rõ ràng về signed/unsigned
- Tuân thủ MISRA-C cho embedded systems

---

### 2.2. Các thuộc tính của biến

Mỗi biến trong C có ba thuộc tính quan trọng:

#### **A. Vị trí lưu trữ (Storage Location)**

Biến có thể được lưu trữ ở các vùng nhớ khác nhau:

**1. Stack:**
- Biến local (auto variables)
- Tự động cấp phát và giải phóng
- Kích thước stack hạn chế (thường 1-8 KB trong embedded)

**2. Heap:**
- Bộ nhớ động (malloc/free)
- Kích thước linh hoạt
- Cần quản lý thủ công

**3. Data segment:**
- Biến global đã khởi tạo
- Biến static đã khởi tạo

**4. BSS segment:**
- Biến global chưa khởi tạo
- Biến static chưa khởi tạo
- Tự động khởi tạo = 0

**5. Register:**
- Lưu trong CPU register (nếu có)
- Truy cập nhanh nhất

#### **B. Phạm vi hoạt động (Scope)**

**Scope** xác định nơi biến có thể được truy cập:

**1. Block scope:**
```c
void function(void) {
    int x = 10;  /* Chỉ truy cập được trong hàm này */
    {
        int y = 20;  /* Chỉ truy cập trong block này */
    }
    /* y không tồn tại ở đây */
}
```

**2. File scope:**
```c
static int file_var = 100;  /* Chỉ truy cập trong file này */
```

**3. Global scope:**
```c
int global_var = 200;  /* Truy cập từ mọi file (với extern) */
```

#### **C. Vòng đời (Lifetime)**

**Lifetime** xác định khi nào biến được tạo và hủy:

**1. Automatic lifetime:**
```c
void function(void) {
    int local = 10;  /* Tạo khi vào hàm, hủy khi ra khỏi hàm */
}
```

**2. Static lifetime:**
```c
static int persistent = 0;  /* Tồn tại suốt chương trình */
```

**3. Dynamic lifetime:**
```c
int *ptr = malloc(sizeof(int));  /* Tồn tại đến khi free() */
free(ptr);
```

---

### 2.3. Biến Local và Global

#### **A. Biến Local**

**Đặc điểm:**
- Khai báo bên trong hàm hoặc block
- Chỉ truy cập được trong phạm vi khai báo
- Lưu trên stack
- Tự động hủy khi ra khỏi scope

**Ví dụ:**
```c
void calculate(void) {
    int result = 0;  /* Biến local */
    result = 10 + 20;
    /* result bị hủy khi hàm kết thúc */
}
```

**Ưu điểm:**
- Không chiếm bộ nhớ khi không dùng
- Tránh xung đột tên biến
- Dễ debug và maintain

**Nhược điểm:**
- Không giữ giá trị giữa các lần gọi hàm
- Stack có kích thước hạn chế

#### **B. Biến Global**

**Đặc điểm:**
- Khai báo bên ngoài tất cả hàm
- Truy cập từ mọi nơi trong chương trình
- Lưu trong data/BSS segment
- Tồn tại suốt chương trình

**Ví dụ:**
```c
uint32_t g_counter = 0;  /* Biến global */

void increment(void) {
    g_counter++;  /* Truy cập từ bất kỳ hàm nào */
}
```

**Ưu điểm:**
- Chia sẻ dữ liệu giữa các hàm
- Giữ trạng thái của chương trình

**Nhược điểm:**
- Chiếm bộ nhớ suốt chương trình
- Khó debug (nhiều nơi có thể thay đổi)
- Vi phạm encapsulation
- Không thread-safe

**Best Practice:**
```c
/* ✅ Good: Prefix với g_ để dễ nhận biết */
uint32_t g_system_state = 0;

/* ✅ Good: Dùng static để hạn chế scope */
static uint32_t s_file_private = 0;

/* ❌ Bad: Global không cần thiết */
int temp;  /* Nên dùng local */
```

---

### 2.4. Từ khóa static, extern, volatile, register

#### **A. Từ khóa static**

**Static có 2 ý nghĩa khác nhau tùy context:**

**1. Static với biến local:**
```c
void counter(void) {
    static uint32_t count = 0;  /* Khởi tạo 1 lần duy nhất */
    count++;
    printf("Count: %u\n", count);
}

/* Gọi hàm 3 lần:
   counter(); // Count: 1
   counter(); // Count: 2
   counter(); // Count: 3
*/
```

**Đặc điểm:**
- Giữ giá trị giữa các lần gọi hàm
- Khởi tạo 1 lần duy nhất
- Lưu trong data segment (không phải stack)

**2. Static với biến/hàm global:**
```c
/* file1.c */
static uint32_t s_private_var = 100;  /* Chỉ truy cập trong file1.c */

static void private_function(void) {
    /* Chỉ gọi được trong file1.c */
}
```

**Đặc điểm:**
- Hạn chế phạm vi trong file hiện tại
- Tránh xung đột tên với file khác
- Encapsulation tốt hơn

#### **B. Từ khóa extern**

**Extern** khai báo biến được định nghĩa ở file khác:

```c
/* file1.c */
uint32_t g_shared_data = 42;  /* Định nghĩa */

/* file2.c */
extern uint32_t g_shared_data;  /* Khai báo */

void use_shared_data(void) {
    printf("%u\n", g_shared_data);  /* Sử dụng */
}
```

**Lưu ý:**
- `extern` chỉ khai báo, không cấp phát bộ nhớ
- Phải có đúng 1 định nghĩa (không có `extern`)
- Thường đặt trong header file

**Best Practice:**
```c
/* config.h */
extern uint32_t g_system_config;

/* config.c */
uint32_t g_system_config = 0;  /* Định nghĩa thực tế */
```

#### **C. Từ khóa volatile**

**Volatile** báo cho compiler biết biến có thể thay đổi bất ngờ:

**Khi nào dùng volatile:**
1. Hardware registers
2. Biến được thay đổi trong ISR (Interrupt Service Routine)
3. Biến được chia sẻ giữa các threads
4. Memory-mapped I/O

**Ví dụ:**
```c
/* Hardware register */
volatile uint32_t *const UART_DATA = (volatile uint32_t *)0x40001000UL;

/* Biến trong ISR */
volatile uint8_t g_button_pressed = 0;

void button_isr(void) {
    g_button_pressed = 1;  /* Thay đổi trong ISR */
}

int main(void) {
    while (g_button_pressed == 0) {
        /* Compiler không tối ưu hóa vòng lặp này */
    }
}
```

**Tại sao cần volatile:**
```c
/* Không có volatile */
uint32_t status = *HARDWARE_REG;
status = *HARDWARE_REG;  /* Compiler có thể bỏ qua dòng này */

/* Có volatile */
volatile uint32_t status = *HARDWARE_REG;
status = *HARDWARE_REG;  /* Compiler PHẢI đọc lại */
```

#### **D. Từ khóa register**

**Register** gợi ý compiler lưu biến trong CPU register:

```c
void fast_loop(void) {
    register uint32_t i;
    
    for (i = 0; i < 1000000; i++) {
        /* Truy cập i rất nhanh */
    }
}
```

**Lưu ý:**
- Chỉ là gợi ý, compiler có thể bỏ qua
- Không thể lấy địa chỉ của register variable
- Modern compiler tự động tối ưu hóa, ít cần dùng `register`

**Hạn chế:**
```c
register int x = 10;
int *ptr = &x;  /* ❌ Lỗi: không thể lấy địa chỉ */
```

---

### 2.5. Structure

#### **A. Cú pháp cơ bản**

**Structure** nhóm nhiều biến khác kiểu thành một đơn vị:

```c
/* Định nghĩa structure */
struct Point {
    int x;
    int y;
};

/* Sử dụng */
struct Point p1;
p1.x = 10;
p1.y = 20;

/* Với typedef */
typedef struct {
    int x;
    int y;
} Point;

Point p2 = {10, 20};  /* Khởi tạo */
```

#### **B. Padding và Alignment**

**Alignment** là yêu cầu địa chỉ bộ nhớ phải chia hết cho một số nhất định:

**Quy tắc alignment:**
- `uint8_t`: 1-byte alignment (địa chỉ bất kỳ)
- `uint16_t`: 2-byte alignment (địa chỉ chẵn)
- `uint32_t`: 4-byte alignment (địa chỉ chia hết cho 4)
- `uint64_t`: 8-byte alignment (địa chỉ chia hết cho 8)

**Tại sao cần alignment:**
1. **Hiệu năng**: CPU đọc dữ liệu aligned nhanh hơn
2. **Yêu cầu phần cứng**: Một số CPU không cho phép unaligned access
3. **Atomic operations**: Yêu cầu aligned data

**Padding example:**
```c
typedef struct {
    uint8_t  a;   /* 1 byte */
    /* 3 bytes padding */
    uint32_t b;   /* 4 bytes */
    uint8_t  c;   /* 1 byte */
    /* 1 byte padding */
    uint16_t d;   /* 2 bytes */
} UnoptimizedStruct;  /* Total: 12 bytes */
```

**Memory layout:**
```
Offset  Content
0       a (1 byte)
1-3     padding (3 bytes)
4-7     b (4 bytes)
8       c (1 byte)
9       padding (1 byte)
10-11   d (2 bytes)
```

**Tối ưu hóa:**
```c
typedef struct {
    uint32_t b;   /* 4 bytes */
    uint16_t d;   /* 2 bytes */
    uint8_t  a;   /* 1 byte */
    uint8_t  c;   /* 1 byte */
} OptimizedStruct;  /* Total: 8 bytes */
```

**Memory layout:**
```
Offset  Content
0-3     b (4 bytes)
4-5     d (2 bytes)
6       a (1 byte)
7       c (1 byte)
```

**Packed structure:**
```c
typedef struct __attribute__((packed)) {
    uint8_t  a;
    uint32_t b;
    uint8_t  c;
    uint16_t d;
} PackedStruct;  /* Total: 8 bytes, no padding */
```

**Trade-offs của packed:**
- ✅ Tiết kiệm bộ nhớ
- ❌ Truy cập chậm hơn (unaligned access)
- ❌ Có thể không hoạt động trên một số CPU

#### **C. Bit Fields**

**Bit fields** cho phép chỉ định số bit cho mỗi thành viên:

**Cú pháp:**
```c
typedef struct {
    unsigned int field1 : 1;   /* 1 bit */
    unsigned int field2 : 3;   /* 3 bits */
    unsigned int field3 : 4;   /* 4 bits */
} BitFieldStruct;
```

**Ứng dụng: Hardware register mapping**
```c
typedef struct {
    uint32_t enable      : 1;   /* Bit 0 */
    uint32_t mode        : 2;   /* Bits 1-2 */
    uint32_t reserved1   : 5;   /* Bits 3-7 */
    uint32_t prescaler   : 8;   /* Bits 8-15 */
    uint32_t reserved2   : 16;  /* Bits 16-31 */
} TimerControlReg;

/* Sử dụng */
TimerControlReg *timer = (TimerControlReg *)0x40000000;
timer->enable = 1;
timer->mode = 2;
timer->prescaler = 64;
```

**Lưu ý:**
- Bit fields không có địa chỉ (không thể dùng `&`)
- Thứ tự bit phụ thuộc implementation (little-endian vs big-endian)
- Không portable giữa các compiler

---

### 2.6. Union

#### **A. Cú pháp cơ bản**

**Union** cho phép lưu nhiều kiểu dữ liệu khác nhau trong cùng vùng nhớ:

```c
typedef union {
    uint32_t u32;
    uint16_t u16;
    uint8_t  u8;
} DataUnion;

DataUnion data;
data.u32 = 0x12345678;
printf("u16 = 0x%04X\n", data.u16);  /* 0x5678 (little-endian) */
printf("u8 = 0x%02X\n", data.u8);    /* 0x78 */
```

**Kích thước union:**
```c
sizeof(DataUnion) == sizeof(uint32_t)  /* Bằng thành viên lớn nhất */
```

#### **B. Type Punning (Ép kiểu thông minh)**

**Type punning** xem cùng dữ liệu dưới nhiều kiểu khác nhau:

**Ví dụ 1: Float to bytes**
```c
typedef union {
    float    f;
    uint32_t u;
    uint8_t  bytes[4];
} FloatConverter;

FloatConverter conv;
conv.f = 3.14159f;

printf("Float: %f\n", conv.f);
printf("As uint32: 0x%08X\n", conv.u);
printf("Bytes: ");
for (int i = 0; i < 4; i++) {
    printf("%02X ", conv.bytes[i]);
}
```

**Ví dụ 2: IP address**
```c
typedef union {
    uint32_t ip_addr;
    struct {
        uint8_t octet1;
        uint8_t octet2;
        uint8_t octet3;
        uint8_t octet4;
    } octets;
} IPAddress;

IPAddress ip;
ip.ip_addr = 0xC0A80101;  /* 192.168.1.1 */
printf("%u.%u.%u.%u\n", 
       ip.octets.octet4, ip.octets.octet3,
       ip.octets.octet2, ip.octets.octet1);
```

#### **C. Tagged Union (Tiết kiệm bộ nhớ)**

**Tagged union** kết hợp type tag với union:

```c
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
} DataType;

typedef struct {
    DataType type;
    union {
        int i;
        float f;
        char *s;
    } data;
} TaggedData;

/* Sử dụng */
TaggedData value;
value.type = TYPE_FLOAT;
value.data.f = 3.14f;

/* Luôn kiểm tra type trước khi truy cập */
if (value.type == TYPE_FLOAT) {
    printf("Float: %f\n", value.data.f);
}
```

**Ứng dụng: Multi-sensor data**
```c
typedef enum {
    SENSOR_TEMP,
    SENSOR_HUMID,
    SENSOR_PRESSURE
} SensorType;

typedef struct {
    SensorType type;
    union {
        float temperature;
        float humidity;
        uint32_t pressure;
    } data;
} SensorReading;

/* Tiết kiệm bộ nhớ so với 3 structure riêng */
```

#### **D. Ánh xạ thanh ghi với nhiều "View"**

**Union** rất hữu ích cho hardware register mapping:

```c
typedef union {
    uint32_t reg;  /* Full 32-bit access */
    
    struct {
        uint32_t bit0  : 1;
        uint32_t bit1  : 1;
        /* ... */
        uint32_t bit31 : 1;
    } bits;  /* Individual bit access */
    
    struct {
        uint8_t byte0;
        uint8_t byte1;
        uint8_t byte2;
        uint8_t byte3;
    } bytes;  /* Byte access */
    
    struct {
        uint16_t low;
        uint16_t high;
    } words;  /* Word access */
} ControlRegister;

/* Sử dụng */
ControlRegister ctrl;
ctrl.reg = 0x12345678;           /* Write full register */
ctrl.bits.bit0 = 1;              /* Set individual bit */
ctrl.bytes.byte1 = 0xFF;         /* Modify byte */
uint16_t low_word = ctrl.words.low;  /* Read word */
```

---

### 2.7. Enum

#### **A. Cú pháp và khái niệm cơ bản**

**Enum** định nghĩa tập hợp các hằng số có tên:

```c
/* Enum cơ bản */
enum Color {
    RED,      /* 0 */
    GREEN,    /* 1 */
    BLUE      /* 2 */
};

/* Với typedef */
typedef enum {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_ERROR
} SystemState;

/* Sử dụng */
SystemState state = STATE_IDLE;
```

**Gán giá trị tùy chỉnh:**
```c
typedef enum {
    ERROR_NONE = 0,
    ERROR_TIMEOUT = -1,
    ERROR_INVALID = -2,
    ERROR_NO_MEMORY = -3
} ErrorCode;

typedef enum {
    LED_OFF = 0,
    LED_ON = 1,
    LED_BLINK_SLOW = 100,
    LED_BLINK_FAST = 500
} LEDMode;
```

#### **B. So sánh với Macro**

**Macro approach:**
```c
#define CMD_START  0
#define CMD_STOP   1
#define CMD_PAUSE  2
```

**Enum approach:**
```c
typedef enum {
    CMD_START,   /* Tự động = 0 */
    CMD_STOP,    /* Tự động = 1 */
    CMD_PAUSE    /* Tự động = 2 */
} Command;
```

**Ưu điểm của Enum:**

**1. Tự động gán giá trị:**
```c
/* Macro: Phải gán thủ công */
#define STATE_A 0
#define STATE_B 1
#define STATE_C 2
/* Nếu thêm STATE_D, phải đếm lại */

/* Enum: Tự động */
typedef enum {
    STATE_A,  /* 0 */
    STATE_B,  /* 1 */
    STATE_C,  /* 2 */
    STATE_D   /* 3 - tự động */
} State;
```

**2. Kiểu dữ liệu có tên:**
```c
/* Macro: Không có kiểu */
int cmd = CMD_START;  /* Chỉ là int */

/* Enum: Có kiểu riêng */
Command cmd = CMD_START;  /* Kiểu Command */
```

**3. Hỗ trợ Debug:**
- Debugger hiển thị tên enum thay vì số
- Dễ đọc hơn khi debug

**4. Type safety:**
```c
void execute_command(Command cmd) {
    /* Compiler kiểm tra kiểu */
}

execute_command(CMD_START);  /* ✅ OK */
execute_command(999);        /* ⚠️ Warning */
```

#### **C. Kích thước của Enum**

**Kích thước enum phụ thuộc compiler:**

```c
typedef enum {
    VALUE_A,
    VALUE_B,
    VALUE_C
} MyEnum;

sizeof(MyEnum);  /* Thường là 4 bytes (int) */
```

**Chỉ định kích thước (GCC):**
```c
typedef enum __attribute__((packed)) {
    VALUE_A,
    VALUE_B,
    VALUE_C
} CompactEnum;

sizeof(CompactEnum);  /* 1 byte */
```

**C11 standard:**
```c
enum MyEnum : uint8_t {  /* Chỉ định underlying type */
    VALUE_A,
    VALUE_B
};
```

---

### 2.8. Best Practices

#### **A. Naming Conventions**

```c
/* ✅ Good naming */
uint32_t g_global_counter;      /* Global: prefix g_ */
static uint32_t s_file_private; /* Static: prefix s_ */
volatile uint8_t v_isr_flag;    /* Volatile: prefix v_ */

typedef struct {
    uint32_t timestamp;
    uint16_t value;
} SensorData_t;  /* Type: suffix _t */

typedef enum {
    STATE_IDLE,
    STATE_RUNNING
} SystemState_e;  /* Enum: suffix _e */
```

#### **B. Memory Optimization**

```c
/* ✅ Good: Sắp xếp từ lớn đến nhỏ */
typedef struct {
    uint64_t timestamp;  /* 8 bytes */
    uint32_t value;      /* 4 bytes */
    uint16_t id;         /* 2 bytes */
    uint8_t  status;     /* 1 byte */
    uint8_t  flags;      /* 1 byte */
} OptimizedStruct;  /* 16 bytes */

/* ❌ Bad: Không sắp xếp */
typedef struct {
    uint8_t  status;     /* 1 byte + 7 padding */
    uint64_t timestamp;  /* 8 bytes */
    uint8_t  flags;      /* 1 byte + 3 padding */
    uint32_t value;      /* 4 bytes */
    uint16_t id;         /* 2 bytes + 6 padding */
} UnoptimizedStruct;  /* 32 bytes! */
```

#### **C. Const Correctness**

```c
/* ✅ Good: Dùng const để bảo vệ dữ liệu */
void process_data(const uint8_t *data, uint32_t size) {
    /* data không thể bị thay đổi */
}

/* ✅ Good: Const pointer to const data */
const uint8_t *const LUT = lookup_table;
```

#### **D. Volatile Usage**

```c
/* ✅ Good: Volatile cho hardware register */
volatile uint32_t *const UART_DATA = (volatile uint32_t *)0x40001000;

/* ✅ Good: Volatile cho ISR variable */
volatile uint8_t g_button_pressed = 0;

/* ❌ Bad: Volatile không cần thiết */
volatile int local_var = 10;  /* Local variable không cần volatile */
```

#### **E. MISRA-C Compliance**

**MISRA-C** là coding standard cho embedded systems:

```c
/* ✅ Good: Explicit type */
uint32_t value = 100U;  /* U suffix cho unsigned */

/* ✅ Good: Explicit cast */
uint16_t u16 = (uint16_t)value;

/* ✅ Good: Explicit comparison */
if (value != 0U) {  /* So sánh rõ ràng */
}

/* ❌ Bad: Implicit conversion */
uint16_t u16 = value;  /* MISRA violation */

/* ❌ Bad: Implicit boolean */
if (value) {  /* MISRA violation */
}
```

#### **F. Magic Numbers**

```c
/* ❌ Bad: Magic numbers */
if (status == 3) {
    /* 3 là gì? */
}

/* ✅ Good: Named constants */
typedef enum {
    STATUS_IDLE = 0,
    STATUS_BUSY = 1,
    STATUS_ERROR = 2,
    STATUS_READY = 3
} Status;

if (status == STATUS_READY) {
    /* Rõ ràng hơn */
}
```

---

## 📝 Tổng kết

Tài liệu này đã trình bày:

1. **Biến và kiểu dữ liệu cơ bản**: Các kiểu dữ liệu, kích thước, và cách sử dụng
2. **Thuộc tính biến**: Storage location, scope, lifetime
3. **Storage classes**: static, extern, volatile, register
4. **Structure**: Padding, alignment, bit fields, memory optimization
5. **Union**: Type punning, tagged union, register mapping
6. **Enum**: Cú pháp, so sánh với macro, best practices

**Key takeaways:**
- Hiểu rõ memory layout để tối ưu hóa bộ nhớ
- Sử dụng stdint.h cho embedded systems
- Áp dụng const và volatile đúng cách
- Tuân thủ MISRA-C cho code an toàn
- Sử dụng enum thay vì macro để tăng type safety

---

**Tài liệu tham khảo:**
- C Programming Language (K&R)
- MISRA-C:2012 Guidelines
- Embedded C Coding Standard
- ARM Cortex-M Programming Guide
