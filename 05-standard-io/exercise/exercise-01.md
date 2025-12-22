# **Bài tập 1 — Buffer I/O Performance Analysis (Medium)**

## **Mục tiêu**

Hiểu rõ sự khác biệt giữa buffered và unbuffered I/O, và cách buffering giảm thiểu system calls để tối ưu hiệu năng.

## **Bối cảnh**

Bạn đang phát triển một ứng dụng logging cho embedded system. Hệ thống cần ghi log liên tục, và bạn muốn tối ưu hóa hiệu năng bằng cách giảm số lượng system calls. Bạn cần so sánh hiệu năng giữa buffered và unbuffered I/O.

## **Yêu cầu**

Viết chương trình C để:

1. Tạo hai hàm test:
   - `test_buffered()`: Sử dụng full buffering (`_IOFBF`)
   - `test_unbuffered()`: Không sử dụng buffering (`_IONBF`)
2. Mỗi hàm ghi 1000 dòng text ra stdout
3. Sử dụng `strace` để đếm số lượng `write()` system calls
4. So sánh và phân tích kết quả

## **Dữ liệu vào**

Chương trình nhận 1 tham số dòng lệnh:
```
./program [buffered|unbuffered]
```

## **Dữ liệu ra**

Chương trình in ra 1000 dòng với format:
```
Line 0: Test output
Line 1: Test output
Line 2: Test output
...
Line 999: Test output
```

## **Phân tích với strace**

Chạy các lệnh sau để phân tích:

```bash
# Compile
gcc -o buffer_test buffer_test.c

# Test buffered
strace -c ./buffer_test buffered 2>&1 | grep -A 20 "% time"

# Test unbuffered
strace -c ./buffer_test unbuffered 2>&1 | grep -A 20 "% time"

# Count write() calls
strace -e write ./buffer_test buffered 2>&1 | grep "write(1" | wc -l
strace -e write ./buffer_test unbuffered 2>&1 | grep "write(1" | wc -l
```

## **Kết quả mong đợi**

| Mode | write() calls | Performance |
|------|---------------|-------------|
| Buffered | 1-5 calls | Fast |
| Unbuffered | 1000 calls | Slow |

## **Code khởi đầu**

```c
#include <stdio.h>
#include <string.h>

#define NUM_LINES 1000

void test_buffered(void) {
    /* TODO: Set full buffering */
    
    for (int i = 0; i < NUM_LINES; i++) {
        printf("Line %d: Test output\n", i);
    }
    
    /* TODO: Flush buffer */
}

void test_unbuffered(void) {
    /* TODO: Set no buffering */
    
    for (int i = 0; i < NUM_LINES; i++) {
        printf("Line %d: Test output\n", i);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [buffered|unbuffered]\n", argv[0]);
        return 1;
    }
    
    /* TODO: Check argv[1] and call appropriate function */
    
    return 0;
}
```

## **Gợi ý**

1. Sử dụng `setvbuf(stdout, buffer, mode, size)` để thiết lập buffering
2. Các mode buffering:
   - `_IOFBF`: Full buffering (buffer đầy mới flush)
   - `_IOLBF`: Line buffering (gặp `\n` thì flush)
   - `_IONBF`: No buffering (ghi ngay lập tức)
3. Sử dụng `fflush(stdout)` để force flush buffer
4. Buffer size nên là 8192 bytes (8KB) cho full buffering

## **Câu hỏi phân tích**

1. Tại sao buffered I/O có ít `write()` calls hơn?
2. Buffering giúp tiết kiệm bao nhiêu system calls (tính theo %)?
3. Trong embedded systems, khi nào nên dùng buffered I/O và khi nào nên dùng unbuffered?
4. Trade-off của buffering là gì?

## **Bonus Challenge**

1. Thêm chế độ line buffering (`_IOLBF`) và so sánh với 2 chế độ trên
2. Đo thời gian thực thi của mỗi chế độ bằng `time` command
3. Thử với buffer size khác nhau (1KB, 4KB, 8KB, 16KB) và phân tích
