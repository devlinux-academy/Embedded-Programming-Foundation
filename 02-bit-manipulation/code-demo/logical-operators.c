#include <stdio.h>
#include <stdint.h>

void print_binary(uint8_t x) {
    for (int i = 7; i >= 0; i--)
        printf("%d", (x >> i) & 1U);
}

int main(void) {

    uint8_t a = 0b11001010;   /* 202 */
    uint8_t b = 0b10110100;   /* 180 */

    printf("a = "); print_binary(a); printf(" (202)\n");
    printf("b = "); print_binary(b); printf(" (180)\n\n");

    /* AND */
    uint8_t and_result = a & b;
    printf("a AND b = "); print_binary(and_result);
    printf(" (%u)\n\n", and_result);

    /* OR */
    uint8_t or_result = a | b;
    printf("a OR  b = "); print_binary(or_result);
    printf(" (%u)\n\n", or_result);

    /* XOR */
    uint8_t xor_result = a ^ b;
    printf("a XOR b = "); print_binary(xor_result);
    printf(" (%u)\n\n", xor_result);

    /* NOT */
    uint8_t not_a = (uint8_t)(~a);
    printf("NOT a   = "); print_binary(not_a);
    printf(" (%u)\n\n", not_a);

    return 0;
}