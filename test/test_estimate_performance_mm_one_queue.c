
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
  long seed_array[2];
  long nr_customer = 1000;
  double avg_interarrival_time = 10.0;
  double avg_service_time = 5.0;
  struct mm_one_simulation_result result;
  double half_alpha = 0.01;
  double eps_relative = 0.05;
  double t;
  double ci_half_width;
  double dev;
  double ci_half_bound;
  double each_round_customer_in_system_time[MAX_ROUND];
  double avg_customer_in_system_time = 0.0;

  struct sample_input in_data;
  struct sample_output out_data;

  int i;
  long round = 0;

  read_seed_table(seed_table, SEED_TABLE_SIZE, "../data/seed_table_size_10000_interval_100000_seed_1.txt");
  seed_array[0] = seed_table[10];
  seed_array[1] = seed_table[30];

  in_data.avg_interarrival_time = 10.0;
  in_data.avg_service_time = 5.0;
  in_data.nr_customer = 1000;
  in_data.half_alpha = 0.01;
  in_data.eps_relative = 0.05;

  estimate_performance_of_mm_one_queue_simulator(&out_data, &in_data, seed_array[0], seed_array[1]);

  printf("sample_avg: %12f\nsample_dev: %12f\nsample_ci_hw: %12f\nround: %ld\n", out_data.sample_avg, out_data.sample_dev, out_data.sample_ci_hw, out_data.round);

  return 0;
}
