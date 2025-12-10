#include <stdio.h>
#include <stdint.h>

static void print_binary(uint8_t value) {
    int8_t i;
    
    for (i = 7; i >= 0; i--) {
        uint8_t bit = (value >> i) & 1U;
        printf("%u", bit);
        
        if (i == 4) {
            printf(" ");
        }
    }
}

int main(void) {
    uint8_t reg = 0b00001010U;  /* Initial value: 10 */
    uint8_t bit_position = 2U;
    
    printf("=== BIT MANIPULATION OPERATIONS ===\n\n");
    
    printf("Initial value:  %u  Binary: ", reg);
    print_binary(reg);
    printf("\n\n");
    
    reg |= (1U << bit_position);
    printf("1. Set bit %u:   %u  Binary: ", bit_position, reg);
    print_binary(reg);
    
    reg &= ~(1U << bit_position);
    printf("2. Clear bit %u: %u  Binary: ", bit_position, reg);
    print_binary(reg);
    
    reg ^= (1U << bit_position);
    printf("3. Toggle bit %u: %u  Binary: ", bit_position, reg);
    print_binary(reg);
    
    printf("4. Check bit %u: ", bit_position);
    if ((reg & (1U << bit_position)) != 0U) {
        printf("SET (1)\n");
    } else {
        printf("CLEAR (0)\n");
    }
    
    return 0;
}
