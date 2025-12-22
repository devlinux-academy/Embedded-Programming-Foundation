# **Đáp án Bài tập 1 — Buffer I/O Performance Analysis**

## **Giải thích**

Bài tập này demo sự khác biệt giữa buffered và unbuffered I/O. Khi sử dụng buffering, dữ liệu được tích lũy trong buffer và chỉ ghi xuống kernel (system call) khi buffer đầy hoặc được flush. Điều này giảm đáng kể số lượng system calls, cải thiện hiệu năng.

## **Code hoàn chỉnh**

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_LINES 1000
#define BUFFER_SIZE 8192

void test_buffered(void) {
    char buffer[BUFFER_SIZE];
    
    /* Set full buffering */
    setvbuf(stdout, buffer, _IOFBF, BUFFER_SIZE);
    
    for (int i = 0; i < NUM_LINES; i++) {
        printf("Line %d: Test output\n", i);
    }
    
    /* Flush buffer to ensure all data is written */
    fflush(stdout);
}

void test_unbuffered(void) {
    /* Set no buffering */
    setvbuf(stdout, NULL, _IONBF, 0);
    
    for (int i = 0; i < NUM_LINES; i++) {
        printf("Line %d: Test output\n", i);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [buffered|unbuffered]\n", argv[0]);
        return 1;
    }
    
    if (argv[1][0] == 'b') {
        test_buffered();
    } else if (argv[1][0] == 'u') {
        test_unbuffered();
    } else {
        fprintf(stderr, "Invalid option. Use 'buffered' or 'unbuffered'\n");
        return 1;
    }
    
    return 0;
}
```

## **Kết quả phân tích với strace**

### Compile và chạy

```bash
gcc -o buffer_test buffer_test.c

# Test buffered
strace -c ./buffer_test buffered 2>&1 | tail -20

# Test unbuffered
strace -c ./buffer_test unbuffered 2>&1 | tail -20
```

### Đếm write() calls

```bash
# Buffered: ~1-5 calls
strace -e write ./buffer_test buffered 2>&1 | grep "write(1" | wc -l

# Unbuffered: 1000 calls
strace -e write ./buffer_test unbuffered 2>&1 | grep "write(1" | wc -l
```

### Kết quả mẫu

**Buffered mode:**
```
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
  0.00    0.000000           0         4           write
```

**Unbuffered mode:**
```
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 95.23    0.002000           2      1000           write
```

## **Phân tích**

### 1. Tại sao buffered I/O có ít write() calls hơn?

Buffered I/O tích lũy dữ liệu trong buffer (8KB) trước khi gọi `write()`. Với mỗi dòng ~20 bytes, buffer có thể chứa ~400 dòng trước khi đầy. Do đó, 1000 dòng chỉ cần ~3 lần `write()`.

### 2. Tiết kiệm system calls

```
Unbuffered: 1000 write() calls
Buffered: 3-5 write() calls
Tiết kiệm: ~99.5% system calls
```

### 3. Khi nào dùng buffered/unbuffered?

**Buffered I/O:**
- ✅ Logging files
- ✅ Data processing
- ✅ Khi hiệu năng quan trọng

**Unbuffered I/O:**
- ✅ Error messages (cần hiển thị ngay)
- ✅ Interactive input
- ✅ Real-time debugging

### 4. Trade-offs

**Buffering:**
- ✅ Ưu điểm: Hiệu năng cao, ít system calls
- ❌ Nhược điểm: Dữ liệu có thể bị mất nếu crash trước khi flush

**No buffering:**
- ✅ Ưu điểm: Dữ liệu được ghi ngay lập tức
- ❌ Nhược điểm: Hiệu năng thấp, nhiều system calls

## **Bonus Challenge - Line Buffering**

```c
void test_line_buffered(void) {
    /* Set line buffering */
    setvbuf(stdout, NULL, _IOLBF, 0);
    
    for (int i = 0; i < NUM_LINES; i++) {
        printf("Line %d: Test output\n", i);
        /* Flush occurs at each \n */
    }
}
```

**Kết quả:**
- Line buffering: 1000 write() calls (mỗi dòng 1 call)
- Giống unbuffered nhưng có buffer cho performance tốt hơn một chút

## **Memory Layout**

```
Buffered I/O:
User Space:  [Data] → [Buffer 8KB] → (buffer full) → System Call
Kernel:      write() called ~3 times

Unbuffered I/O:
User Space:  [Data] → (no buffer) → System Call
Kernel:      write() called 1000 times
```
