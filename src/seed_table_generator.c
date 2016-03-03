
#include <random_generator.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Usage: ./seed_table_generator size interval seed\n");
    return 0;
  }
  long size = atol(argv[1]);
  long interval = atol(argv[2]);
  long seed = atol(argv[3]);
  if (size == 0 || interval == 0 || seed == 0) {
    printf("Error: size, interval, or seed can't be 0.\n");
    return 0;
  }
  print_ibm_random_generator_seed(size, interval, seed);
  return 0;
}
