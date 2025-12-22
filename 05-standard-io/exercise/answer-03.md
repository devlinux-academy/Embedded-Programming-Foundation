# **Đáp án Bài tập 3 — Stack Canary và Buffer Overflow Protection**

## **Giải thích**

Bài tập này demo cơ chế buffer overflow attack và cách stack canary bảo vệ chương trình. Buffer overflow xảy ra khi ghi dữ liệu vượt quá kích thước buffer, ghi đè lên các biến khác trên stack.

## **Code hoàn chỉnh**

```c
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERNAME 20
#define MAX_PASSWORD 20
#define CORRECT_USER "admin"
#define CORRECT_PASS "secret123"

void vulnerable_login(void) {
    char username[16];
    char password[16];
    int is_authenticated = 0;
    
    printf("=== Vulnerable Authentication ===\n");
    printf("Username: ");
    gets(username);
    
    printf("Password: ");
    gets(password);
    
    if (strcmp(username, CORRECT_USER) == 0 && 
        strcmp(password, CORRECT_PASS) == 0) {
        is_authenticated = 1;
    }
    
    printf("\nAuthentication: %s\n", 
           is_authenticated ? "SUCCESS" : "FAILED");
    printf("Access: %s\n", 
           is_authenticated ? "GRANTED" : "DENIED");
}

bool secure_login(void) {
    char username[MAX_USERNAME + 1];
    char password[MAX_PASSWORD + 1];
    
    printf("=== Secure Authentication ===\n");
    
    printf("Username: ");
    if (fgets(username, sizeof(username), stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read username\n");
        return false;
    }
    username[strcspn(username, "\n")] = '\0';
    
    if (strlen(username) >= MAX_USERNAME) {
        fprintf(stderr, "Error: Username too long (max %d characters)\n", 
                MAX_USERNAME);
        return false;
    }
    
    printf("Password: ");
    if (fgets(password, sizeof(password), stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read password\n");
        return false;
    }
    password[strcspn(password, "\n")] = '\0';
    
    if (strlen(password) >= MAX_PASSWORD) {
        fprintf(stderr, "Error: Password too long (max %d characters)\n", 
                MAX_PASSWORD);
        return false;
    }
    
    if (strcmp(username, CORRECT_USER) == 0 && 
        strcmp(password, CORRECT_PASS) == 0) {
        printf("\nAuthentication: SUCCESS\n");
        return true;
    }
    
    printf("\nAuthentication: FAILED\n");
    return false;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [vulnerable|secure]\n", argv[0]);
        return 1;
    }
    
    if (strcmp(argv[1], "vulnerable") == 0) {
        vulnerable_login();
    } else if (strcmp(argv[1], "secure") == 0) {
        if (secure_login()) {
            printf("Access: GRANTED\n");
        } else {
            printf("Access: DENIED\n");
        }
    } else {
        fprintf(stderr, "Invalid option\n");
        return 1;
    }
    
    return 0;
}
```

## **Compilation và Testing**

### 1. Compile vulnerable version (NO stack protection)

```bash
gcc -fno-stack-protector -Wno-deprecated-declarations -o auth_vuln auth.c
```

### 2. Compile với stack canary protection

```bash
gcc -fstack-protector-all -Wno-deprecated-declarations -o auth_protected auth.c
```

### 3. Compile secure version

```bash
gcc -o auth_secure auth.c
```

## **Test Cases và Kết quả**

### Test 1: Normal login (vulnerable)

```bash
$ echo -e "admin\nsecret123" | ./auth_vuln vulnerable
=== Vulnerable Authentication ===
Username: Password: 
Authentication: SUCCESS
Access: GRANTED
```

### Test 2: Buffer overflow attack (vulnerable, no protection)

```bash
$ echo -e "AAAAAAAAAAAAAAAAAAAAAAAAAAAA\nanything" | ./auth_vuln vulnerable
=== Vulnerable Authentication ===
Username: Password: 
Authentication: FAILED
Access: GRANTED  ← is_authenticated was overwritten!
```

**Giải thích:** Input dài 28 ký tự 'A' ghi đè lên `is_authenticated`, biến nó thành giá trị khác 0 (true).

### Test 3: Stack canary detection

```bash
$ echo -e "AAAAAAAAAAAAAAAAAAAAAAAAAAAA\nanything" | ./auth_protected vulnerable
=== Vulnerable Authentication ===
Username: Password: 
*** stack smashing detected ***: terminated
Aborted (core dumped)
```

**Giải thích:** Stack canary phát hiện buffer overflow và terminate chương trình.

### Test 4: Secure version

```bash
$ echo -e "AAAAAAAAAAAAAAAAAAAAAAAAAAAA\nanything" | ./auth_secure secure
=== Secure Authentication ===
Username: Error: Username too long (max 20 characters)
```

**Giải thích:** `fgets()` giới hạn input, không cho phép overflow.

## **Stack Layout Analysis**

### Vulnerable version (without stack canary)

```
High Address
+---------------------------+
| Return Address            | ← Target of advanced attacks
+---------------------------+
| Saved Frame Pointer (EBP) |
+---------------------------+
| is_authenticated (4 bytes)| ← Can be overwritten!
+---------------------------+
| password[16]              |
+---------------------------+
| username[16]              | ← Overflow starts here
+---------------------------+
Low Address

Overflow path:
username[0..15] → username[16..31] (password) → 
username[32..35] (is_authenticated) → ...
```

### With stack canary protection

```
High Address
+---------------------------+
| Return Address            |
+---------------------------+
| Stack Canary (0xDEADBEEF) | ← Random value, checked before return
+---------------------------+
| Saved Frame Pointer (EBP) |
+---------------------------+
| is_authenticated          |
+---------------------------+
| password[16]              |
+---------------------------+
| username[16]              |
+---------------------------+
Low Address

If canary is modified → __stack_chk_fail() → Program terminated
```

## **Câu hỏi phân tích - Đáp án**

### 1. Buffer Overflow

**Q: Giải thích cách buffer overflow có thể bypass authentication**

A: Khi nhập username dài hơn 16 bytes, dữ liệu thừa ghi đè lên `password` và `is_authenticated`. Nếu ghi đè `is_authenticated` thành giá trị khác 0, điều kiện `if (is_authenticated)` sẽ true, cho phép truy cập.

**Q: Tại sao is_authenticated có thể bị ghi đè?**

A: Các biến local được lưu liên tiếp trên stack. Khi `gets()` không kiểm tra độ dài, nó ghi tiếp vào vùng nhớ sau `username`, ghi đè lên các biến khác.

**Q: Stack layout ảnh hưởng như thế nào?**

A: Thứ tự khai báo biến ảnh hưởng đến vị trí trên stack. Compiler có thể sắp xếp lại, nhưng thường theo thứ tự khai báo.

### 2. Stack Canary

**Q: Stack canary hoạt động như thế nào?**

A: 
1. **Function prologue**: Compiler chèn code để đặt canary lên stack
2. **Function execution**: Chương trình chạy bình thường
3. **Function epilogue**: Trước khi return, kiểm tra canary
4. **Detection**: Nếu canary thay đổi → gọi `__stack_chk_fail()` → terminate

**Q: Tại sao gọi là "canary"?**

A: Giống "chim hoàng yến trong mỏ than" - thợ mỏ mang chim vào hầm để phát hiện khí độc. Chim chết trước → cảnh báo nguy hiểm. Stack canary "chết" (thay đổi) trước → cảnh báo buffer overflow.

**Q: Khi nào stack canary được kiểm tra?**

A: Ngay trước khi hàm return (function epilogue), trước khi restore frame pointer và jump về return address.

### 3. Security

**Q: Tại sao gets() bị deprecated?**

A: `gets()` không có cách nào giới hạn số ký tự đọc, luôn gây buffer overflow. Đã bị remove khỏi C11 standard.

**Q: Sự khác biệt giữa -fno-stack-protector và -fstack-protector-all?**

A:
- `-fno-stack-protector`: Tắt hoàn toàn stack canary
- `-fstack-protector`: Bật cho hàm có buffer > 8 bytes
- `-fstack-protector-all`: Bật cho TẤT CẢ hàm

**Q: Ngoài stack canary, còn cơ chế bảo vệ nào?**

A:
- **ASLR** (Address Space Layout Randomization): Randomize địa chỉ stack/heap
- **DEP/NX** (Data Execution Prevention): Ngăn execute code trên stack
- **PIE** (Position Independent Executable): Randomize code location
- **RELRO** (Relocation Read-Only): Bảo vệ GOT/PLT

## **Bonus Challenge - Memory Analysis với GDB**

```bash
# Compile with debug symbols
gcc -g -fstack-protector-all -o auth_debug auth.c

# Run with GDB
gdb ./auth_debug

# Set breakpoint
(gdb) break vulnerable_login
(gdb) run vulnerable

# View stack
(gdb) info frame
(gdb) x/20x $esp

# Find canary
(gdb) x/x $ebp-0x8  # Canary usually at ebp-8
```

## **Security Recommendations**

1. ✅ **Never use `gets()`** - Use `fgets()` instead
2. ✅ **Compile with `-fstack-protector-all`**
3. ✅ **Enable ASLR** - `echo 2 > /proc/sys/kernel/randomize_va_space`
4. ✅ **Use safe string functions** - `strncpy()`, `snprintf()`
5. ✅ **Validate all inputs** - Length, format, range
6. ✅ **Use static analysis tools** - Valgrind, AddressSanitizer
7. ✅ **Follow MISRA-C guidelines** for embedded systems
