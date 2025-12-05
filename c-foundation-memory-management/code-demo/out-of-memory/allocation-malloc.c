#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void) {
    size_t size = 1024UL * 1024UL * 1024UL * 1024UL; /* ~ 1 TB */

    uint8_t *ptr = (uint8_t *)malloc(size);
    if (ptr == NULL) {
        printf("Out of Memory! malloc failed.\n");
        return 1;
    }

    printf("Allocated memory successfully.\n");

    free(ptr);
    return 0;
}