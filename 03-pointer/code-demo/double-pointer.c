#include <stdio.h>

int main(void) {
    int x = 10;
    int *ptr = &x;     // Level 1 pointer points to x
    int **pptr = &ptr; // Level 2 pointer points to ptr

    printf("Value of x         = %d\n", x);
    printf("Value of *ptr      = %d\n", *ptr);
    printf("Value of **pptr    = %d\n", **pptr);

    // Change value of x through double pointer
    **pptr = 20;
    printf("\nAfter changing via double pointer:\n");
    printf("Value of x         = %d\n", x);
    printf("Value of *ptr      = %d\n", *ptr);
    printf("Value of **pptr    = %d\n", **pptr);

    return 0;
}