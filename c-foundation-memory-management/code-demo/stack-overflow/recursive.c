#include <stdint.h>
#include <stdio.h>

void causeStackOverflow(void) {
    /* Calls itself back without a stop condition */
    printf("Hello from function\n");
    causeStackOverflow();
}

int main(void){
    causeStackOverflow();

    /* Never come here */
    printf("Hello from main\n");
}
