# C Foundation - Memory Management

Tài liệu này cung cấp kiến thức nền tảng về quản lý bộ nhớ trong ngôn ngữ lập trình C, bao gồm các ví dụ code demo minh họa các lỗi phổ biến và cách xử lý.

---

## 📁 Mô tả Code Demo

Thư mục `code-demo` chứa các ví dụ minh họa các lỗi bộ nhớ phổ biến trong C:

### 1. Memory Leak (`memory-leak/memory-leak.c`)
**Mục đích:** Minh họa lỗi rò rỉ bộ nhớ (memory leak)

**Mô tả:** 
- Chương trình cấp phát bộ nhớ liên tục trong vòng lặp (1KB mỗi lần)
- Không giải phóng bộ nhớ đã cấp phát (`free()` bị comment)
- Dẫn đến tiêu thụ bộ nhớ tăng dần cho đến khi hệ thống cạn kiệt tài nguyên
- Kết quả: Out of Memory hoặc bị OOM Killer chấm dứt tiến trình

### 2. Out of Memory (`out-of-memory/allocation-malloc.c`)
**Mục đích:** Minh họa lỗi cạn kiệt bộ nhớ khi cấp phát

**Mô tả:**
- Cố gắng cấp phát một khối bộ nhớ cực lớn (~1TB)
- Kiểm tra giá trị trả về của `malloc()` để phát hiện lỗi
- Xử lý trường hợp `malloc()` trả về `NULL` khi không đủ bộ nhớ
- Minh họa cách xử lý lỗi OOM đúng cách

### 3. Stack Overflow

#### a. Đệ quy vô hạn (`stack-overflow/recursive.c`)
**Mục đích:** Minh họa stack overflow do đệ quy vô hạn

**Mô tả:**
- Hàm tự gọi lại chính nó không có điều kiện dừng
- Mỗi lần gọi tạo một stack frame mới
- Stack bị tràn khi số lượng stack frame vượt quá giới hạn
- Chương trình sẽ crash với segmentation fault

#### b. Mảng cục bộ quá lớn (`stack-overflow/initial-large-array.c`)
**Mục đích:** Minh họa stack overflow do cấp phát mảng lớn trên stack

**Mô tả:**
- Khai báo mảng cục bộ có kích thước rất lớn (~20MB) trên stack
- Stack có kích thước giới hạn (thường 1-8MB)
- Cấp phát mảng lớn hơn giới hạn stack gây tràn ngăn xếp
- Giải pháp: Sử dụng cấp phát động trên heap với `malloc()`

---

## 🔧 Hướng dẫn viết Makefile

### Makefile cơ bản để biên dịch các code demo:

```makefile
# Compiler và flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Thư mục
CODE_DEMO = code-demo
BUILD_DIR = build

# Tạo thư mục build nếu chưa tồn tại
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Biên dịch tất cả các demo
all: $(BUILD_DIR) memory-leak oom stack-overflow-recursive stack-overflow-array

# Memory Leak Demo
memory-leak: $(CODE_DEMO)/memory-leak/memory-leak.c
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/memory-leak $<

# Out of Memory Demo
oom: $(CODE_DEMO)/out-of-memory/allocation-malloc.c
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/oom $<

# Stack Overflow - Recursive Demo
stack-overflow-recursive: $(CODE_DEMO)/stack-overflow/recursive.c
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/stack-overflow-recursive $<

# Stack Overflow - Large Array Demo
stack-overflow-array: $(CODE_DEMO)/stack-overflow/initial-large-array.c
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/stack-overflow-array $<

# Chạy các demo
run-memory-leak: memory-leak
	./$(BUILD_DIR)/memory-leak

run-oom: oom
	./$(BUILD_DIR)/oom

run-stack-recursive: stack-overflow-recursive
	./$(BUILD_DIR)/stack-overflow-recursive

run-stack-array: stack-overflow-array
	./$(BUILD_DIR)/stack-overflow-array

# Dọn dẹp
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean run-memory-leak run-oom run-stack-recursive run-stack-array
```

### Cách sử dụng Makefile:

```bash
# Biên dịch tất cả
make all

# Biên dịch từng demo riêng lẻ
make memory-leak
make oom
make stack-overflow-recursive
make stack-overflow-array

# Chạy demo
make run-memory-leak
make run-oom
make run-stack-recursive
make run-stack-array

# Dọn dẹp
make clean
```

---

## 📚 Tips và Kiến thức từ Documentation

### 1. Kiểm tra phân vùng bộ nhớ của biến (Memory Layout)

Trong tài liệu này chúng ta sẽ tìm hiểu về phân vùng bộ nhớ Memory Layout của chương trình C thông qua ví dụ code sau:

```c
#include <stdio.h>
#include <stdlib.h>

/* --- .data section: biến global có khởi tạo --- */
int g_data = 10;

/* --- .bss section: biến global không khởi tạo --- */
int g_bss;

/* --- .rodata section: biến hằng --- */
const char g_rodata[] = "Hello, RO data";

/* --- .text section: hàm của chương trình --- */
void func_demo(void) {
    /* empty */
}

int main(void) {
    /* --- Stack --- */
    int stack_var = 123;

    /* --- Heap --- */
    int *heap_var = (int*)malloc(sizeof(int));
    *heap_var = 999;

    printf("====== MEMORY LAYOUT DEMO ======\n");
    
    free(heap_var);
    return 0;
}
```

Sau khi biên dịch chương trình chúng ta chạy lệnh `nm` trên Linux để theo dõi các biến trong code thuộc phân vùng nào.

```bash
gcc -o demo main.c 
nm -S demo
```

Ta thu được kết quả:
```bash
toanonestar@toan:~/test$ nm -S demo 
000000000000038c 0000000000000020 r __abi_tag
0000000000004014 B __bss_start
0000000000004014 0000000000000001 b completed.0
                 w __cxa_finalize@GLIBC_2.2.5
0000000000004000 D __data_start
0000000000004000 W data_start
00000000000010d0 t deregister_tm_clones
0000000000001140 t __do_global_dtors_aux
0000000000003db0 d __do_global_dtors_aux_fini_array_entry
0000000000004008 D __dso_handle
0000000000003db8 d _DYNAMIC
0000000000004014 D _edata
0000000000004020 B _end
00000000000011e4 T _fini
0000000000001180 t frame_dummy
0000000000003da8 d __frame_dummy_init_array_entry
0000000000002140 r __FRAME_END__
                 U free@GLIBC_2.2.5
0000000000001189 000000000000000b T func_demo
0000000000004018 0000000000000004 B g_bss
0000000000004010 0000000000000004 D g_data
0000000000003fa8 d _GLOBAL_OFFSET_TABLE_
                 w __gmon_start__
000000000000203c r __GNU_EH_FRAME_HDR
0000000000002008 000000000000000f R g_rodata
0000000000001000 T _init
0000000000002000 0000000000000004 R _IO_stdin_used
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 U __libc_start_main@GLIBC_2.34
0000000000001194 000000000000004d T main
                 U malloc@GLIBC_2.2.5
                 U puts@GLIBC_2.2.5
0000000000001100 t register_tm_clones
00000000000010a0 0000000000000026 T _start
0000000000004018 D __TMC_END__
```

Từ đó ta có thể tra phân vùng của biến trong bảng sau:

| Ký hiệu   | Phân vùng        | Ý nghĩa                                              |
| --------- | ---------------- | ---------------------------------------------------- |
| **T / t** | `.text`          | Code (hàm thực thi)                                  |
| **D / d** | `.data`          | Biến global **khởi tạo ≠ 0**                         |
| **B / b** | `.bss`           | Biến global **không khởi tạo** hoặc **khởi tạo = 0** |
| **R / r** | `.rodata`        | Hằng số, dữ liệu chỉ đọc                             |
| **U**     | Unresolved       | Symbol từ thư viện ngoài                             |
| **W**     | Weak symbol      | Symbol yếu                                           |
| **w**     | weak, local      |                                                      |
| **r**     | read-only, local |                                                      |
| **d**     | data local       |                                                      |
| **b**     | bss local        |                                                      |

---

### 2. Quản lý bộ nhớ (Memory Management)

