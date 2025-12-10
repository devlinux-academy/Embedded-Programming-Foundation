#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void) {
    for (size_t i = 0UL; i < 1000000000UL; i++) {
        uint8_t *p = (uint8_t *)malloc(1024UL); /* 1 KB */

        if (p == NULL) {
            printf("Out of Memory! System cannot allocate more.\n");
            return 1;
        }
        
        /* No free(p);  --> Memory leak */
        /* -> OOM Killed */
    }

    return 0;
}