# **Bài tập 1 — Điều khiển LED Matrix 8x8 bằng Bit Manipulation (Medium)**

## **Mục tiêu**

Hiểu cách sử dụng các phép toán bit (set, clear, toggle) để điều khiển LED trong hệ thống embedded.

## **Bối cảnh**

Bạn đang lập trình cho một LED matrix 8x8 trên vi điều khiển. Mỗi LED được điều khiển bởi 1 bit trong thanh ghi 8-bit.
Bạn cần viết các hàm để:
- Bật LED tại vị trí cụ thể
- Tắt LED tại vị trí cụ thể
- Đảo trạng thái LED (toggle)
- Kiểm tra trạng thái LED

## **Yêu cầu**

Hoàn thiện các hàm sau:
- `set_led(uint8_t *port, uint8_t position)` - Bật LED tại vị trí position
- `clear_led(uint8_t *port, uint8_t position)` - Tắt LED tại vị trí position
- `toggle_led(uint8_t *port, uint8_t position)` - Đảo trạng thái LED
- `check_led(uint8_t port, uint8_t position)` - Trả về 1 nếu LED đang bật, 0 nếu đang tắt

## **Dữ liệu vào**

- Dòng 1: Giá trị ban đầu của thanh ghi LED (0-255)
- Dòng 2: Số lượng lệnh N
- N dòng tiếp theo, mỗi dòng chứa:
  - `S position` - Set LED tại vị trí position
  - `C position` - Clear LED tại vị trí position
  - `T position` - Toggle LED tại vị trí position
  - `Q position` - Query (kiểm tra) LED tại vị trí position

## **Dữ liệu ra**

- Với mỗi lệnh Query (Q), in ra `1` hoặc `0`
- Dòng cuối cùng: Giá trị cuối cùng của thanh ghi (dạng số thập phân)

## **Ví dụ Input**

```
0
5
S 0
S 3
T 0
Q 0
Q 3
```

## **Ví dụ Output**

```
0
1
8
```

## **Giải thích**

- Ban đầu: `0b00000000` (0)
- Set bit 0: `0b00000001` (1)
- Set bit 3: `0b00001001` (9)
- Toggle bit 0: `0b00001000` (8)
- Query bit 0: 0 (đã tắt)
- Query bit 3: 1 (đang bật)
- Kết quả cuối: 8

## **Code khởi đầu**

```c
#include <stdio.h>
#include <stdint.h>

void set_led(uint8_t *port, uint8_t position) {
    // TODO: Implement this function
}

void clear_led(uint8_t *port, uint8_t position) {
    // TODO: Implement this function
}

void toggle_led(uint8_t *port, uint8_t position) {
    // TODO: Implement this function
}

uint8_t check_led(uint8_t port, uint8_t position) {
    // TODO: Implement this function
    return 0;
}

int main() {
    uint8_t led_port;
    int n;
    
    scanf("%hhu", &led_port);
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        char cmd;
        uint8_t pos;
        scanf(" %c %hhu", &cmd, &pos);
        
        if (cmd == 'S') {
            set_led(&led_port, pos);
        } else if (cmd == 'C') {
            clear_led(&led_port, pos);
        } else if (cmd == 'T') {
            toggle_led(&led_port, pos);
        } else if (cmd == 'Q') {
            printf("%u\n", check_led(led_port, pos));
        }
    }
    
    printf("%u\n", led_port);
    return 0;
}
```
