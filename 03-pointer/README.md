# Pointer in C

Tài liệu này cung cấp kiến thức nền tảng về con trỏ (pointer) trong ngôn ngữ lập trình C cho hệ thống nhúng (embedded systems), bao gồm các ví dụ code demo và kiến thức chuyên sâu về cách thức hoạt động của con trỏ.

## 📑 Mục lục

[1. 📁 Mô tả Code Demo](#-1-mô-tả-code-demo)

[1.1. Size of Pointer](#11-size-of-pointer-size-of-pointerc)

[1.2. Double Pointer](#12-double-pointer-double-pointerc)

[1.3. Callbacks](#13-callbacks-callbacksc)

[1.4. Simple State Machine](#14-simple-state-machine-simple-state-machinec)

[2. 📚 Documentation](#-2-documentation)

[2.1. Mô hình bộ nhớ và biến](#21-mô-hình-bộ-nhớ-và-biến)

[2.2. Con trỏ cơ bản](#22-con-trỏ-cơ-bản)

[2.3. Các loại con trỏ đặc biệt](#23-các-loại-con-trỏ-đặc-biệt)

[2.4. Con trỏ hàm và ứng dụng](#24-con-trỏ-hàm-và-ứng-dụng)

[2.5. Best Practices](#25-best-practices)

---

## 📁 1. Mô tả Code Demo

Thư mục `code-demo` chứa các ví dụ minh họa các khái niệm về con trỏ trong C:

### 1.1. Size of Pointer (`size-of-pointer.c`)
**Mục đích:** Minh họa kích thước của con trỏ với các kiểu dữ liệu khác nhau

**Mô tả:** 
- Kích thước con trỏ phụ thuộc vào kiến trúc hệ thống (32-bit hoặc 64-bit)
- Tất cả các con trỏ có cùng kích thước bất kể kiểu dữ liệu
- Trên hệ thống 32-bit: con trỏ = 4 bytes
- Trên hệ thống 64-bit: con trỏ = 8 bytes

**Ví dụ:**
```c
int *ptr_int;
char *ptr_char;
double *ptr_double;

// Tất cả đều có cùng kích thước
sizeof(ptr_int) == sizeof(ptr_char) == sizeof(ptr_double)
```

### 1.2. Double Pointer (`double-pointer.c`)
**Mục đích:** Minh họa con trỏ cấp hai (pointer to pointer)

**Mô tả:**
- Con trỏ trỏ đến con trỏ khác
- Cần dereference hai lần để lấy giá trị cuối cùng
- Ứng dụng: Hàm cần thay đổi con trỏ, danh sách liên kết

**Ví dụ:**
```c
int x = 10;
int *ptr = &x;      // Con trỏ cấp 1
int **pptr = &ptr;  // Con trỏ cấp 2

**pptr = 20;        // Thay đổi giá trị x qua con trỏ kép
```

### 1.3. Callbacks (`callbacks.c`)
**Mục đích:** Minh họa callback function sử dụng function pointer

**Mô tả:**
- Function pointer cho phép truyền hàm như tham số
- Callback được gọi khi sự kiện xảy ra
- Ứng dụng: Event handling, interrupt service routines

**Ví dụ:**
```c
typedef void (*CallbackFunc)(int);

void registerCallback(CallbackFunc cb, int data) {
    cb(data);  // Gọi callback
}
```

### 1.4. Simple State Machine (`simple-state-machine.c`)
**Mục đích:** Minh họa state machine sử dụng function pointer

**Mô tả:**
- Sử dụng mảng function pointers để lưu state handlers
- Chuyển đổi trạng thái động
- Code đồng nhất, dễ mở rộng

**Ví dụ:**
```c
typedef void(*StateFunc)();
StateFunc stateTable[3] = {stateA, stateB, stateC};

// Gọi state handler
stateTable[currentState]();
```

---

## 📚 2. Documentation

### 2.1. Mô hình bộ nhớ và biến

#### **A. Kiến trúc bộ nhớ cơ bản**

Để có thể làm chủ được con trỏ, một trong những khái niệm mạnh mẽ và cũng phức tạp nhất của ngôn ngữ lập trình C, trước hết chúng ta cần phải có một sự am hiểu sâu sắc về cách thức chương trình tương tác với bộ nhớ máy tính.

**Mọi biến, mọi mảng, mọi cấu trúc dữ liệu đều tồn tại dưới dạng các byte trong bộ nhớ.**

Con trỏ chính là công cụ cho phép chúng ta làm việc trực tiếp với các byte này thông qua địa chỉ của chúng.

**Bộ nhớ RAM** của máy tính có thể được hình dung như một dãy các ô nhớ khổng lồ, được xếp tuần tự và liên tiếp nhau:

```
Address    Value
0x0000     [  ]
0x0001     [  ]
0x0002     [  ]
0x0003     [  ]
...        ...
0xFFFF     [  ]
```

**Đặc điểm:**
- Mỗi ô nhớ có kích thước **1 byte**
- Mỗi ô nhớ có một **địa chỉ duy nhất** (thường biểu diễn dưới dạng số hexadecimal)
- Địa chỉ là số nguyên không âm

#### **B. Biến và cấp phát bộ nhớ**

Khi chúng ta khai báo một biến, trình biên dịch C thực hiện hai công việc chính:

1. **Dành riêng một vùng nhớ** có kích thước phù hợp với kiểu dữ liệu
2. **Liên kết tên biến** với địa chỉ của ô nhớ đầu tiên trong vùng nhớ được cấp phát

**Kích thước các kiểu dữ liệu** (hệ thống 32-bit):

| Kiểu dữ liệu | Kích thước | Ví dụ |
|--------------|------------|-------|
| `char` | 1 byte | `char c = 'A';` |
| `int` | 4 bytes | `int x = 100;` |
| `float` | 4 bytes | `float f = 3.14;` |
| `double` | 8 bytes | `double d = 2.718;` |
| `pointer` | 4 bytes (32-bit) | `int *ptr;` |
| `pointer` | 8 bytes (64-bit) | `int *ptr;` |

**Ví dụ minh họa:**

```c
int x = 42;
```

Trong bộ nhớ:
```
Address    Value
0x1000     [42]  ← x chiếm 4 bytes
0x1001     [00]
0x1002     [00]
0x1003     [00]
0x1004     [  ]
```

Biến `x` được lưu tại địa chỉ `0x1000` và chiếm 4 bytes liên tiếp.

#### **C. Toán tử địa chỉ (&)**

Mỗi biến trong chương trình đều có một địa chỉ cụ thể. Ngôn ngữ C cung cấp **toán tử địa chỉ `&`** (address-of) để lấy địa chỉ bộ nhớ của một biến.

**Ví dụ:**

```c
int x = 42;
printf("Value of x: %d\n", x);        // 42
printf("Address of x: %p\n", &x);     // 0x1000 (ví dụ)
```

**Lưu ý:**
- `&x` trả về địa chỉ của biến `x`
- Địa chỉ được in ra dưới dạng hexadecimal với format `%p`

---

### 2.2. Con trỏ cơ bản

#### **A. Con trỏ là gì?**

**Con trỏ (pointer)** là một biến đặc biệt, nhưng thay vì lưu trữ một giá trị dữ liệu như số nguyên hay ký tự, nó lưu trữ một **địa chỉ bộ nhớ** của một biến khác.

Có thể nói, con trỏ không chứa dữ liệu, mà nó **"trỏ"** đến nơi dữ liệu được lưu trữ.

**Sức mạnh của con trỏ:**

1. **Cấp phát bộ nhớ động:** Tạo ra các mảng và cấu trúc dữ liệu mà kích thước chỉ được quyết định trong lúc chương trình chạy
2. **Truyền tham số hiệu quả:** Truyền các cấu trúc dữ liệu lớn vào hàm mà không cần sao chép toàn bộ dữ liệu
3. **Thao tác trực tiếp trên bộ nhớ:** Cho phép các thao tác ở mức độ thấp, rất quan trọng trong lập trình hệ thống
4. **Xây dựng cấu trúc dữ liệu phức tạp:** Nền tảng để xây dựng linked lists, trees, graphs

#### **B. Kích thước của con trỏ**

**Điểm quan trọng:** Kích thước của pointer trong C/C++ **không phụ thuộc** vào kiểu dữ liệu mà nó trỏ đến.

Tất cả các con trỏ trên một hệ thống thường có **cùng kích thước** vì chúng lưu trữ địa chỉ bộ nhớ, và kích thước này phụ thuộc vào **không gian địa chỉ (address space)** của kiến trúc.

**Trên hệ thống 32-bit:**
- Con trỏ có kích thước: **4 bytes (32 bit)**
- Không gian địa chỉ tối đa: **2³² = 4 GB**

**Trên hệ thống 64-bit:**
- Con trỏ có kích thước: **8 bytes (64 bit)**
- Không gian địa chỉ tối đa: **2⁶⁴ ≈ 18 exabytes**

**Trường hợp đặc biệt:**
- Một số hệ thống nhúng (embedded) hoặc kiến trúc không tiêu chuẩn có thể dùng con trỏ 2 bytes hoặc kích thước không phổ biến khác

**Ví dụ:**

```c
#include <stdio.h>

int main() {
    int *ptr_int;
    char *ptr_char;
    double *ptr_double;
    void *ptr_void;
    
    printf("sizeof(int*)    = %zu bytes\n", sizeof(ptr_int));
    printf("sizeof(char*)   = %zu bytes\n", sizeof(ptr_char));
    printf("sizeof(double*) = %zu bytes\n", sizeof(ptr_double));
    printf("sizeof(void*)   = %zu bytes\n", sizeof(ptr_void));
    
    // Tất cả đều in ra cùng kích thước (4 hoặc 8 bytes)
    return 0;
}
```

#### **C. Khai báo con trỏ**

**Cú pháp:**
```c
kiểu_dữ_liệu *tên_con_trỏ;
```

**Ví dụ:**
```c
int *ptr_int;       // Con trỏ trỏ đến int
char *ptr_char;     // Con trỏ trỏ đến char
float *ptr_float;   // Con trỏ trỏ đến float
double *ptr_double; // Con trỏ trỏ đến double
```

**Tại sao con trỏ cần có kiểu dữ liệu?**

Mặc dù con trỏ chỉ lưu một địa chỉ (về bản chất là một con số), nhưng nó vẫn cần có kiểu dữ liệu cụ thể vì hai lý do:

1. **Để tham chiếu ngược (Dereferencing):** Khi ta dùng toán tử `*` để lấy giá trị tại địa chỉ mà con trỏ đang trỏ tới, trình biên dịch cần biết phải đọc **bao nhiêu byte** từ địa chỉ đó
   - Nếu con trỏ là `int *`, trình biên dịch sẽ đọc `sizeof(int)` bytes
   - Nếu là `char *`, nó sẽ đọc `sizeof(char)` bytes

2. **Để thực hiện số học con trỏ (Pointer Arithmetic):** Khi ta thực hiện các phép toán như `ptr + 1`, trình biên dịch không chỉ cộng 1 vào giá trị địa chỉ. Thay vào đó, nó sẽ tính toán địa chỉ mới bằng cách lấy địa chỉ hiện tại cộng với `1 * sizeof(kiểu_dữ_liệu)`

**Ví dụ minh họa:**

```c
int arr[3] = {10, 20, 30};
int *ptr = arr;

printf("ptr     = %p\n", ptr);      // 0x1000
printf("ptr + 1 = %p\n", ptr + 1);  // 0x1004 (cộng 4 bytes)
printf("ptr + 2 = %p\n", ptr + 2);  // 0x1008 (cộng 8 bytes)
```

#### **D. Toán tử tham chiếu ngược (*)**

**Toán tử tham chiếu ngược (dereference)** hay **toán tử gián tiếp (indirection)** `*` làm điều ngược lại: nó lấy giá trị tại địa chỉ mà con trỏ đang trỏ tới.

**Cần phân biệt rõ ràng vai trò kép của dấu `*`:**

1. **Trong khai báo:** `int *ptr;` - dấu `*` chỉ ra rằng `ptr` là một biến con trỏ
2. **Trong biểu thức:** `*ptr` - dấu `*` là toán tử tham chiếu ngược, dùng để lấy giá trị

**Ví dụ:**

```c
int x = 42;
int *ptr = &x;  // ptr lưu địa chỉ của x

printf("Value of x: %d\n", x);       // 42
printf("Address of x: %p\n", &x);    // 0x1000
printf("Value of ptr: %p\n", ptr);   // 0x1000
printf("Value at ptr: %d\n", *ptr);  // 42

*ptr = 100;  // Thay đổi giá trị tại địa chỉ mà ptr trỏ tới
printf("New value of x: %d\n", x);   // 100
```

**Minh họa trong bộ nhớ:**

```
Variable   Address   Value
x          0x1000    [42]
ptr        0x2000    [0x1000]  ← ptr chứa địa chỉ của x

*ptr → đọc giá trị tại địa chỉ 0x1000 → 42
```

#### **E. Con trỏ NULL**

Một con trỏ chưa được khởi tạo được gọi là **con trỏ hoang dã (wild pointer)**. Nó chứa một địa chỉ rác và việc sử dụng nó sẽ dẫn đến **hành vi không xác định (undefined behavior)**, thường là làm sập chương trình.

**Để tránh điều này**, một thực hành lập trình an toàn là luôn khởi tạo con trỏ với một giá trị đặc biệt: **NULL**

**NULL pointer:**
- Là một con trỏ không trỏ đến bất kỳ địa chỉ hợp lệ nào
- Giá trị `NULL` thường là `0` hoặc `(void*)0`
- Được định nghĩa trong `<stddef.h>`, `<stdio.h>`, `<stdlib.h>`

**Ví dụ:**

```c
int *ptr = NULL;  // Khởi tạo con trỏ với NULL

// Trước khi sử dụng, luôn kiểm tra NULL
if (ptr != NULL) {
    printf("Value: %d\n", *ptr);
} else {
    printf("Pointer is NULL\n");
}
```

**Best Practice:**
```c
// ✅ Good: Luôn khởi tạo con trỏ
int *ptr = NULL;

// ✅ Good: Kiểm tra NULL trước khi dereference
if (ptr != NULL) {
    *ptr = 10;
}

// ❌ Bad: Con trỏ hoang dã
int *ptr;  // Chứa địa chỉ rác
*ptr = 10; // Undefined behavior!
```

---

### 2.3. Các loại con trỏ đặc biệt

#### **A. Void Pointer (Con trỏ void)**

**Void pointer** (con trỏ void) là con trỏ có thể lưu địa chỉ của **bất kỳ kiểu dữ liệu nào**. Vì không có kiểu cụ thể, compiler không biết kích thước dữ liệu, nên **không thể dereference trực tiếp**.

**Khai báo:**
```c
void *ptr;
```

**Sử dụng khi:**
- Cần xử lý dữ liệu mà chưa biết trước kiểu của nó
- Trong các hàm làm việc với dữ liệu generic (ví dụ: hàm xử lý bộ nhớ, thuật toán sắp xếp, xử lý buffer)
- Khi muốn viết API linh hoạt, không phụ thuộc vào kiểu dữ liệu

**Ví dụ:**

```c
#include <stdio.h>
#include <stdlib.h>

void print_bytes(void *ptr, size_t size) {
    unsigned char *byte_ptr = (unsigned char*)ptr;
    
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", byte_ptr[i]);
    }
    printf("\n");
}

int main() {
    int x = 0x12345678;
    float f = 3.14f;
    
    printf("Bytes of int: ");
    print_bytes(&x, sizeof(x));
    
    printf("Bytes of float: ");
    print_bytes(&f, sizeof(f));
    
    return 0;
}
```

**Lưu ý:**
- Phải **ép kiểu (type cast)** trước khi dereference
- Thường dùng trong `malloc()`, `memcpy()`, `qsort()`

#### **B. Double Pointer (Con trỏ kép)**

Một **con trỏ trỏ đến con trỏ**, hay **con trỏ cấp hai**, là một biến con trỏ mà giá trị nó lưu trữ là địa chỉ của một biến con trỏ khác.

**Khai báo:**
```c
kiểu_dữ_liệu **tên_con_trỏ;
```

**Tham chiếu ngược:**
- `pptr`: Chứa địa chỉ của con trỏ cấp một
- `*pptr`: Lấy giá trị tại địa chỉ đó, tức là lấy ra con trỏ cấp một
- `**pptr`: Lấy giá trị tại địa chỉ mà con trỏ cấp một trỏ tới, tức là giá trị của biến ban đầu

**Ví dụ:**

```c
int x = 10;
int *ptr = &x;      // Con trỏ cấp 1 trỏ tới x
int **pptr = &ptr;  // Con trỏ cấp 2 trỏ tới ptr

printf("x = %d\n", x);          // 10
printf("*ptr = %d\n", *ptr);    // 10
printf("**pptr = %d\n", **pptr);// 10

**pptr = 20;  // Thay đổi giá trị x qua con trỏ kép
printf("x = %d\n", x);          // 20
```

**Minh họa trong bộ nhớ:**

```
Variable   Address   Value
x          0x1000    [10]
ptr        0x2000    [0x1000]  ← trỏ đến x
pptr       0x3000    [0x2000]  ← trỏ đến ptr

**pptr → *0x2000 → *0x1000 → 10
```

**Ứng dụng:**

1. **Hàm cấp phát động cần thay đổi con trỏ truyền vào:**

```c
void allocate_memory(int **ptr, int size) {
    *ptr = (int*)malloc(size * sizeof(int));
}

int main() {
    int *arr = NULL;
    allocate_memory(&arr, 10);  // Truyền địa chỉ của con trỏ
    
    if (arr != NULL) {
        arr[0] = 100;
        free(arr);
    }
    return 0;
}
```

2. **Danh sách liên kết (Linked List):**

```c
typedef struct Node {
    int data;
    struct Node *next;
} Node;

void insert_at_head(Node **head, int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = *head;
    *head = new_node;  // Thay đổi con trỏ head
}
```

#### **C. Con trỏ hằng vs Hằng con trỏ**

Lập trình viên cần phân biệt được sự khác nhau giữa 2 khái niệm tưởng chừng đơn giản nhưng dễ gây nhầm lẫn này.

**1. Con trỏ hằng (Pointer to Constant)**

Con trỏ trỏ tới một giá trị hằng – nghĩa là **không được phép thay đổi giá trị qua con trỏ**, nhưng bản thân con trỏ có thể trỏ sang nơi khác.

**Khai báo:**
```c
const int *ptr;
// hoặc
int const *ptr;
```

**Ví dụ:**
```c
int x = 10, y = 20;
const int *ptr = &x;

// ❌ Không thể thay đổi giá trị qua con trỏ
// *ptr = 15;  // Lỗi biên dịch

// ✅ Có thể thay đổi con trỏ trỏ sang nơi khác
ptr = &y;  // OK
```

**2. Hằng con trỏ (Constant Pointer)**

Hằng con trỏ là con trỏ mà **địa chỉ không được phép thay đổi**, nhưng giá trị tại địa chỉ đó có thể thay đổi.

**Khai báo:**
```c
int *const ptr;
```

**Ví dụ:**
```c
int x = 10, y = 20;
int *const ptr = &x;

// ✅ Có thể thay đổi giá trị qua con trỏ
*ptr = 15;  // OK, x = 15

// ❌ Không thể thay đổi con trỏ trỏ sang nơi khác
// ptr = &y;  // Lỗi biên dịch
```

**3. Hằng con trỏ trỏ đến hằng (Constant Pointer to Constant)**

Kết hợp cả hai: **không thể thay đổi địa chỉ** và **không thể thay đổi giá trị**.

**Khai báo:**
```c
const int *const ptr;
```

**Ví dụ:**
```c
int x = 10, y = 20;
const int *const ptr = &x;

// ❌ Không thể thay đổi giá trị
// *ptr = 15;  // Lỗi

// ❌ Không thể thay đổi địa chỉ
// ptr = &y;   // Lỗi
```

**Bảng tóm tắt:**

| Khai báo | Thay đổi giá trị | Thay đổi địa chỉ |
|----------|------------------|------------------|
| `int *ptr` | ✅ | ✅ |
| `const int *ptr` | ❌ | ✅ |
| `int *const ptr` | ✅ | ❌ |
| `const int *const ptr` | ❌ | ❌ |

**Mẹo nhớ:** Đọc từ phải sang trái:
- `const int *ptr` → ptr là con trỏ đến int hằng
- `int *const ptr` → ptr là hằng con trỏ đến int

---

### 2.4. Con trỏ hàm và ứng dụng

#### **A. Con trỏ hàm là gì?**

**Con trỏ hàm (function pointer)** là một con trỏ trỏ đến một hàm thay vì trỏ đến một biến. Nó lưu trữ địa chỉ của hàm trong bộ nhớ.

**Khai báo:**
```c
kiểu_trả_về (*tên_con_trỏ)(danh_sách_tham_số);
```

**Ví dụ:**
```c
// Hàm bình thường
int add(int a, int b) {
    return a + b;
}

// Con trỏ hàm
int (*func_ptr)(int, int);

// Gán địa chỉ hàm cho con trỏ
func_ptr = add;

// Gọi hàm qua con trỏ
int result = func_ptr(5, 3);  // result = 8
```

**Sử dụng typedef để đơn giản hóa:**
```c
typedef int (*MathFunc)(int, int);

MathFunc func_ptr = add;
int result = func_ptr(5, 3);
```

#### **B. Callbacks cho Sự kiện và Ngắt (Events and Interrupts)**

**Callback** là một hàm được truyền cho hàm khác để "gọi lại" khi xảy ra sự kiện.

**Tầm quan trọng của Callback:**

**Đảo ngược quyền điều khiển (Inversion of Control - IoC):**
- Luồng điều khiển từ trên xuống bị đảo ngược
- Code cao cấp gọi hàm cấp thấp với con trỏ hàm, cho phép thực hiện công việc khác trong khi chờ đợi

**Lợi ích:**
- **Lập trình bất đồng bộ:** Không bị "treo" khi chờ sự kiện
- **Tách biệt và tái sử dụng:** Các module độc lập, dễ bảo trì và có thể sử dụng lại cho nhiều mục đích khác nhau

**Ví dụ trong Embedded:**

```c
#include <stdio.h>
#include <stdint.h>

// Callback function type
typedef void (*EventCallback)(uint8_t event_id);

// Event handler
void on_button_press(uint8_t event_id) {
    printf("Button %d pressed!\n", event_id);
}

void on_timer_expire(uint8_t event_id) {
    printf("Timer %d expired!\n", event_id);
}

// Register callback
void register_event_handler(uint8_t event_id, EventCallback callback) {
    // Lưu callback vào bảng
    // Khi event xảy ra, gọi callback
    callback(event_id);
}

int main() {
    // Đăng ký callbacks
    register_event_handler(1, on_button_press);
    register_event_handler(2, on_timer_expire);
    
    return 0;
}
```

**Ứng dụng trong Embedded:**
- Bộ hẹn giờ (Timer): Gọi callback khi timer hết hạn
- UART/I2C/SPI: Xử lý các sự kiện như dữ liệu đã nhận, hoàn tất truyền
- Interrupt Service Routine (ISR): Xử lý ngắt

#### **C. Máy trạng thái (State Machines)**

Con trỏ hàm cho phép triển khai các **máy trạng thái (state machine)** bằng cách cho phép chuyển đổi động giữa các trạng thái, làm cho mã trở nên đồng nhất và dễ duy trì.

**Ví dụ:**

```c
#include <stdio.h>

typedef void (*StateFunc)(void);

// State handler functions
void state_idle(void) {
    printf("State: IDLE\n");
}

void state_running(void) {
    printf("State: RUNNING\n");
}

void state_error(void) {
    printf("State: ERROR\n");
}

// State table
StateFunc state_table[] = {
    state_idle,
    state_running,
    state_error
};

int main() {
    int current_state = 0;
    
    // Chuyển đổi trạng thái
    for (int i = 0; i < 3; i++) {
        state_table[current_state]();
        current_state = (current_state + 1) % 3;
    }
    
    return 0;
}
```

**Lợi ích:**
- Code đồng nhất, dễ đọc
- Dễ dàng thêm state mới
- Tách biệt logic của từng state

#### **D. Bảng Điều phối Lệnh (Command Dispatch Tables)**

**So sánh với switch-case:**

Giả sử bạn đang viết firmware cho robot nhận lệnh qua sóng radio. Khi bạn muốn thêm một lệnh mới `CMD_FIRE_LASER`, bạn phải vào tận sâu bên trong hàm `process_command` và thêm một `case` mới. Hàm này sẽ ngày càng phình to, trở nên khó đọc và khó quản lý.

**Điều này vi phạm nguyên tắc Mở/Đóng (Open/Closed Principle)** - một module nên có thể mở rộng nhưng không cần sửa đổi.

**Cách giải quyết: Dùng Bảng Điều phối Lệnh**

```c
#include <stdio.h>
#include <stdint.h>

// Command handler type
typedef void (*CommandHandler)(void);

// Command handlers
void cmd_move_forward(void) {
    printf("Moving forward\n");
}

void cmd_turn_left(void) {
    printf("Turning left\n");
}

void cmd_stop(void) {
    printf("Stopping\n");
}

// Command dispatch table
typedef struct {
    uint8_t command_id;
    CommandHandler handler;
} CommandEntry;

CommandEntry command_table[] = {
    {0x01, cmd_move_forward},
    {0x02, cmd_turn_left},
    {0x03, cmd_stop},
    // Dễ dàng thêm lệnh mới
};

void process_command(uint8_t cmd_id) {
    for (int i = 0; i < sizeof(command_table) / sizeof(CommandEntry); i++) {
        if (command_table[i].command_id == cmd_id) {
            command_table[i].handler();
            return;
        }
    }
    printf("Unknown command\n");
}

int main() {
    process_command(0x01);  // Moving forward
    process_command(0x02);  // Turning left
    process_command(0x03);  // Stopping
    
    return 0;
}
```

**Lợi ích:**
- Dễ dàng thêm lệnh mới mà không cần sửa đổi code cũ
- Code sạch hơn, dễ bảo trì
- Tuân thủ Open/Closed Principle

#### **E. Các Thuật toán Generic**

Con trỏ hàm cho phép viết các thuật toán generic, không phụ thuộc vào kiểu dữ liệu cụ thể.

**Ví dụ: Hàm sắp xếp generic (qsort)**

```c
#include <stdio.h>
#include <stdlib.h>

// Comparison function for integers
int compare_int(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Comparison function for descending order
int compare_int_desc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int arr[] = {5, 2, 8, 1, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    // Sắp xếp tăng dần
    qsort(arr, n, sizeof(int), compare_int);
    
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}
```

**Lợi ích:**
- Một hàm có thể xử lý nhiều kiểu dữ liệu khác nhau
- Tái sử dụng code
- Linh hoạt, dễ mở rộng

---

### 2.5. Best Practices

#### **1. Luôn khởi tạo con trỏ**

```c
// ❌ Bad: Wild pointer
int *ptr;

// ✅ Good: Initialize with NULL
int *ptr = NULL;
```

#### **2. Kiểm tra NULL trước khi dereference**

```c
// ✅ Good: Check before use
if (ptr != NULL) {
    *ptr = 10;
}
```

#### **3. Giải phóng bộ nhớ sau khi sử dụng**

```c
int *ptr = (int*)malloc(sizeof(int) * 10);

if (ptr != NULL) {
    // Sử dụng ptr
    
    free(ptr);
    ptr = NULL;  // Tránh dangling pointer
}
```

#### **4. Sử dụng const khi có thể**

```c
// ✅ Good: Protect data from modification
void print_array(const int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
}
```

#### **5. Tránh pointer arithmetic phức tạp**

```c
// ❌ Bad: Hard to read
int value = *(ptr + 3 * sizeof(int));

// ✅ Good: Use array notation
int value = ptr[3];
```

#### **6. Sử dụng typedef cho function pointers**

```c
// ❌ Bad: Hard to read
void register_callback(void (*callback)(int));

// ✅ Good: Use typedef
typedef void (*Callback)(int);
void register_callback(Callback callback);
```

#### **7. Validate pointer parameters**

```c
void process_data(int *data, int size) {
    if (data == NULL || size <= 0) {
        return;  // Invalid parameters
    }
    
    // Process data
}
```

#### **8. Sử dụng stdint.h cho portable code**

```c
#include <stdint.h>

// ✅ Good: Explicit size
uint8_t *buffer;
uint32_t *register_ptr;
```

---

## 🎯 Kết luận

Con trỏ là một trong những khái niệm quan trọng nhất trong lập trình C, đặc biệt trong embedded systems:

- ✅ Hiểu rõ mô hình bộ nhớ và cách biến được lưu trữ
- ✅ Nắm vững các loại con trỏ: basic, void, double pointer
- ✅ Biết cách sử dụng con trỏ hàm cho callbacks và state machines
- ✅ Luôn khởi tạo và kiểm tra NULL trước khi sử dụng
- ✅ Giải phóng bộ nhớ đúng cách để tránh memory leak
- ✅ Sử dụng const để bảo vệ dữ liệu

**Nguyên tắc vàng:**
> "Luôn khởi tạo con trỏ, kiểm tra NULL trước khi dereference, và giải phóng bộ nhớ sau khi sử dụng!"

---

## 📖 Tài liệu tham khảo

- Code demo trong `code-demo/` để thực hành
- MISRA C Guidelines cho embedded systems
- ARM Cortex-M Programming Manual
- "The C Programming Language" by Kernighan and Ritchie
