# **Bài tập 3 — Gỡ lỗi Memory Leak trong Telemetry Handler (Medium)**

## **Mục tiêu**

Xác định lỗi **rò rỉ bộ nhớ (memory leak)** do thiếu `free()` và sửa lại.

## **Bối cảnh**

Module telemetry này bị rò rỉ bộ nhớ sau mỗi gói dữ liệu.
Nguyên nhân là lập trình viên ban đầu **quên giải phóng bộ nhớ tạm thời** được cấp phát trong hàm.

## **Yêu cầu**

Chỉnh sửa code sao cho:

* Hàm `parse_packet()` **không gây rò rỉ bộ nhớ**
* Hàm **không được trả về vùng nhớ cấp phát động**
* Gợi ý: trả về một số nguyên đã xử lý, hoặc một cấu trúc nhỏ.

Bạn có thể thiết kế lại hoàn toàn hàm.

 

## **Dữ liệu vào**

Một dòng văn bản biểu diễn một telemetry packet.

## **Dữ liệu ra**

In `"OK"` sau khi xử lý packet an toàn, không rò rỉ bộ nhớ.

 

## **Ví dụ Input**

```
TEMP:32
```

## **Ví dụ Output**

```
OK
```

 

## **Code khởi đầu**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* parse_packet(const char *msg) {
    char *copy = malloc(100);
    strcpy(copy, msg);

    return copy;
}

int main() {
    char msg[100];
    scanf("%[^\n]", msg);

    char *out = parse_packet(msg);

    printf("OK");

    return 0;
}
```