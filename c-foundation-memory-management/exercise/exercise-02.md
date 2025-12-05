# **Exercise 2 — Fix Out-of-Memory Crash in Data Logger (Medium/Hard)**

## **Objective**

Identify and repair a dynamic memory bug that causes out-of-memory conditions.

## **Background**

The firmware reads sensor packets and dynamically allocates memory for each packet.
However, the original programmer mistakenly allocates **gigantic memory blocks** due to integer overflow.

---

## **Buggy Code**

```c
uint32_t packet_count;
scanf("%u", &packet_count);

uint32_t size = packet_count * 1024 * 1024; // intended: packet_count MB
uint8_t *buffer = malloc(size);  // may overflow → request huge memory

if (buffer == NULL)
    printf("OOM\n");
else
    printf("Allocated\n");
```

## **Task**

Fix the code so:

* No integer overflow occurs
* The maximum allowed memory is **128 MB**
* If `packet_count * 1MB` exceeds 128MB → print `"OOM"`
* Otherwise allocate safely

## **Input Format**

A single integer packet_count.

## **Output Format**

`Allocated` or `OOM`.

## **Sample Input**

```
200
```

## **Sample Output**

```
OOM
```

---

## **Starter Code**

```c
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
    uint32_t packet_count;
    scanf("%u", &packet_count);

    // BUG: unsafe multiplication, integer overflow possible
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