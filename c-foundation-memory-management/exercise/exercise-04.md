# **Bài 4 — Phát hiện Stack Overflow trong ISR có lời gọi lồng nhau (Medium/Hard)**

## **Mục tiêu**

Mô phỏng việc phân tích mức sử dụng stack khi các hàm được gọi lồng nhau trong ISR.

## **Bối cảnh**

Bo mạch nhúng chỉ có **stack hệ thống 2 KB**.
Một lập trình viên viết ISR gọi chuỗi hàm, mỗi hàm tiêu tốn thêm stack.
Hệ thống không kiểm tra tổng lượng stack cần dùng → dẫn đến **stack overflow**.


## **Mức sử dụng stack thực tế**

* A: 300 * 4 = 1200 bytes
* B: 400 * 4 = 1600 bytes
* C: 500 * 4 = 2000 bytes
  Tổng lời gọi lồng nhau = **4800 bytes** → **Overflow** với stack 2 KB.

 

## **Yêu cầu**

Sửa chương trình sao cho:

* Tính **tổng stack cần dùng** của chuỗi lời gọi hàm
* Nếu tổng > 2048 bytes → in `"Stack Overflow"`
* Ngược lại → in `"Safe"`
* **Không** được cấp phát thật các mảng → chỉ mô phỏng bằng cách cộng kích thước.

 

## **Định dạng Input**

Không có input.

## **Định dạng Output**

`Stack Overflow` hoặc `Safe`

## **Ví dụ Output**

```
Stack Overflow
```

 

## **Starter Code**

```c
#include <stdio.h>

int processA(int x) {
    int arr[300];
    return x + 1;
}

int processB(int x) {
    int arr[400];
    return processA(x);
}

int processC(int x) {
    int arr[500];
    return processB(x);
}

int main() {
    // BUG: lập trình viên không kiểm tra mức sử dụng stack

    int result = processC(0);
    printf("%d", result);

    return 0;
}
```