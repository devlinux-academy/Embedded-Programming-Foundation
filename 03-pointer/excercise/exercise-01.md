# **Bài tập 1 — Quản lý Buffer Ring sử dụng Con trỏ (Medium)**

## **Mục tiêu**

Hiểu cách sử dụng con trỏ để quản lý bộ đệm vòng (ring buffer) trong hệ thống embedded, đặc biệt cho UART communication.

## **Bối cảnh**

Bạn đang phát triển driver UART cho vi điều khiển. Để xử lý dữ liệu nhận được từ UART một cách hiệu quả, bạn cần implement một ring buffer sử dụng con trỏ.

Ring buffer có các đặc điểm:
- Kích thước cố định (circular buffer)
- Hai con trỏ: `head` (vị trí ghi) và `tail` (vị trí đọc)
- Khi buffer đầy, dữ liệu mới sẽ ghi đè dữ liệu cũ (overwrite mode)

## **Yêu cầu**

Hoàn thiện các hàm sau:
- `buffer_write(RingBuffer *rb, uint8_t data)` - Ghi 1 byte vào buffer
- `buffer_read(RingBuffer *rb, uint8_t *data)` - Đọc 1 byte từ buffer
- `buffer_available(RingBuffer *rb)` - Trả về số byte có sẵn để đọc
- `buffer_is_empty(RingBuffer *rb)` - Kiểm tra buffer có rỗng không

## **Dữ liệu vào**

- Dòng 1: Kích thước buffer N (1 ≤ N ≤ 100)
- Dòng 2: Số lượng lệnh M
- M dòng tiếp theo, mỗi dòng chứa:
  - `W value` - Write giá trị value vào buffer (0-255)
  - `R` - Read 1 byte từ buffer
  - `A` - Query số byte available
  - `E` - Query buffer empty (1=empty, 0=not empty)

## **Dữ liệu ra**

- Với mỗi lệnh Read (R): In ra giá trị đọc được, hoặc `-1` nếu buffer rỗng
- Với mỗi lệnh Available (A): In ra số byte có sẵn
- Với mỗi lệnh Empty (E): In ra `1` hoặc `0`

## **Ví dụ Input**

```
3
10
W 10
W 20
W 30
A
R
R
W 40
W 50
R
A
```

## **Ví dụ Output**

```
3
10
20
30
2
```

## **Giải thích**

- Buffer size = 3
- Write 10, 20, 30 → buffer = [10, 20, 30], head=0, tail=0
- Available → 3 bytes
- Read → 10, buffer = [_, 20, 30], tail=1
- Read → 20, buffer = [_, _, 30], tail=2
- Write 40, 50 → buffer = [40, 50, 30], head=2 (overwrite mode)
- Read → 30, tail=0
- Available → 2 bytes (40, 50 còn lại)

## **Code khởi đầu**

```c
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_BUFFER_SIZE 100

typedef struct {
    uint8_t buffer[MAX_BUFFER_SIZE];
    uint8_t *head;
    uint8_t *tail;
    uint8_t *buffer_start;
    uint8_t *buffer_end;
    uint8_t size;
    uint8_t count;
} RingBuffer;

void buffer_init(RingBuffer *rb, uint8_t size) {
    rb->size = size;
    rb->count = 0;
    rb->buffer_start = rb->buffer;
    rb->buffer_end = rb->buffer + size;
    rb->head = rb->buffer_start;
    rb->tail = rb->buffer_start;
}

void buffer_write(RingBuffer *rb, uint8_t data) {
    // TODO: Implement this function
    // Use pointer arithmetic to manage circular buffer
}

bool buffer_read(RingBuffer *rb, uint8_t *data) {
    // TODO: Implement this function
    // Return true if read successful, false if buffer empty
    return false;
}

uint8_t buffer_available(RingBuffer *rb) {
    // TODO: Implement this function
    return 0;
}

bool buffer_is_empty(RingBuffer *rb) {
    // TODO: Implement this function
    return true;
}

int main() {
    RingBuffer rb;
    uint8_t size;
    int m;
    
    scanf("%hhu", &size);
    buffer_init(&rb, size);
    
    scanf("%d", &m);
    
    for (int i = 0; i < m; i++) {
        char cmd;
        scanf(" %c", &cmd);
        
        if (cmd == 'W') {
            uint8_t value;
            scanf("%hhu", &value);
            buffer_write(&rb, value);
        } else if (cmd == 'R') {
            uint8_t data;
            if (buffer_read(&rb, &data)) {
                printf("%u\n", data);
            } else {
                printf("-1\n");
            }
        } else if (cmd == 'A') {
            printf("%u\n", buffer_available(&rb));
        } else if (cmd == 'E') {
            printf("%u\n", buffer_is_empty(&rb) ? 1 : 0);
        }
    }
    
    return 0;
}
```
