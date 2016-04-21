
/* EAR(1) time-series generator */

#include "random_generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SEQUENCE_SIZE 1000
#define SEED_TABLE_SIZE 10000
#define VALUE_SIZE 20

int main(void) {
  long seed_table[SEED_TABLE_SIZE];
  long seed_array[4];
  int i;
  double avg_rate = 10;
  double corr = 0.5;
  double test_avg_rate;
  double test_corr;
  double x[SEQUENCE_SIZE];
  double *y[2];

  read_seed_table(seed_table, SEED_TABLE_SIZE, "../data/seed_table_size_10000_interval_100000_seed_1.txt");
  seed_array[0] = seed_table[10];
  seed_array[1] = seed_table[30];
  seed_array[2] = seed_table[50];
  seed_array[3] = seed_table[70];

  printf("avg_rate:%f\ncorr:%f\n", avg_rate, corr);
  x[0] = exponential_random_generator(avg_rate, &seed_array[0]);
  for (i = 1; i < SEQUENCE_SIZE; i++) {
    x[i] = time_series_ear_random_generator(x[i-1], corr, avg_rate, &seed_array[1], &seed_array[2]);
  }

  for (i = 0; i < SEQUENCE_SIZE; i++) {
    printf("x[%2d]:%12f\n", i, x[i]);
  }

  test_avg_rate = 1 / avg_sequence(x, SEQUENCE_SIZE);

  y[0] = &x[0];
  y[1] = &x[1];

  test_corr = corr_sequence(y, SEQUENCE_SIZE-1);
  printf("test_avg_rate:%f\ntest_corr:%f\n", test_avg_rate, test_corr);

  return 0;
}
