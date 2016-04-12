
#include "random_generator.h"
#include <stdio.h>

#define SEQUENCE_SIZE 10000
#define SEED_TABLE_SIZE 10000

int main(void) {
  long seed_table[SEED_TABLE_SIZE];
  long seed_array[2];
  double x;
  int i;

  read_seed_table(seed_table, SEED_TABLE_SIZE, "../data/seed_table_size_10000_interval_100000_seed_1.txt");
  seed_array[0] = seed_table[10];
  seed_array[1] = seed_table[30];

  x = erlang_random_generator(2, 0.5, seed_array);
  printf("x: %10g\n", x );
  return 0;
}
