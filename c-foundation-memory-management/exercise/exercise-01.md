# **Exercise 1 — Fix Stack Overflow in Recursive Sensor Calibration (Medium)**

## **Objective**

Understand how excessive recursion causes stack overflow and learn how to fix it with controlled recursion depth.

## **Background**

An embedded system uses a recursive function to calibrate sensors.
However, the recursion does **not stop correctly** when calibration reaches a stable value → causing **stack overflow** on real hardware.

Your job is to **debug and fix the function**.

---

## **Buggy Code (Given in Template)**

```c
int calibrate(int x) {
    // Recursively adjusts until stable
    if (x > 0)
        return calibrate(x - 1);  // <--- BUG: no base case for x == 0
    
    return calibrate(x); // infinite recursion
}
```

## **Task**

Rewrite the function so that:

* The recursion stops at **x == 0**
* The function returns **0**
* No infinite recursion occurs
* No stack overflow occurs

## **Input Format**

A single integer **x** (initial calibration value)

## **Output Format**

Print the final calibration result.

## **Sample Input**

```
5
```

## **Sample Output**

```
0
```

---

## **Starter Code**

```c
#include <stdio.h>
#include <stdlib.h>

int calibrate(int x) {
    // BUGGY FUNCTION - Fix it
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