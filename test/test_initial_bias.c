
/* mm1 queue */

#include "mm_one_queue.h"
#include "random_generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_cdf.h>

#define SEED_TABLE_SIZE 10000
#define MAX_ROUND 1000

int main(void) {
  long seed_table[SEED_TABLE_SIZE];
  long seed_array[4];
  long nr_customer = 10000;
  double avg_interarrival_time = 10.0;
  double avg_service_time = 9.0;
  struct mm_one_simulation_result *result;
  double half_alpha = 0.01;
  double eps_relative = 0.05;
  double t;
  double ci_half_width;
  double dev;
  double ci_half_bound;
  double each_round_customer_in_system_time[MAX_ROUND];
  double avg_customer_in_system_time = 0.0;

  int i, j;
  long round = 0;
  long nr_round = 100;

  /*
        y11 y12 y13 ... y1,nr_round
        y21 y22 y23 ... y2,nr_round
        ...
        y1000,1 y1000,2 ... y1000,nr_round
  */
  double **customer_round_time;
  double *avg_customer_time;
  double *ci_hw_customer;

  double *smooth_avg_m5_avg_customer_time;
  double nr_smooth_customer = nr_customer - 11 + 1;

  customer_round_time = malloc(nr_customer * sizeof(double *));
  for (i = 0; i < nr_customer; i++) {
    customer_round_time[i] = malloc(nr_round * sizeof(double));
  }

  avg_customer_time = malloc(nr_customer * sizeof(double));
  ci_hw_customer = malloc(nr_customer * sizeof(double));

  smooth_avg_m5_avg_customer_time = malloc(nr_smooth_customer * sizeof(double));

  read_seed_table(seed_table, SEED_TABLE_SIZE, "../data/seed_table_size_10000_interval_100000_seed_1.txt");
  seed_array[0] = seed_table[10];
  seed_array[1] = seed_table[30];
  seed_array[2] = seed_table[50];
  seed_array[3] = seed_table[70];

  result = malloc(nr_round * sizeof(struct mm_one_simulation_result));

  for (i = 0; i < nr_round; i++) {
    init_mm_one_simulation_result(&result[i], nr_customer);
    mm_one_queue_simulator(nr_customer, avg_interarrival_time, avg_service_time, &seed_array[0], &seed_array[1], &result[i]);
  }

  for (i = 0; i < nr_round; i++) {
    for (j = 0; j < nr_customer; j++) {
      customer_round_time[j][i] = result[i].customer_in_system_time[j];
    }
  }

  t = gsl_cdf_tdist_Pinv(1.0-half_alpha,nr_round - 1);

  for (i = 0; i < nr_customer; i++) {
    avg_customer_time[i] = avg_sequence(customer_round_time[i], nr_round);
    dev = dev_sequence(customer_round_time[i], nr_round);
    ci_hw_customer[i] = t * dev / nr_round;
  }

  for (i = 0; i < nr_smooth_customer; i++) {
    smooth_avg_m5_avg_customer_time[i] = avg_sequence(&avg_customer_time[i], 11);
  }

  for (i = 0; i < nr_customer; i++) {
    printf("%f %f\n", avg_customer_time[i], ci_hw_customer[i]);
  }

  for (i = 0; i < nr_smooth_customer; i++) {
    printf("%f\n", smooth_avg_m5_avg_customer_time[i]);
  }

  /* free */
  for (i = 0; i < nr_customer; i++) {
    free_array_in_mm_one_simulation_result(&result[i]);
  }

  free(result);
  result = NULL;

  for (i = 0; i < nr_customer; i++) {
    free(customer_round_time[i]);
    customer_round_time[i] = NULL;
  }

  free(customer_round_time);
  customer_round_time = NULL;

  free(avg_customer_time);
  avg_customer_time = NULL;

  free(smooth_avg_m5_avg_customer_time);
  smooth_avg_m5_avg_customer_time = NULL;

  return 0;
}
