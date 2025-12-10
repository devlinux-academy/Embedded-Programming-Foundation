# **Bài tập 2 — Sửa lỗi Out-of-Memory trong Data Logger (Medium/Hard)**

## **Mục tiêu**

Nhận diện và sửa lỗi cấp phát bộ nhớ động dẫn đến tình trạng **hết bộ nhớ (Out-of-Memory)**.

## **Bối cảnh**

Firmware đọc các gói dữ liệu (sensor packets) và cấp phát bộ nhớ động cho mỗi gói.
Tuy nhiên, lập trình viên ban đầu đã mắc lỗi khiến chương trình cấp phát **những vùng nhớ khổng lồ** do **tràn số học (integer overflow)** trong phép nhân.

 

## **Yêu cầu**

Sửa lại code sao cho:

* Không xảy ra tràn số học (integer overflow)
* Giới hạn bộ nhớ cấp phát tối đa là **128 MB**
* Nếu `packet_count * 1MB` vượt quá 128 MB → in `"OOM"`
* Ngược lại, cấp phát bộ nhớ một cách an toàn

 

## **Dữ liệu vào**

Một số nguyên `packet_count`.

## **Dữ liệu ra**

`Allocated` hoặc `OOM`.

 

## **Ví dụ Input**

```
200
```

## **Ví dụ Output**

```
OOM
```

 

## **Code khởi đầu**

```c
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
    uint32_t packet_count;
    scanf("%u", &packet_count);

    // BUG: phép nhân không an toàn, có thể bị tràn số
    uint32_t size = packet_count * 1024 * 1024;

    uint8_t *buffer = malloc(size);

    if (buffer == NULL)
        printf("OOM\n");
    else
        printf("Allocated\n");

    free(buffer);
    return 0;
}
```