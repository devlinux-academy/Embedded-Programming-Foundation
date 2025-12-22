# **Bài tập 2 — Safe String Input System (Medium)**

## **Mục tiêu**

Học cách sử dụng các hàm I/O an toàn (`fgets`, `snprintf`) để tránh buffer overflow và xử lý input validation.

## **Bối cảnh**

Bạn đang xây dựng một hệ thống nhập liệu cho embedded device. Hệ thống cần nhận thông tin người dùng (tên, tuổi, email) và đảm bảo không bị buffer overflow attack.

## **Yêu cầu**

Viết chương trình C để:

1. Nhập thông tin người dùng:
   - Tên (tối đa 50 ký tự)
   - Tuổi (số nguyên 1-150)
   - Email (tối đa 100 ký tự)
2. Validate input:
   - Tên không được rỗng
   - Tuổi phải trong khoảng hợp lệ
   - Email phải chứa ký tự '@'
3. Sử dụng `fgets()` thay vì `gets()` hoặc `scanf()`
4. Sử dụng `snprintf()` để format output an toàn
5. Xử lý trường hợp input quá dài

## **Dữ liệu vào**

```
Enter name: John Doe
Enter age: 25
Enter email: john.doe@example.com
```

## **Dữ liệu ra**

```
=== User Information ===
Name: John Doe
Age: 25
Email: john.doe@example.com
Status: Valid
```

## **Trường hợp lỗi**

**Input quá dài:**
```
Enter name: [string with 100 characters]
Error: Name too long (max 50 characters)
```

**Tuổi không hợp lệ:**
```
Enter age: 200
Error: Age must be between 1 and 150
```

**Email không hợp lệ:**
```
Enter email: invalidemail
Error: Email must contain '@'
```

## **Code khởi đầu**

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NAME_LEN 50
#define MAX_EMAIL_LEN 100
#define MIN_AGE 1
#define MAX_AGE 150

typedef struct {
    char name[MAX_NAME_LEN + 1];
    int age;
    char email[MAX_EMAIL_LEN + 1];
} UserInfo;

bool read_name(char *name, size_t max_len) {
    printf("Enter name: ");
    
    /* TODO: Use fgets() to read name safely */
    /* TODO: Remove newline character */
    /* TODO: Check if input is too long */
    /* TODO: Validate name is not empty */
    
    return true;
}

bool read_age(int *age) {
    char buffer[10];
    printf("Enter age: ");
    
    /* TODO: Use fgets() to read input */
    /* TODO: Convert to integer */
    /* TODO: Validate age range */
    
    return true;
}

bool read_email(char *email, size_t max_len) {
    printf("Enter email: ");
    
    /* TODO: Use fgets() to read email safely */
    /* TODO: Remove newline character */
    /* TODO: Validate email contains '@' */
    
    return true;
}

void print_user_info(const UserInfo *user) {
    /* TODO: Use snprintf() to safely format output */
    printf("=== User Information ===\n");
    /* TODO: Print name, age, email */
}

int main(void) {
    UserInfo user;
    
    if (!read_name(user.name, MAX_NAME_LEN)) {
        return 1;
    }
    
    if (!read_age(&user.age)) {
        return 1;
    }
    
    if (!read_email(user.email, MAX_EMAIL_LEN)) {
        return 1;
    }
    
    print_user_info(&user);
    printf("Status: Valid\n");
    
    return 0;
}
```

## **Gợi ý**

1. **Đọc string an toàn:**
   ```c
   fgets(buffer, sizeof(buffer), stdin);
   buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline
   ```

2. **Kiểm tra input quá dài:**
   ```c
   if (strlen(buffer) >= max_len) {
       fprintf(stderr, "Error: Input too long\n");
       return false;
   }
   ```

3. **Convert string to int:**
   ```c
   char *endptr;
   long value = strtol(buffer, &endptr, 10);
   if (*endptr != '\0') {
       // Invalid number
   }
   ```

4. **Kiểm tra email:**
   ```c
   if (strchr(email, '@') == NULL) {
       fprintf(stderr, "Error: Email must contain '@'\n");
       return false;
   }
   ```

5. **Format output an toàn:**
   ```c
   char output[200];
   snprintf(output, sizeof(output), "Name: %s, Age: %d", name, age);
   ```

## **Câu hỏi phân tích**

1. Tại sao `gets()` không an toàn và không nên sử dụng?
2. Sự khác biệt giữa `sprintf()` và `snprintf()` là gì?
3. Tại sao cần remove newline character sau khi dùng `fgets()`?
4. Làm thế nào để xử lý trường hợp người dùng nhập quá nhiều ký tự?

## **Bonus Challenge**

1. Thêm validation cho email format (phải có dạng `user@domain.com`)
2. Thêm chức năng clear input buffer khi input quá dài
3. Implement retry mechanism (cho phép nhập lại khi lỗi)
4. Thêm password field với input ẩn (không hiển thị khi gõ)
