# ✅ **Solution 1 — Fix Stack Overflow in Recursive Sensor Calibration**

## ✔️ Ý tưởng

* Vấn đề là recursion không có **điểm dừng** cho trường hợp `x == 0`.
* Ta chỉ cần:

  * Nếu `x <= 0` → trả về 0
  * Nếu `x > 0` → giảm dần về 0

## ✔️ Code Solution

```c
#include <stdio.h>
#include <stdlib.h>

int calibrate(int x) {
    // FIX: add valid base case
    if (x <= 0)
        return 0;

    return calibrate(x - 1);
}

int main() {
    int x;
    scanf("%d", &x);

    int result = calibrate(x);
    printf("%d", result);

    return 0;
}
```

---

# ✅ **Solution 2 — Fix Out-of-Memory Crash in Data Logger**

## ✔️ Ý tưởng

* Kiểm tra overflow bằng cách:

  * Nếu `packet_count > 128` → chắc chắn vượt 128 MB.
* Không thực hiện multiplication trước khi kiểm tra giới hạn.
* Chỉ allocate khi đúng giới hạn:

  * `size = packet_count * 1MB;`

## ✔️ Code Solution

```c
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_MB 128
#define ONE_MB (1024 * 1024)

int main() {
    uint32_t packet_count;
    scanf("%u", &packet_count);

    // Check limit first to avoid overflow
    if (packet_count > MAX_MB) {
        printf("OOM");
        return 0;
    }

    uint32_t size = packet_count * ONE_MB;

    uint8_t *buffer = malloc(size);
    if (buffer == NULL) {
        printf("OOM");
    } else {
        printf("Allocated");
        free(buffer);
    }

    return 0;
}
```

---

# ✅ **Solution 3 — Debug Memory Leak in Telemetry Handler**

## ✔️ Ý tưởng

* Không được return bộ nhớ động (heap).
* Không để memory leak.
* Giải pháp đúng:

  * Dùng bộ đệm cục bộ (stack buffer) thay vì malloc
    hoặc
  * Parse và trả về dữ liệu dạng primitive.

Ở đây, ta chỉ cần xử lý packet rồi in `"OK"` ⇒ chỉ cần dùng local buffer.

## ✔️ Code Solution

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_packet(const char *msg) {
    char copy[100];     // local buffer → no leak
    strcpy(copy, msg);

    // ... process packet ...
    // For exercise purpose, processing not required.
}

int main() {
    char msg[100];
    scanf("%[^\n]", msg);

    parse_packet(msg); // no memory leak now

    printf("OK");

    return 0;
}
```

---

# ✅ **Solution 4 — Detect Stack Overflow in ISR Nested Calls**

## ✔️ Ý tưởng

* Không allocate thật, chỉ “simulated”.
* Tính tổng stack:

  * A: 300 * 4 = 1200
  * B: 400 * 4 = 1600
  * C: 500 * 4 = 2000
  * Tổng: 4800 bytes
* So sánh với giới hạn 2048 bytes.

## ✔️ Code Solution

```c
#include <stdio.h>

int main() {
    int sizeA = 300 * 4;
    int sizeB = 400 * 4;
    int sizeC = 500 * 4;

    int total_stack = sizeA + sizeB + sizeC;

    if (total_stack > 2048)
        printf("Stack Overflow");
    else
        printf("Safe");

    return 0;
}
```