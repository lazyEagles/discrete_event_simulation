
/* time-series generator */

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
  double avg = 10;
  double dev = 2;
  double cov = 0.9;
  double corr;
  double dev_for_x1;
  double dev_eps;
  double epsilen[SEQUENCE_SIZE];
  double x[SEQUENCE_SIZE];
  double test_avg;
  double test_dev;
  double test_corr;
  double *y[2];

  read_seed_table(seed_table, SEED_TABLE_SIZE, "../data/seed_table_size_10000_interval_100000_seed_1.txt");
  seed_array[0] = seed_table[10];
  seed_array[1] = seed_table[30];
  seed_array[2] = seed_table[50];
  seed_array[3] = seed_table[70];

  corr = corr_t_t_1(cov, dev);
  dev_eps = dev_epsilen(corr, dev);
  dev_for_x1 = sqrt(dev_eps*dev_eps/(1-corr*corr));
  printf("avg:%f\ndev:%f\ncov:%f\ncorr:%f\ndev_eps:%f\ndev_for_x1:%f\n", avg, dev, cov, corr, dev_eps, dev_for_x1);
  x[0] = normal_random_generator(avg, dev_for_x1, &seed_array[0], &seed_array[1]);
  for (i = 1; i < SEQUENCE_SIZE; i++) {
    epsilen[i] = normal_random_generator(0, dev_eps, &seed_array[2], &seed_array[3]);
    x[i] = time_series_random_generator(x[i-1], avg, corr, epsilen[i]);
  }

  for (i = 0; i < SEQUENCE_SIZE; i++) {
    printf("x[%2d]:%12f, epsilen[%2d]:%12f\n", i, x[i], i, epsilen[i]);
  }

  test_avg = avg_sequence(x, SEQUENCE_SIZE);
  test_dev = dev_sequence(x, SEQUENCE_SIZE);

  y[0] = &x[0];
  y[1] = &x[1];

  test_corr = corr_sequence(y, SEQUENCE_SIZE-1);
  printf("test_avg:%f\ntest_dev:%f\ntest_corr:%f\n", test_avg, test_dev, test_corr);

  return 0;
}
