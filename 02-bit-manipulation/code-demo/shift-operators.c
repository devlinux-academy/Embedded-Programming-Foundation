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
    uint8_t original_value = 128U;
    uint8_t left_shifted;
    uint8_t right_shifted;
    
    printf("=== BIT SHIFTING COMPARISON ===\n\n");
    
    printf("Original value: %u\n", original_value);
    printf("Binary:         ");
    print_binary(original_value);
    printf("\n\n");
    
    left_shifted = original_value << 2U;
    printf("Left shift << 2:  %u\n", left_shifted);
    printf("Binary:           ");
    print_binary(left_shifted);
    printf("\n\n");
    
    right_shifted = original_value >> 2U;
    printf("Right shift >> 2: %u\n", right_shifted);
    printf("Binary:           ");
    print_binary(right_shifted);
    printf("\n");
    
    return 0;
}