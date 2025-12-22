# **Bài tập 3 — Stack Canary và Buffer Overflow Protection (Hard)**

## **Mục tiêu**

Hiểu rõ cơ chế buffer overflow attack và cách stack canary bảo vệ chương trình. Học cách viết code an toàn để tránh lỗ hổng bảo mật.

## **Bối cảnh**

Bạn đang phát triển một hệ thống authentication cho embedded device. Hệ thống cần kiểm tra username và password, nhưng phải đảm bảo không bị tấn công buffer overflow để bypass authentication.

## **Yêu cầu**

Viết chương trình C bao gồm:

1. **Phiên bản vulnerable** (có lỗ hổng):
   - Sử dụng `gets()` để nhập username và password
   - Có biến `is_authenticated` để kiểm tra quyền truy cập
   - Dễ bị tấn công buffer overflow

2. **Phiên bản secure** (an toàn):
   - Sử dụng `fgets()` để nhập an toàn
   - Validate độ dài input
   - Không thể bypass authentication bằng buffer overflow

3. **Demo tấn công**:
   - Viết test case để chứng minh buffer overflow
   - Compile với và không có stack canary protection
   - So sánh kết quả

## **Dữ liệu vào**

**Normal input:**
```
Username: admin
Password: secret123
```

**Attack input (overflow):**
```
Username: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA (40+ characters)
Password: anything
```

## **Dữ liệu ra**

**Normal case:**
```
=== Authentication System ===
Username: admin
Password: secret123
Authentication: FAILED
Access: DENIED
```

**Attack case (vulnerable version):**
```
=== Authentication System ===
Username: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Password: anything
Authentication: FAILED
Access: GRANTED  ← Buffer overflow bypassed authentication!
```

**Attack case (secure version):**
```
=== Authentication System ===
Error: Username too long (max 20 characters)
Access: DENIED
```

**With stack canary:**
```
*** stack smashing detected ***: terminated
Aborted
```

## **Code khởi đầu**

```c
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERNAME 20
#define MAX_PASSWORD 20
#define CORRECT_USER "admin"
#define CORRECT_PASS "secret123"

/* Vulnerable version */
void vulnerable_login(void) {
    char username[16];
    char password[16];
    int is_authenticated = 0;
    
    printf("=== Vulnerable Authentication ===\n");
    printf("Username: ");
    gets(username);  /* UNSAFE! */
    
    printf("Password: ");
    gets(password);  /* UNSAFE! */
    
    /* Check credentials */
    if (strcmp(username, CORRECT_USER) == 0 && 
        strcmp(password, CORRECT_PASS) == 0) {
        is_authenticated = 1;
    }
    
    printf("\nAuthentication: %s\n", 
           is_authenticated ? "SUCCESS" : "FAILED");
    printf("Access: %s\n", 
           is_authenticated ? "GRANTED" : "DENIED");
}

/* TODO: Implement secure version */
bool secure_login(void) {
    char username[MAX_USERNAME + 1];
    char password[MAX_PASSWORD + 1];
    
    printf("=== Secure Authentication ===\n");
    
    /* TODO: Use fgets() to read username safely */
    /* TODO: Validate username length */
    /* TODO: Remove newline character */
    
    /* TODO: Use fgets() to read password safely */
    /* TODO: Validate password length */
    /* TODO: Remove newline character */
    
    /* TODO: Check credentials */
    
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
    }
    
    return 0;
}
```

## **Compilation và Testing**

### Compile vulnerable version (NO stack protection)
```bash
gcc -fno-stack-protector -o auth_vulnerable auth.c
./auth_vulnerable vulnerable
```

### Compile với stack canary protection
```bash
gcc -fstack-protector-all -o auth_protected auth.c
./auth_protected vulnerable
```

### Compile secure version
```bash
gcc -o auth_secure auth.c
./auth_secure secure
```

## **Test Cases**

### Test 1: Normal login
```bash
echo -e "admin\nsecret123" | ./auth_vulnerable vulnerable
# Expected: Access DENIED (wrong credentials demo)
```

### Test 2: Buffer overflow attack
```bash
echo -e "AAAAAAAAAAAAAAAAAAAAAAAAAAAA\nanything" | ./auth_vulnerable vulnerable
# Expected: May bypass authentication (is_authenticated overwritten)
```

### Test 3: Stack canary detection
```bash
echo -e "AAAAAAAAAAAAAAAAAAAAAAAAAAAA\nanything" | ./auth_protected vulnerable
# Expected: *** stack smashing detected ***
```

### Test 4: Secure version
```bash
echo -e "AAAAAAAAAAAAAAAAAAAAAAAAAAAA\nanything" | ./auth_secure secure
# Expected: Error: Username too long
```

## **Gợi ý**

1. **Stack layout trong vulnerable version:**
   ```
   High Address
   +------------------+
   | Return Address   | ← Target
   +------------------+
   | is_authenticated | ← Can be overwritten!
   +------------------+
   | password[16]     |
   +------------------+
   | username[16]     | ← Overflow starts here
   +------------------+
   Low Address
   ```

2. **Stack canary protection:**
   ```
   High Address
   +------------------+
   | Return Address   |
   +------------------+
   | Stack Canary     | ← Random value (e.g., 0xDEADBEEF)
   +------------------+
   | is_authenticated |
   +------------------+
   | Local variables  |
   +------------------+
   Low Address
   ```

3. **Safe input reading:**
   ```c
   if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
       return false;
   }
   buffer[strcspn(buffer, "\n")] = '\0';
   if (strlen(buffer) >= max_len) {
       fprintf(stderr, "Error: Input too long\n");
       return false;
   }
   ```

## **Câu hỏi phân tích**

1. **Buffer Overflow:**
   - Giải thích cách buffer overflow có thể bypass authentication
   - Tại sao `is_authenticated` có thể bị ghi đè?
   - Stack layout ảnh hưởng như thế nào?

2. **Stack Canary:**
   - Stack canary hoạt động như thế nào?
   - Tại sao gọi là "canary" (chim hoàng yến)?
   - Khi nào stack canary được kiểm tra?

3. **Security:**
   - Tại sao `gets()` bị deprecated?
   - Sự khác biệt giữa `-fno-stack-protector` và `-fstack-protector-all`?
   - Ngoài stack canary, còn cơ chế bảo vệ nào khác?

## **Bonus Challenge**

1. **ASLR (Address Space Layout Randomization):**
   - Tìm hiểu về ASLR và cách nó bảo vệ chương trình
   - Test với ASLR enabled/disabled

2. **Format String Vulnerability:**
   - Thêm lỗ hổng format string vào vulnerable version
   - Demo cách khai thác và cách phòng chống

3. **Secure Coding:**
   - Implement password hashing (không lưu plaintext)
   - Thêm rate limiting (giới hạn số lần login thất bại)
   - Implement secure password input (không hiển thị khi gõ)

4. **Memory Analysis:**
   - Sử dụng `gdb` để xem stack layout
   - Tìm vị trí của stack canary trong memory
   - Phân tích assembly code để hiểu cơ chế protection
