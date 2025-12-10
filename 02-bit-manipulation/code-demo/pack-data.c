#include <stdio.h>
#include <stdint.h>

int main() {
    uint8_t mode = 3;   // 3 bit
    uint8_t temp = 45;  // 6 bit
    uint8_t error = 7;  // 4 bit
    
    uint16_t packet = 0;
    
    packet |= (mode & 0x07) << 0;   // mask 3 bit: 0000 0111
    packet |= (temp & 0x3F) << 3;   // mask 6 bit: 0011 1111
    packet |= (error & 0x0F) << 9;  // mask 4 bit: 0000 1111
    
    printf("Packed 16-bit packet = 0x%04X\n", packet);
    return 0;
}