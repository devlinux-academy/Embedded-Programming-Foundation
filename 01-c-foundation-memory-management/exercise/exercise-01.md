# **Bài tập 1 — Sửa lỗi Stack Overflow trong hàm hiệu chuẩn cảm biến (Medium)**

## **Mục tiêu**

Hiểu việc sử dụng đệ quy quá sâu dẫn đến lỗi **stack overflow**, và học cách sửa nó bằng việc kiểm soát độ sâu đệ quy.

## **Bối cảnh**

Một hệ thống embedded sử dụng hàm đệ quy để hiệu chuẩn cảm biến.
Tuy nhiên, hàm đệ quy này **không dừng đúng cách** khi giá trị hiệu chuẩn đã ổn định → dẫn đến **tràn stack (stack overflow)** trên phần cứng thật.

Nhiệm vụ của bạn là **gỡ lỗi và sửa lại hàm**.

## **Yêu cầu**

Viết lại hàm sao cho:

* Đệ quy **dừng lại** khi `x == 0`
* Hàm **trả về 0**
* Không xảy ra đệ quy vô hạn
* Không gây ra lỗi **stack overflow**

## **Dữ liệu vào**

Một số nguyên **x** — giá trị hiệu chuẩn ban đầu.

## **Dữ liệu ra**

In ra kết quả hiệu chuẩn cuối cùng.

## **Ví dụ Input**

```
5
```

## **Ví dụ Output**

```
0
```

## **Code khởi đầu**

```c
#include <stdio.h>
#include <stdlib.h>

int calibrate(int x) {
    // HÀM LỖI - Hãy sửa lại
    if (x > 0)
        return calibrate(x - 1);
    return calibrate(x);
}

int main() {
    int x;
    scanf("%d", &x);

    int result = calibrate(x);
    printf("%d", result);

    return 0;
}
```