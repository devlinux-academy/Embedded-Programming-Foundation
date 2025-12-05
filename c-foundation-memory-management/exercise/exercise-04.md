
# **Exercise 4 — Detect Stack Overflow in ISR Nested Calls (Medium/Hard)**

## **Objective**

Simulate stack usage analysis in nested ISR calls.

## **Background**

An embedded board has a 2 KB system stack.
A buggy developer wrote an ISR that calls a chain of functions, each consuming stack.
But the system does not check total stack usage → leading to stack overflow.

---

## **Buggy Code**

```c
int processA(int x) { int arr[300]; return x+1; }
int processB(int x) { int arr[400]; return processA(x); }
int processC(int x) { int arr[500]; return processB(x); }

int isr_handler(int x) {
    return processC(x); // may overflow!
}
```

## **Real Stack Usage**

* A: 300 * 4 = 1200 bytes
* B: 400 * 4 = 1600 bytes
* C: 500 * 4 = 2000 bytes
  Total nested stack = 4800 bytes → **Overflow** on a 2 KB stack.

## **Task**

Modify the program so:

* It **computes total required stack size**
* If stack > 2048 bytes → print `"Stack Overflow"`
* Otherwise → `"Safe"`

Do **not** actually allocate arrays.
Simulate by summing the sizes.

## **Input Format**

No input.

## **Output Format**

`Stack Overflow` or `Safe`

## **Sample Output**

```
Stack Overflow
```

---

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
    // BUG: developer does not check stack usage

    int result = processC(0);
    printf("%d", result);

    return 0;
}
```