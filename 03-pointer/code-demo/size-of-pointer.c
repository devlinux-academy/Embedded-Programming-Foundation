#include <stdio.h>
#include <stdint.h>

int main(void) {
    char *ptr_char = NULL;
    int *ptr_int = NULL;
    float *ptr_float = NULL;
    double *ptr_double = NULL;
    void *ptr_void = NULL;

    printf("Basic Data Type Pointers:\n");
    printf("sizeof(char*)    = %zu bytes\n", sizeof(ptr_char));
    printf("sizeof(int*)     = %zu bytes\n", sizeof(ptr_int));
    printf("sizeof(float*)   = %zu bytes\n", sizeof(ptr_float));
    printf("sizeof(double*)  = %zu bytes\n", sizeof(ptr_double));
    printf("sizeof(void*)    = %zu bytes\n\n", sizeof(ptr_void));

    printf("Note: Pointer size depends on system architecture\n");
    printf("      32-bit system: pointers are 4 bytes\n");
    printf("      64-bit system: pointers are 8 bytes\n");
    return 0;
}
