
/* Quantile-Quantile Plots */

#include "random_generator.h"
#include <stdio.h>
#include <stdlib.h>

#define SEQUENCE_SIZE 10000
#define SEED_TABLE_SIZE 10000
#define VALUE_SIZE 20

int main(void) {
  long seed_table[SEED_TABLE_SIZE];
  long seed_array[2];
  double x;
  int i;
  double value[VALUE_SIZE];
  double y[VALUE_SIZE];

  read_seed_table(seed_table, SEED_TABLE_SIZE, "../data/seed_table_size_10000_interval_100000_seed_1.txt");
  seed_array[0] = seed_table[10];
  seed_array[1] = seed_table[30];

  for (i = 0; i < VALUE_SIZE; i++) {
    value[i] = normal_cos_random_generator(&seed_array[0], &seed_array[1]);
  }
  qsort(value, VALUE_SIZE, sizeof(double), compare_double);

  for (i = 0; i < VALUE_SIZE; i++) {
    y[i] = approximation_inverse_cdf_normal_distribution(((double)i+1.0-0.5)/VALUE_SIZE);
  }

  printf("value, y\n");
  for (i = 0; i < VALUE_SIZE; i++) {
    printf("%f, %f\n", value[i], y[i]);
  }

  return 0;
}
