#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
  uint8_t a;  /* 1 byte */
  uint32_t b; /* 4 bytes */
  uint8_t c;  /* 1 byte */
  uint16_t d; /* 2 bytes */
} UnoptimizedStruct;

typedef struct {
  uint32_t b; /* 4 bytes */
  uint16_t d; /* 2 bytes */
  uint8_t a;  /* 1 byte */
  uint8_t c;  /* 1 byte */
} OptimizedStruct;

typedef struct __attribute__((packed)) {
  uint8_t a;
  uint32_t b;
  uint8_t c;
  uint16_t d;
} PackedStruct;

int main(void) {
  printf("=== Structure Padding and Alignment Demo ===\n\n");

  printf("UnoptimizedStruct:\n");
  printf("  sizeof = %zu bytes\n", sizeof(UnoptimizedStruct));
  printf("  offsetof(a) = %zu\n", offsetof(UnoptimizedStruct, a));
  printf("  offsetof(b) = %zu\n", offsetof(UnoptimizedStruct, b));
  printf("  offsetof(c) = %zu\n", offsetof(UnoptimizedStruct, c));
  printf("  offsetof(d) = %zu\n\n", offsetof(UnoptimizedStruct, d));

  printf("OptimizedStruct:\n");
  printf("  sizeof = %zu bytes\n", sizeof(OptimizedStruct));
  printf("  offsetof(b) = %zu\n", offsetof(OptimizedStruct, b));
  printf("  offsetof(d) = %zu\n", offsetof(OptimizedStruct, d));
  printf("  offsetof(a) = %zu\n", offsetof(OptimizedStruct, a));
  printf("  offsetof(c) = %zu\n\n", offsetof(OptimizedStruct, c));

  printf("PackedStruct:\n");
  printf("  sizeof = %zu bytes\n", sizeof(PackedStruct));
  printf("  offsetof(a) = %zu\n", offsetof(PackedStruct, a));
  printf("  offsetof(b) = %zu\n", offsetof(PackedStruct, b));
  printf("  offsetof(c) = %zu\n", offsetof(PackedStruct, c));
  printf("  offsetof(d) = %zu\n\n", offsetof(PackedStruct, d));

  printf("Memory saved: %zu bytes\n",
         sizeof(UnoptimizedStruct) - sizeof(OptimizedStruct));

  return 0;
}
