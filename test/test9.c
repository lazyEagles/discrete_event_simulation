
#include "random_generator.h"
#include <stdio.h>

#define SEQUENCE_SIZE 10000
#define SEED_TABLE_SIZE 10000

int main(void) {
  long seed_table[SEED_TABLE_SIZE];
  long next_seed_1;
  long next_seed_2;
  long next_seed_3;
  long next_seed_4;
  int i;

  read_seed_table(seed_table, SEED_TABLE_SIZE, "../data/seed_table_size_10000_interval_100000_seed_1.txt");
  next_seed_1 = seed_table[10];
  next_seed_2 = seed_table[30];
  next_seed_3 = seed_table[10];
  next_seed_4 = seed_table[30];

  printf("seed1: %ld, seed2: %ld\n", next_seed_1, next_seed_2);

  double zx, zy;
  for (i = 0; i < 10; i++) {
    zx = normal_cos_random_generator(&next_seed_1, &next_seed_2);
    zy = normal_sin_random_generator(&next_seed_3, &next_seed_4);
    printf("zx: %10g, zy: %10g\n", zx, zy );
  }
  return 0;
}
