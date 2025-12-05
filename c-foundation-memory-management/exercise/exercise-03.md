# **Exercise 3 — Debug Memory Leak in Telemetry Handler (Medium)**

## **Objective**

Identify memory leak caused by missing free() and fix it.

## **Background**

This telemetry module leaks memory after each packet.
The original programmer forgot to free temporary buffers.

---

## **Buggy Code**

```c
char* parse_packet(const char *msg) {
    char *copy = malloc(100);  // temporary copy
    strcpy(copy, msg);

    // ... some processing ...

    return copy;   // BUG: caller never frees it -> leak!
}
```

## **Task**

Modify the code so:

* `parse_packet()` does **not** leak memory
* It should **not** return dynamically allocated memory
* Suggestion: return a processed integer or small struct instead.

You may redesign the function as needed.

## **Input Format**

A line of text representing a telemetry packet.

## **Output Format**

Print `"OK"` after safely processing the packet.

## **Sample Input**

```
TEMP:32
```

## **Sample Output**

```
OK
```

---

## **Starter Code**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* parse_packet(const char *msg) {
    char *copy = malloc(100);
    strcpy(copy, msg);

    // process...

    return copy;
}

int main() {
    char msg[100];
    scanf("%[^\n]", msg);

    char *out = parse_packet(msg);

    // BUG: never freed → memory leak
    printf("OK");

    return 0;
}
```