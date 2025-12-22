# Standard I/O in C

Tài liệu này cung cấp kiến thức nền tảng về Standard I/O (Input/Output) trong ngôn ngữ lập trình C cho hệ thống nhúng (embedded systems), bao gồm các ví dụ code demo và kiến thức chuyên sâu về buffering, system calls, và bảo mật.

## 📑 Mục lục

[1. 📁 Mô tả Code Demo](#-1-mô-tả-code-demo)

[1.1. Printf và Scanf Formatting](#11-printf-và-scanf-formatting-printf-scanf-formattingc)

[1.2. Variadic Functions](#12-variadic-functions-variadic-functionsc)

[1.3. Buffer Comparison](#13-buffer-comparison-buffer-comparisonc)

[1.4. Stack Canary Demo](#14-stack-canary-demo-stack-canary-democ)

[2. 📚 Documentation](#-2-documentation)

[2.1. Giới thiệu Standard I/O](#21-giới-thiệu-standard-io)

[2.2. Printf và Scanf](#22-printf-và-scanf)

[2.3. Buffering trong C](#23-buffering-trong-c)

[2.4. System Calls và Performance](#24-system-calls-và-performance)

[2.5. Buffer Overflow và Bảo mật](#25-buffer-overflow-và-bảo-mật)

[2.6. Stack Canary Protection](#26-stack-canary-protection)

[2.7. Best Practices](#27-best-practices)

---

## 📁 1. Mô tả Code Demo

Thư mục `code-demo` chứa các ví dụ minh họa các khái niệm về Standard I/O trong C:

### 1.1. Printf và Scanf Formatting (`printf-scanf-formatting.c`)
**Mục đích:** Minh họa các format specifiers và alignment options

**Mô tả:**
- **Right-justify**: `%10d` - Căn phải với độ rộng 10 ký tự
- **Left-justify**: `%-10d` - Căn trái với độ rộng 10 ký tự  
- **Zero-padding**: `%08d` - Điền số 0 vào khoảng trống bên trái
- **Precision**: `%.2f` - Hiển thị số thực với 2 chữ số sau dấu phẩy

**Ví dụ:**
```c
int number = 123;
printf("[%10d]\n", number);   /* [       123] */
printf("[%-10d]\n", number);  /* [123       ] */
printf("[%08d]\n", number);   /* [00000123] */

float pi = 3.14159f;
printf("%.2f\n", pi);          /* 3.14 */
```

### 1.2. Variadic Functions (`variadic-functions.c`)
**Mục đích:** Minh họa hàm với danh sách đối số thay đổi

**Mô tả:**
- **va_list**: Kiểu dữ liệu để chứa danh sách đối số
- **va_start**: Khởi tạo danh sách đối số
- **va_arg**: Lấy đối số tiếp theo từ danh sách
- **va_end**: Kết thúc xử lý danh sách đối số

**Ví dụ:**
```c
int sum_integers(int count, ...) {
    va_list args;
    va_start(args, count);
    
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
    
    va_end(args);
    return total;
}

/* Sử dụng */
int result = sum_integers(5, 1, 2, 3, 4, 5);  /* 15 */
```

### 1.3. Buffer Comparison (`buffer-comparison.c`)
**Mục đích:** So sánh hiệu năng giữa buffered và unbuffered I/O

**Mô tả:**
- **Buffered mode**: Sử dụng `_IOFBF` (Full Buffering)
- **Unbuffered mode**: Sử dụng `_IONBF` (No Buffering)
- Chạy 1000 lần printf để thấy rõ sự khác biệt
- Sử dụng `strace` để đếm system calls

**Ví dụ:**
```c
/* Buffered: ~1-5 write() calls */
setvbuf(stdout, buffer, _IOFBF, 8192);
for (int i = 0; i < 1000; i++) {
    printf("Line %d\n", i);
}
fflush(stdout);

/* Unbuffered: 1000 write() calls */
setvbuf(stdout, NULL, _IONBF, 0);
for (int i = 0; i < 1000; i++) {
    printf("Line %d\n", i);
}
```

### 1.4. Stack Canary Demo (`stack-canary-demo.c`)
**Mục đích:** Minh họa buffer overflow và cơ chế bảo vệ stack canary

**Mô tả:**
- **Vulnerable function**: Sử dụng `gets()` - không an toàn
- **Safe function**: Sử dụng `fgets()` - an toàn
- Demo cách buffer overflow có thể ghi đè biến
- Compile với/không có stack protection để thấy sự khác biệt

**Ví dụ:**
```c
/* UNSAFE */
void vulnerable_function(void) {
    char buffer[16];
    int is_admin = 0;
    gets(buffer);  /* Buffer overflow! */
}

/* SAFE */
void safe_function(void) {
    char buffer[16];
    int is_admin = 0;
    fgets(buffer, sizeof(buffer), stdin);  /* Protected */
}
```

---

## 📚 2. Documentation

### 2.1. Giới thiệu Standard I/O

#### **A. Standard I/O là gì?**

**Standard I/O** là thư viện chuẩn của C (`stdio.h`) cung cấp các hàm để đọc/ghi dữ liệu. Nó bao gồm:

**3 luồng chuẩn:**
- `stdin` (Standard Input): File descriptor 0 - Nhập dữ liệu từ bàn phím
- `stdout` (Standard Output): File descriptor 1 - Xuất dữ liệu ra màn hình
- `stderr` (Standard Error): File descriptor 2 - Xuất thông báo lỗi

**Các hàm chính:**
- **Input**: `scanf()`, `fgets()`, `getchar()`, `fread()`
- **Output**: `printf()`, `fprintf()`, `puts()`, `fwrite()`
- **File**: `fopen()`, `fclose()`, `fseek()`, `ftell()`

#### **B. Tại sao cần Standard I/O?**

**1. Buffering tự động:**
- Giảm số lượng system calls
- Cải thiện hiệu năng đáng kể

**2. Portable:**
- Hoạt động trên mọi platform
- Không phụ thuộc OS-specific APIs

**3. Dễ sử dụng:**
- API đơn giản, trực quan
- Format string mạnh mẽ

---

### 2.2. Printf và Scanf

#### **A. Printf Format Specifiers**

**Cú pháp:**
```
%[flags][width][.precision][length]specifier
```

**Specifiers phổ biến:**

| Specifier | Kiểu dữ liệu | Ví dụ |
|-----------|--------------|-------|
| `%d`, `%i` | int (signed) | `printf("%d", 123)` → `123` |
| `%u` | unsigned int | `printf("%u", 255)` → `255` |
| `%x`, `%X` | hex (lowercase/uppercase) | `printf("%X", 255)` → `FF` |
| `%f` | float/double | `printf("%f", 3.14)` → `3.140000` |
| `%c` | char | `printf("%c", 'A')` → `A` |
| `%s` | string | `printf("%s", "Hello")` → `Hello` |
| `%p` | pointer | `printf("%p", ptr)` → `0x7fff...` |

**Flags:**

| Flag | Ý nghĩa | Ví dụ |
|------|---------|-------|
| `-` | Left-justify | `printf("%-10d", 123)` → `123       ` |
| `+` | Hiển thị dấu | `printf("%+d", 123)` → `+123` |
| `0` | Zero-padding | `printf("%08d", 123)` → `00000123` |
| `#` | Alternative form | `printf("%#x", 255)` → `0xff` |

**Width và Precision:**

```c
printf("%10d", 123);      /* [       123] - width 10 */
printf("%.2f", 3.14159);  /* [3.14] - 2 decimal places */
printf("%10.2f", 3.14);   /* [      3.14] - width 10, precision 2 */
```

#### **B. Scanf Format Specifiers**

**Cú pháp:**
```c
scanf("%[*][width]specifier", &variable);
```

**Ví dụ:**
```c
int age;
float height;
char name[50];

scanf("%d", &age);           /* Đọc integer */
scanf("%f", &height);        /* Đọc float */
scanf("%49s", name);         /* Đọc string (max 49 chars) */
scanf("%*d %d", &age);       /* Skip first int, read second */
```

**Lưu ý quan trọng:**
- ⚠️ `scanf()` không kiểm tra buffer overflow
- ⚠️ Luôn giới hạn width cho string: `%49s` thay vì `%s`
- ✅ Nên dùng `fgets()` thay vì `scanf()` cho string

---

### 2.3. Buffering trong C

#### **A. Buffering là gì?**

**Buffering** là kỹ thuật tích lũy dữ liệu trong bộ nhớ (buffer) trước khi ghi xuống thiết bị I/O. Điều này giảm số lượng system calls, cải thiện hiệu năng.

**Quy trình:**
```
User Space:  printf() → [Buffer] → (buffer full/flush) → write() system call
Kernel:      write() → Device Driver → Hardware
```

#### **B. Các chế độ Buffering**

**1. Full Buffering (_IOFBF):**
```c
char buffer[8192];
setvbuf(stdout, buffer, _IOFBF, sizeof(buffer));

/* Dữ liệu được tích lũy trong buffer */
/* Chỉ ghi khi: buffer đầy, fflush(), hoặc fclose() */
```

**Đặc điểm:**
- Buffer đầy mới flush
- Tốt nhất cho file I/O
- Ít system calls nhất

**2. Line Buffering (_IOLBF):**
```c
setvbuf(stdout, NULL, _IOLBF, 0);

/* Flush khi gặp newline '\n' */
printf("Hello\n");  /* Flush ngay */
printf("World");    /* Chưa flush */
```

**Đặc điểm:**
- Flush khi gặp `\n`
- Mặc định cho terminal (stdout)
- Cân bằng giữa hiệu năng và responsiveness

**3. No Buffering (_IONBF):**
```c
setvbuf(stdout, NULL, _IONBF, 0);

/* Mỗi printf() → 1 write() system call */
printf("A");  /* write() called immediately */
```

**Đặc điểm:**
- Không có buffer
- Mặc định cho stderr
- Nhiều system calls nhất
- Dữ liệu xuất hiện ngay lập tức

#### **C. Hàm setvbuf()**

**Cú pháp:**
```c
int setvbuf(FILE *stream, char *buffer, int mode, size_t size);
```

**Tham số:**
- `stream`: File pointer (stdin, stdout, stderr, hoặc file)
- `buffer`: Con trỏ đến buffer (hoặc NULL để tự động cấp phát)
- `mode`: `_IOFBF`, `_IOLBF`, hoặc `_IONBF`
- `size`: Kích thước buffer (bytes)

**Ví dụ:**
```c
/* Full buffering với buffer 8KB */
char buffer[8192];
setvbuf(stdout, buffer, _IOFBF, sizeof(buffer));

/* Line buffering (auto buffer) */
setvbuf(stdout, NULL, _IOLBF, 0);

/* No buffering */
setvbuf(stdout, NULL, _IONBF, 0);
```

#### **D. Hàm fflush()**

**Mục đích:** Force flush buffer ngay lập tức

```c
printf("Processing...");
fflush(stdout);  /* Hiển thị ngay, không đợi \n */

/* Do some work */
sleep(5);

printf(" Done!\n");
```

**Lưu ý:**
- `fflush(NULL)` flush tất cả output streams
- `fflush(stdin)` là undefined behavior (không nên dùng)

---

### 2.4. System Calls và Performance

#### **A. System Call là gì?**

**System call** là cơ chế chương trình user space yêu cầu kernel thực hiện tác vụ (I/O, memory, process, etc.). Mỗi system call có overhead đáng kể:

**Overhead của system call:**
1. **Context switch**: User space → Kernel space
2. **Parameter validation**: Kernel kiểm tra tham số
3. **Execution**: Kernel thực hiện tác vụ
4. **Context switch**: Kernel space → User space

**Thời gian:** ~1-10 microseconds per call (phụ thuộc CPU)

#### **B. Buffering giảm System Calls**

**Ví dụ so sánh:**

```c
/* Unbuffered: 1000 write() calls */
setvbuf(stdout, NULL, _IONBF, 0);
for (int i = 0; i < 1000; i++) {
    printf("Line %d\n", i);  /* 1 write() per line */
}

/* Buffered: ~3-5 write() calls */
char buffer[8192];
setvbuf(stdout, buffer, _IOFBF, sizeof(buffer));
for (int i = 0; i < 1000; i++) {
    printf("Line %d\n", i);  /* Accumulated in buffer */
}
fflush(stdout);  /* 1 final write() */
```

**Kết quả:**
- Unbuffered: 1000 system calls
- Buffered: 3-5 system calls
- **Tiết kiệm: ~99.5% system calls!**

#### **C. Phân tích với strace**

**strace** là công cụ Linux để trace system calls:

```bash
# Compile
gcc -o test test.c

# Trace all system calls
strace ./test

# Count system calls
strace -c ./test

# Filter only write() calls
strace -e write ./test

# Count write() calls
strace -e write ./test 2>&1 | grep "write(1" | wc -l
```

**Output mẫu:**
```
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 95.23    0.002000           2      1000           write
  2.38    0.000050          25         2           read
  ...
```

#### **D. Trade-offs**

| Aspect | Buffered | Unbuffered |
|--------|----------|------------|
| System calls | Ít (1-5) | Nhiều (1000+) |
| Performance | Nhanh | Chậm |
| Latency | Cao (đợi buffer đầy) | Thấp (ngay lập tức) |
| Data loss risk | Có (nếu crash) | Không |
| Use case | File I/O, logging | Error messages, debugging |

---

### 2.5. Buffer Overflow và Bảo mật

#### **A. Buffer Overflow là gì?**

**Buffer overflow** xảy ra khi ghi dữ liệu vượt quá kích thước buffer, ghi đè lên vùng nhớ khác.

**Ví dụ:**
```c
char buffer[16];
gets(buffer);  /* User nhập 30 ký tự → Overflow! */
```

**Stack layout:**
```
High Address
+---------------------------+
| Return Address            | ← Can be overwritten!
+---------------------------+
| Other variables           | ← Can be overwritten!
+---------------------------+
| buffer[16]                | ← Overflow starts here
+---------------------------+
Low Address
```

#### **B. Hậu quả của Buffer Overflow**

**1. Ghi đè biến:**
```c
void vulnerable(void) {
    char username[16];
    int is_admin = 0;
    
    gets(username);  /* Input: "AAAAAAAAAAAAAAAAAAAAAA" (22 chars) */
    
    /* is_admin bị ghi đè thành giá trị khác 0 */
    if (is_admin) {
        printf("Admin access granted!\n");  /* Bypassed! */
    }
}
```

**2. Code execution:**
- Ghi đè return address
- Redirect execution flow
- Execute malicious code

**3. Crash:**
- Segmentation fault
- Program terminated

#### **C. Hàm không an toàn**

**Danh sách hàm KHÔNG NÊN DÙNG:**

| Hàm | Lý do | Thay thế |
|-----|-------|----------|
| `gets()` | Không kiểm tra buffer size | `fgets()` |
| `scanf("%s")` | Không giới hạn length | `scanf("%49s")` hoặc `fgets()` |
| `strcpy()` | Không kiểm tra destination size | `strncpy()` |
| `strcat()` | Không kiểm tra destination size | `strncat()` |
| `sprintf()` | Không kiểm tra buffer size | `snprintf()` |

#### **D. Hàm an toàn**

**1. fgets() thay vì gets():**
```c
/* UNSAFE */
char buffer[50];
gets(buffer);  /* No size check! */

/* SAFE */
char buffer[50];
fgets(buffer, sizeof(buffer), stdin);  /* Size limited */
buffer[strcspn(buffer, "\n")] = '\0';  /* Remove newline */
```

**2. snprintf() thay vì sprintf():**
```c
/* UNSAFE */
char buffer[20];
sprintf(buffer, "Name: %s", very_long_name);  /* Overflow! */

/* SAFE */
char buffer[20];
snprintf(buffer, sizeof(buffer), "Name: %s", very_long_name);  /* Truncated */
```

**3. strncpy() thay vì strcpy():**
```c
/* UNSAFE */
char dest[10];
strcpy(dest, "Very long string");  /* Overflow! */

/* SAFE */
char dest[10];
strncpy(dest, "Very long string", sizeof(dest) - 1);
dest[sizeof(dest) - 1] = '\0';  /* Ensure null-termination */
```

---

### 2.6. Stack Canary Protection

#### **A. Stack Canary là gì?**

**Stack Canary** (còn gọi là Stack Guard) là một giá trị ngẫu nhiên được compiler đặt trên stack để phát hiện buffer overflow.

**Cơ chế:**
1. **Function Prologue**: Compiler chèn code để đặt canary lên stack
2. **Function Execution**: Chương trình chạy bình thường
3. **Function Epilogue**: Trước khi return, kiểm tra canary
4. **Detection**: Nếu canary thay đổi → `__stack_chk_fail()` → Terminate

**Tên gọi:** "Canary" (chim hoàng yến) - Thợ mỏ mang chim vào hầm để phát hiện khí độc. Chim chết trước → cảnh báo nguy hiểm.

#### **B. Stack Layout với Canary**

**Không có Stack Canary:**
```
High Address
+---------------------------+
| Return Address            |
+---------------------------+
| Saved Frame Pointer (EBP) |
+---------------------------+
| Local variables           |
+---------------------------+
| buffer[16]                | ← Overflow can reach return address
+---------------------------+
Low Address
```

**Có Stack Canary:**
```
High Address
+---------------------------+
| Return Address            |
+---------------------------+
| Stack Canary (0xDEADBEEF) | ← Random value
+---------------------------+
| Saved Frame Pointer (EBP) |
+---------------------------+
| Local variables           |
+---------------------------+
| buffer[16]                | ← Overflow detected by canary
+---------------------------+
Low Address
```

#### **C. Compilation Flags**

**GCC Stack Protection Flags:**

| Flag | Mô tả |
|------|-------|
| `-fno-stack-protector` | Tắt hoàn toàn stack canary |
| `-fstack-protector` | Bật cho hàm có buffer > 8 bytes |
| `-fstack-protector-strong` | Bật cho hàm có local array hoặc address-taken |
| `-fstack-protector-all` | Bật cho TẤT CẢ hàm |

**Ví dụ:**
```bash
# Compile WITHOUT protection (vulnerable)
gcc -fno-stack-protector -o vuln program.c

# Compile WITH protection
gcc -fstack-protector-all -o protected program.c
```

#### **D. Demo Stack Canary**

**Test buffer overflow:**
```bash
# Compile vulnerable version
gcc -fno-stack-protector -Wno-deprecated-declarations -o vuln test.c

# Test with overflow
echo "AAAAAAAAAAAAAAAAAAAAAAAAAAAA" | ./vuln
# Result: May bypass authentication

# Compile with stack canary
gcc -fstack-protector-all -o protected test.c

# Test with overflow
echo "AAAAAAAAAAAAAAAAAAAAAAAAAAAA" | ./protected
# Result: *** stack smashing detected *** terminated
```

#### **E. Các cơ chế bảo vệ khác**

Ngoài Stack Canary, còn có:

**1. ASLR (Address Space Layout Randomization):**
- Randomize địa chỉ stack, heap, libraries
- Khó đoán địa chỉ để tấn công

**2. DEP/NX (Data Execution Prevention):**
- Ngăn execute code trên stack/heap
- Chỉ cho phép execute code trong code segment

**3. PIE (Position Independent Executable):**
- Randomize địa chỉ code segment
- Kết hợp với ASLR để bảo vệ tốt hơn

**4. RELRO (Relocation Read-Only):**
- Bảo vệ GOT (Global Offset Table)
- Ngăn ghi đè function pointers

**Enable tất cả protections:**
```bash
gcc -fstack-protector-all -fPIE -pie -Wl,-z,relro,-z,now -o secure program.c
```

---

### 2.7. Best Practices

#### **A. Input Handling**

**1. Luôn validate input:**
```c
char buffer[50];
if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
    fprintf(stderr, "Error: Failed to read input\n");
    return -1;
}

buffer[strcspn(buffer, "\n")] = '\0';

if (strlen(buffer) >= MAX_LEN) {
    fprintf(stderr, "Error: Input too long\n");
    return -1;
}
```

**2. Sử dụng hàm an toàn:**
- ✅ `fgets()` thay vì `gets()`
- ✅ `snprintf()` thay vì `sprintf()`
- ✅ `strncpy()` thay vì `strcpy()`
- ✅ `strncat()` thay vì `strcat()`

**3. Giới hạn input length:**
```c
/* BAD */
scanf("%s", buffer);

/* GOOD */
scanf("%49s", buffer);  /* Max 49 chars + null terminator */
```

#### **B. Buffering Strategy**

**Khi nào dùng buffering:**

**Full Buffering (_IOFBF):**
- ✅ File I/O
- ✅ Logging to file
- ✅ Data processing
- ✅ Khi performance quan trọng

**Line Buffering (_IOLBF):**
- ✅ Terminal output
- ✅ Interactive programs
- ✅ Cần thấy output sau mỗi dòng

**No Buffering (_IONBF):**
- ✅ Error messages (stderr)
- ✅ Debugging output
- ✅ Real-time monitoring
- ✅ Critical logs

**Ví dụ:**
```c
/* Logging to file: Full buffering */
FILE *logfile = fopen("app.log", "a");
char buffer[8192];
setvbuf(logfile, buffer, _IOFBF, sizeof(buffer));

/* Error output: No buffering (default for stderr) */
fprintf(stderr, "Error: %s\n", error_msg);  /* Appears immediately */
```

#### **C. Embedded Systems Considerations**

**1. RAM hạn chế:**
```c
/* Giảm buffer size cho embedded */
char buffer[512];  /* Thay vì 8192 */
setvbuf(stdout, buffer, _IOFBF, sizeof(buffer));
```

**2. Flush trước khi sleep/wait:**
```c
printf("Waiting for sensor...");
fflush(stdout);  /* Hiển thị ngay */
wait_for_sensor();
```

**3. Tránh dynamic allocation:**
```c
/* BAD - malloc() trong embedded */
char *buffer = malloc(8192);
setvbuf(stdout, buffer, _IOFBF, 8192);

/* GOOD - static buffer */
static char buffer[512];
setvbuf(stdout, buffer, _IOFBF, sizeof(buffer));
```

#### **D. Security Checklist**

**Compile-time:**
- ✅ Enable stack protection: `-fstack-protector-all`
- ✅ Enable warnings: `-Wall -Wextra -Werror`
- ✅ Enable ASLR: `-fPIE -pie`
- ✅ Enable RELRO: `-Wl,-z,relro,-z,now`

**Code-level:**
- ✅ Never use `gets()`, `scanf("%s")`, `strcpy()`, `sprintf()`
- ✅ Always validate input length
- ✅ Always null-terminate strings
- ✅ Check return values of I/O functions
- ✅ Use `const` for read-only data
- ✅ Initialize all variables

**Runtime:**
- ✅ Enable ASLR: `echo 2 > /proc/sys/kernel/randomize_va_space`
- ✅ Run with minimum privileges
- ✅ Use sandboxing (seccomp, AppArmor, SELinux)

#### **E. MISRA-C Guidelines**

Cho embedded systems, tuân thủ MISRA-C:

**Rule 21.6:** Không dùng `stdio.h` trong safety-critical code
- Lý do: Dynamic allocation, unbounded execution time
- Thay thế: Implement custom I/O functions

**Rule 21.11:** Không dùng `gets()`
- Lý do: Buffer overflow risk
- Thay thế: `fgets()`

**Directive 4.1:** Minimize run-time failures
- Validate all inputs
- Check all return values
- Handle all error cases

**Example:**
```c
/* MISRA-compliant input handling */
static char buffer[MAX_SIZE];

int read_input(void) {
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;  /* Error */
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    if (strlen(buffer) >= MAX_SIZE - 1) {
        return -2;  /* Input too long */
    }
    
    return 0;  /* Success */
}
```

---

## 📝 Bài tập

Thư mục `exercise` chứa 3 bài tập với độ khó tăng dần:

1. **exercise-01.md** - Buffer I/O Performance Analysis (Medium)
   - So sánh buffered vs unbuffered I/O
   - Phân tích system calls với strace

2. **exercise-02.md** - Safe String Input System (Medium)
   - Xây dựng hệ thống input validation
   - Sử dụng fgets() và snprintf() an toàn

3. **exercise-03.md** - Stack Canary và Buffer Overflow Protection (Hard)
   - Demo buffer overflow attack
   - Hiểu cơ chế stack canary protection
   - Security analysis

Mỗi bài tập đều có file đáp án tương ứng (`answer-01.md`, `answer-02.md`, `answer-03.md`).
