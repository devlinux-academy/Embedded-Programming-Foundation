#include <stdio.h>

#define ITERATIONS 1000

void test_with_buffer(void) {
  setvbuf(stdout, NULL, _IOFBF, 8192);

  for (int i = 0; i < ITERATIONS; i++) {
    printf("Buffered output line %d\n", i);
  }

  fflush(stdout);
}

void test_without_buffer(void) {
  setvbuf(stdout, NULL, _IONBF, 0);

  for (int i = 0; i < ITERATIONS; i++) {
    printf("Unbuffered output line %d\n", i);
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s [buffered|unbuffered]\n", argv[0]);
    return 1;
  }

  if (argv[1][0] == 'b') {
    test_with_buffer();
  } else if (argv[1][0] == 'u') {
    test_without_buffer();
  } else {
    fprintf(stderr, "Invalid option. Use 'buffered' or 'unbuffered'\n");
    return 1;
  }

  return 0;
}
