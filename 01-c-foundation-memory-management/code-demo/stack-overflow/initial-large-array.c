#include <stdint.h>
#include <stdio.h>

#define LARGE_SIZE 20000000U  /* ~20 MB */

static void causeStackOverflow(void) {
    /* This array is on the stack, too large will cause overflow */
    uint8_t buffer[LARGE_SIZE];

    /* Use buffer to avoid compiler optimization */
    buffer[0] = 1U;
}

int main(void) {
    causeStackOverflow();

    printf("Hello from main\n");
}