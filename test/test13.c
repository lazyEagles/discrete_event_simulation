
/* Quantile-Quantile Plots */

#include "random_generator.h"
#include <stdio.h>
#include <stdlib.h>

#define SEQUENCE_SIZE 10000
#define SEED_TABLE_SIZE 10000
#define VALUE_SIZE 20

int main(void) {
  long seed_table[SEED_TABLE_SIZE];
  long seed_array[4];
  int i;
  double value[2][VALUE_SIZE];
  double y[VALUE_SIZE];
  double avg[2];
  double dev[2];
  double *seq[2];
  double corr;
  double x[2];

  read_seed_table(seed_table, SEED_TABLE_SIZE, "../data/seed_table_size_10000_interval_100000_seed_1.txt");
  seed_array[0] = seed_table[10];
  seed_array[1] = seed_table[30];
  seed_array[2] = seed_table[50];
  seed_array[3] = seed_table[70];

  value[0][0] = normal_cos_random_generator(&seed_array[0], &seed_array[1]);
  for (i = 1; i < VALUE_SIZE; i++) {
    value[0][i] = normal_cos_random_generator(&seed_array[0], &seed_array[1]);
    value[1][i - 1] = value[0][i];
  }
  value[1][VALUE_SIZE-1] = normal_cos_random_generator(&seed_array[0], &seed_array[1]);

  for (i = 0; i < 2; i++) {
    avg[i] = avg_sequence(value[i], VALUE_SIZE);
    dev[i] = dev_sequence(value[i], VALUE_SIZE);
  }
  seq[0] = &value[0][0];
  seq[1] = &value[1][0];
  corr = corr_sequence(seq, VALUE_SIZE);
  printf("X1 sequence: ");
  for (i = 0; i < VALUE_SIZE; i++) {
    printf("%f ", value[0][i]);
  }
  printf("\n");
  printf("X2 sequence: ");
  for (i = 0; i < VALUE_SIZE; i++) {
    printf("%f ", value[1][i]);
  }
  printf("\n");
  printf("avg1: %f, dev1: %f\n", avg[0], dev[0]);
  printf("avg2: %f, dev2: %f\n", avg[1], dev[1]);
  printf("corr: %f\n", corr);
  bivariate_normal_random_generator(x, avg, dev, corr, &seed_array[2], &seed_array[3]);

  printf("X1:%f, X2:%f\n", x[0], x[1]);

  return 0;
}
