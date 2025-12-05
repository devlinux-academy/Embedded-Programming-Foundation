Trong tài liệu này chúng ta sẽ tìm hiểu về phân vùng bộ nhớ Memory Layout của chương trình C thông qua ví dụ code sau :
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
