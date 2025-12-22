# **Đáp án Bài tập 2 — Safe String Input System**

## **Giải thích**

Bài tập này demo cách sử dụng `fgets()` và `snprintf()` để tránh buffer overflow. Các hàm này giới hạn số ký tự được đọc/ghi, đảm bảo không vượt quá kích thước buffer.

## **Code hoàn chỉnh**

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
    char buffer[MAX_NAME_LEN + 10];
    
    printf("Enter name: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read input\n");
        return false;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    if (strlen(buffer) > max_len) {
        fprintf(stderr, "Error: Name too long (max %zu characters)\n", max_len);
        return false;
    }
    
    if (strlen(buffer) == 0) {
        fprintf(stderr, "Error: Name cannot be empty\n");
        return false;
    }
    
    strncpy(name, buffer, max_len);
    name[max_len] = '\0';
    
    return true;
}

bool read_age(int *age) {
    char buffer[10];
    
    printf("Enter age: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read input\n");
        return false;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    char *endptr;
    long value = strtol(buffer, &endptr, 10);
    
    if (*endptr != '\0') {
        fprintf(stderr, "Error: Age must be a number\n");
        return false;
    }
    
    if (value < MIN_AGE || value > MAX_AGE) {
        fprintf(stderr, "Error: Age must be between %d and %d\n", 
                MIN_AGE, MAX_AGE);
        return false;
    }
    
    *age = (int)value;
    return true;
}

bool read_email(char *email, size_t max_len) {
    char buffer[MAX_EMAIL_LEN + 10];
    
    printf("Enter email: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read input\n");
        return false;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    if (strlen(buffer) > max_len) {
        fprintf(stderr, "Error: Email too long (max %zu characters)\n", max_len);
        return false;
    }
    
    if (strchr(buffer, '@') == NULL) {
        fprintf(stderr, "Error: Email must contain '@'\n");
        return false;
    }
    
    strncpy(email, buffer, max_len);
    email[max_len] = '\0';
    
    return true;
}

void print_user_info(const UserInfo *user) {
    char output[300];
    
    printf("=== User Information ===\n");
    
    snprintf(output, sizeof(output), "Name: %s", user->name);
    printf("%s\n", output);
    
    snprintf(output, sizeof(output), "Age: %d", user->age);
    printf("%s\n", output);
    
    snprintf(output, sizeof(output), "Email: %s", user->email);
    printf("%s\n", output);
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

## **Ví dụ chạy chương trình**

### Test case 1: Input hợp lệ

```
$ ./safe_input
Enter name: John Doe
Enter age: 25
Enter email: john.doe@example.com
=== User Information ===
Name: John Doe
Age: 25
Email: john.doe@example.com
Status: Valid
```

### Test case 2: Name quá dài

```
$ ./safe_input
Enter name: ThisIsAVeryLongNameThatExceedsTheMaximumLengthAllowed
Error: Name too long (max 50 characters)
```

### Test case 3: Age không hợp lệ

```
$ ./safe_input
Enter name: John
Enter age: 200
Error: Age must be between 1 and 150
```

### Test case 4: Email không có @

```
$ ./safe_input
Enter name: John
Enter age: 25
Enter email: invalidemail.com
Error: Email must contain '@'
```

## **Giải thích chi tiết**

### 1. Tại sao gets() không an toàn?

```c
/* UNSAFE - gets() không kiểm tra kích thước buffer */
char buffer[10];
gets(buffer);  // Nếu user nhập 20 ký tự → Buffer overflow!

/* SAFE - fgets() giới hạn số ký tự đọc */
char buffer[10];
fgets(buffer, sizeof(buffer), stdin);  // Chỉ đọc tối đa 9 ký tự + '\0'
```

### 2. sprintf() vs snprintf()

```c
/* UNSAFE - sprintf() không kiểm tra kích thước */
char buffer[20];
sprintf(buffer, "Name: %s", very_long_name);  // Buffer overflow!

/* SAFE - snprintf() giới hạn số ký tự ghi */
char buffer[20];
snprintf(buffer, sizeof(buffer), "Name: %s", very_long_name);  // Truncated safely
```

### 3. Remove newline character

`fgets()` đọc cả ký tự newline `\n`, cần xóa nó:

```c
buffer[strcspn(buffer, "\n")] = '\0';

/* Hoặc cách khác: */
size_t len = strlen(buffer);
if (len > 0 && buffer[len-1] == '\n') {
    buffer[len-1] = '\0';
}
```

### 4. Xử lý input quá dài

Khi user nhập quá nhiều ký tự, `fgets()` chỉ đọc phần vừa buffer:

```c
char buffer[MAX_NAME_LEN + 10];  // Buffer lớn hơn max_len
fgets(buffer, sizeof(buffer), stdin);

if (strlen(buffer) > max_len) {
    fprintf(stderr, "Error: Input too long\n");
    return false;
}
```

## **Bonus Challenge Solutions**

### 1. Email validation nâng cao

```c
bool is_valid_email(const char *email) {
    const char *at = strchr(email, '@');
    if (at == NULL) return false;
    
    const char *dot = strchr(at, '.');
    if (dot == NULL) return false;
    
    if (at == email) return false;
    if (dot == at + 1) return false;
    if (*(dot + 1) == '\0') return false;
    
    return true;
}
```

### 2. Clear input buffer

```c
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
```

### 3. Retry mechanism

```c
bool read_name_with_retry(char *name, size_t max_len, int max_attempts) {
    for (int i = 0; i < max_attempts; i++) {
        if (read_name(name, max_len)) {
            return true;
        }
        printf("Please try again (%d/%d)\n", i + 1, max_attempts);
    }
    return false;
}
```

## **Security Best Practices**

1. ✅ Always use `fgets()` instead of `gets()`
2. ✅ Always use `snprintf()` instead of `sprintf()`
3. ✅ Validate input length before processing
4. ✅ Remove newline characters after `fgets()`
5. ✅ Use `strncpy()` instead of `strcpy()`
6. ✅ Always null-terminate strings
7. ✅ Validate input format and range
