# Operators and Control Structures in C

Tài liệu này cung cấp kiến thức nền tảng về toán tử (operators) và cấu trúc điều khiển (control structures) trong ngôn ngữ lập trình C cho hệ thống nhúng (embedded systems).

## 📑 Mục lục

[1. 📁 Mô tả Code Demo](#-1-mô-tả-code-demo)

[1.1. Ternary Operator Demo](#11-ternary-operator-demo-ternary-operator-democ)

[1.2. Float Comparison](#12-float-comparison-float-comparisonc)

[1.3. Jump Table](#13-jump-table-jump-tablec)

[1.4. Interrupt Demo](#14-interrupt-demo-interrupt-democ)

[2. 📚 Documentation](#-2-documentation)

[2.1. Toán tử trong C](#21-toán-tử-trong-c)

[2.2. Toán tử 3 ngôi (Ternary Operator)](#22-toán-tử-3-ngôi-ternary-operator)

[2.3. So sánh số thực (Float Comparison)](#23-so-sánh-số-thực-float-comparison)

[2.4. Cấu trúc điều khiển](#24-cấu-trúc-điều-khiển)

[2.5. Jump Table](#25-jump-table)

[2.6. Interrupt Mechanism](#26-interrupt-mechanism)

[2.7. Best Practices](#27-best-practices)

---

## 📁 1. Mô tả Code Demo

### 1.1. Ternary Operator Demo (`ternary-operator-demo.c`)
**Mục đích:** Minh họa lỗi phổ biến khi sử dụng toán tử 3 ngôi

**Mô tả:**
- So sánh macro WRONG (không có dấu ngoặc) vs CORRECT (có dấu ngoặc)
- Demo operator precedence issues
- Ví dụ về MAX macro

**Ví dụ:**
```c
#define MAX_BAD(a, b) a > b ? a : b
#define MAX_GOOD(a, b) ((a) > (b) ? (a) : (b))

MAX_BAD(5 + 1, 10)   // = 15 (WRONG!)
MAX_GOOD(5 + 1, 10)  // = 10 (CORRECT)
```

### 1.2. Float Comparison (`float-comparison.c`)
**Mục đích:** Demo lỗi khi so sánh số thực và kỹ thuật epsilon

**Mô tả:**
- Vấn đề: `0.1 + 0.2 != 0.3` do sai số làm tròn
- Giải pháp: Sử dụng epsilon để so sánh
- `fabs(a - b) < EPSILON`

**Ví dụ:**
```c
#define EPSILON 0.00001f

float a = 0.1f + 0.2f;
float b = 0.3f;

// WRONG
if (a == b) { /* Never true! */ }

// CORRECT
if (fabs(a - b) < EPSILON) { /* Works! */ }
```

### 1.3. Jump Table (`jump-table.c`)
**Mục đích:** So sánh switch-case vs jump table

**Mô tả:**
- Jump table: Mảng con trỏ hàm
- Độ phức tạp: O(1) vs O(n)
- Hiệu quả cho nhiều cases liên tiếp

**Ví dụ:**
```c
void (*jump_table[])(void) = {
    case_0,
    case_1,
    case_2
};

// Direct jump - O(1)
jump_table[value]();
```

### 1.4. Interrupt Demo (`interrupt-demo.c`)
**Mục đích:** Minh họa cơ chế interrupt vs polling

**Mô tả:**
- Polling: Lãng phí CPU (100% usage)
- Interrupt: Hiệu quả, chỉ xử lý khi cần
- ISR (Interrupt Service Routine)
- Volatile variables

**Ví dụ:**
```c
volatile bool button_pressed = false;

void button_isr(void) {
    button_pressed = true;  // Set flag
}

int main(void) {
    while (1) {
        if (button_pressed) {
            // Handle event
            button_pressed = false;
        }
    }
}
```

---

## 📚 2. Documentation

### 2.1. Toán tử trong C

#### **A. Phân loại Toán tử**

**1. Toán tử số học:**
- `+`, `-`, `*`, `/`, `%`

**2. Toán tử quan hệ:**
- `==`, `!=`, `>`, `<`, `>=`, `<=`

**3. Toán tử logic:**
- `&&` (AND), `||` (OR), `!` (NOT)

**4. Toán tử thao tác bit:**
- `&` (AND), `|` (OR), `^` (XOR), `~` (NOT)
- `<<` (Left shift), `>>` (Right shift)

**5. Toán tử gán:**
- `=`, `+=`, `-=`, `*=`, `/=`, `%=`
- `&=`, `|=`, `^=`, `<<=`, `>>=`

**6. Toán tử 3 ngôi:**
- `condition ? value_if_true : value_if_false`

#### **B. Operator Precedence**

Thứ tự ưu tiên (cao → thấp):

| Precedence | Operators | Associativity |
|------------|-----------|---------------|
| 1 | `()`, `[]`, `->`, `.` | Left to right |
| 2 | `!`, `~`, `++`, `--`, `+`, `-` (unary) | Right to left |
| 3 | `*`, `/`, `%` | Left to right |
| 4 | `+`, `-` | Left to right |
| 5 | `<<`, `>>` | Left to right |
| 6 | `<`, `<=`, `>`, `>=` | Left to right |
| 7 | `==`, `!=` | Left to right |
| 8 | `&` | Left to right |
| 9 | `^` | Left to right |
| 10 | `|` | Left to right |
| 11 | `&&` | Left to right |
| 12 | `||` | Left to right |
| 13 | `?:` | Right to left |
| 14 | `=`, `+=`, `-=`, etc. | Right to left |

---

### 2.2. Toán tử 3 ngôi (Ternary Operator)

#### **A. Cú pháp**

```c
condition ? value_if_true : value_if_false;
```

#### **B. Ví dụ cơ bản**

```c
int max = (a > b) ? a : b;
int abs_value = (x >= 0) ? x : -x;
```

#### **C. Lỗi phổ biến - Thiếu dấu ngoặc**

**WRONG:**
```c
#define MAX(a, b) a > b ? a : b

int result = MAX(x + 1, y);
// Expands to: x + 1 > y ? x + 1 : y
// = x + (1 > y ? x + 1 : y)  // WRONG!
```

**CORRECT:**
```c
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int result = MAX(x + 1, y);
// Expands to: ((x + 1) > (y) ? (x + 1) : (y))  // CORRECT!
```

#### **D. Khi nào dùng**

**✅ Good use cases:**
- Simple conditional assignments
- Return values
- Function arguments

**❌ Avoid:**
- Complex nested ternary (hard to read)
- Side effects in expressions

---

### 2.3. So sánh số thực (Float Comparison)

#### **A. Vấn đề**

Máy tính biểu diễn số thực ở dạng nhị phân → Sai số làm tròn

```c
float a = 0.1f + 0.2f;  // 0.30000000000000004
float b = 0.3f;         // 0.29999999999999999

if (a == b) {  // FALSE!
    // Never executes
}
```

#### **B. Giải pháp - Kỹ thuật Epsilon**

```c
#define EPSILON 0.00001f

bool float_equal(float a, float b) {
    return fabs(a - b) < EPSILON;
}

if (float_equal(a, b)) {
    // Works correctly!
}
```

#### **C. Chọn giá trị Epsilon**

- **General purpose**: `1e-5` (0.00001)
- **High precision**: `1e-9` (0.000000001)
- **Low precision**: `1e-3` (0.001)

**Lưu ý:** Epsilon phụ thuộc vào độ lớn của số:

```c
bool float_equal_relative(float a, float b) {
    float diff = fabs(a - b);
    float max_val = fmax(fabs(a), fabs(b));
    return diff < (EPSILON * max_val);
}
```

---

### 2.4. Cấu trúc điều khiển

#### **A. If-Else**

```c
if (condition) {
    // Code
} else if (another_condition) {
    // Code
} else {
    // Code
}
```

#### **B. Switch-Case**

```c
switch (value) {
    case 0:
        // Code
        break;
    case 1:
        // Code
        break;
    default:
        // Code
        break;
}
```

**Lưu ý:**
- Luôn có `break` (trừ khi muốn fall-through)
- Luôn có `default` case

#### **C. Loops**

**For loop:**
```c
for (int i = 0; i < 10; i++) {
    // Code
}
```

**While loop:**
```c
while (condition) {
    // Code
}
```

**Do-While loop:**
```c
do {
    // Code
} while (condition);
```

---

### 2.5. Jump Table

#### **A. Khái niệm**

Jump table là mảng con trỏ hàm, cho phép nhảy trực tiếp đến hàm xử lý dựa trên index.

#### **B. So sánh với Switch-Case**

| Aspect | Switch-Case | Jump Table |
|--------|-------------|------------|
| Complexity | O(n) | O(1) |
| Code size | Larger | Smaller |
| Flexibility | Limited | High |
| Compiler optimization | May create jump table | Direct jump table |

#### **C. Implementation**

```c
// Define handler functions
void case_0(void) { printf("Case 0\n"); }
void case_1(void) { printf("Case 1\n"); }
void case_2(void) { printf("Case 2\n"); }

// Create jump table
void (*jump_table[])(void) = {
    case_0,
    case_1,
    case_2
};

// Use jump table
int value = 1;
if (value >= 0 && value < 3) {
    jump_table[value]();  // Direct jump - O(1)
}
```

#### **D. Khi nào dùng Jump Table**

**✅ Good for:**
- Many sequential cases (0, 1, 2, 3, ...)
- Performance-critical code
- State machines
- Command dispatchers

**❌ Avoid when:**
- Sparse cases (0, 100, 1000, ...)
- Few cases (< 5)
- Cases not sequential

---

### 2.6. Interrupt Mechanism

#### **A. Polling vs Interrupt**

**Polling (BAD):**
```c
while (button_flag == 0) {
    // Busy waiting - 100% CPU!
}
```

**Interrupt (GOOD):**
```c
volatile bool button_pressed = false;

void button_isr(void) {
    button_pressed = true;
}

int main(void) {
    while (1) {
        if (button_pressed) {
            // Handle event
            button_pressed = false;
        }
        // Do other work - efficient!
    }
}
```

#### **B. Interrupt Flow**

1. **Event occurs** - Hardware event (button, timer, UART)
2. **CPU pauses** - Stop current execution
3. **Save context** - Push registers to stack
4. **Jump to ISR** - Execute interrupt handler
5. **Execute ISR** - Quick processing
6. **Restore context** - Pop registers from stack
7. **Resume** - Continue main program

#### **C. ISR Best Practices**

**✅ DO:**
- Keep ISR short and fast
- Only set flags
- Use `volatile` for shared variables
- Disable interrupts if needed (critical section)

**❌ DON'T:**
- Use `printf()` in ISR
- Call blocking functions
- Do heavy computation
- Use `malloc()/free()`

#### **D. Volatile Keyword**

```c
volatile bool flag = false;
```

**Tại sao cần volatile:**
- Compiler không tối ưu hóa biến này
- Biến có thể thay đổi bất ngờ (ISR, hardware)
- Force read từ memory mỗi lần access

---

### 2.7. Best Practices

#### **A. Operators**

1. **Luôn dùng dấu ngoặc trong macros:**
   ```c
   #define MAX(a, b) ((a) > (b) ? (a) : (b))
   ```

2. **Tránh side effects trong expressions:**
   ```c
   // BAD
   result = (x++) > 10 ? x++ : x--;
   
   // GOOD
   if (x > 10) {
       x++;
       result = x;
   }
   ```

3. **Sử dụng epsilon cho float comparison:**
   ```c
   if (fabs(a - b) < EPSILON) { /* Equal */ }
   ```

#### **B. Control Structures**

1. **Luôn có default case trong switch:**
   ```c
   switch (value) {
       case 0: break;
       case 1: break;
       default:
           // Handle unexpected value
           break;
   }
   ```

2. **Tránh deep nesting:**
   ```c
   // BAD
   if (a) {
       if (b) {
           if (c) {
               // Too deep!
           }
       }
   }
   
   // GOOD - Early return
   if (!a) return;
   if (!b) return;
   if (!c) return;
   // Main logic
   ```

3. **Sử dụng jump table cho nhiều cases:**
   ```c
   void (*handlers[])(void) = { func0, func1, func2 };
   handlers[index]();
   ```

#### **C. Interrupts**

1. **Volatile cho shared variables:**
   ```c
   volatile bool isr_flag = false;
   ```

2. **Keep ISR short:**
   ```c
   void timer_isr(void) {
       flag = true;  // Just set flag
   }
   ```

3. **Critical sections:**
   ```c
   disable_interrupts();
   // Critical code
   enable_interrupts();
   ```

#### **D. Embedded Systems**

1. **Avoid floating point nếu không cần:**
   - Slow on embedded systems
   - Use fixed-point arithmetic

2. **Minimize interrupt latency:**
   - Short ISRs
   - Prioritize interrupts

3. **Use state machines:**
   - Clear structure
   - Easy to debug
   - Jump table implementation

---

## 📝 Bài tập

Thư mục `exercise` chứa 3 bài tập:

1. **exercise-01.md** - State Machine với Jump Table (Medium)
2. **exercise-02.md** - Interrupt-driven Button Handler (Medium)
3. **exercise-03.md** - Bit Manipulation và Control Flags (Hard)
