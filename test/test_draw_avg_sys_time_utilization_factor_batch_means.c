
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
  long nr_customer = 10000000;
  double avg_interarrival_time = 10.0;
  double avg_service_time = 5.0;
  double half_alpha = 0.01;
  double eps_relative = 0.05;
  double t;
  double ci_half_width;
  double dev;
  double ci_half_bound;
  double each_round_customer_in_system_time[MAX_ROUND];
  double avg_customer_in_system_time = 0.0;

  double utilization_factor; /* utilization factor = avg_service_time / avg_interarrival_time */

  struct sample_input in_data;
  struct sample_output out_data;

  struct batch_means_output result;

  int i;
  long round = 0;

  long next_seed_interarrival, next_seed_service;
  long nr_batch = 10;
  long batch_size = 64;
  long initial_bias = 500;
  double correlation_bound = 0.3;

  read_seed_table(seed_table, SEED_TABLE_SIZE, "../data/seed_table_size_10000_interval_100000_seed_1.txt");
  seed_array[0] = seed_table[10];
  seed_array[1] = seed_table[210];

  for (i = 1; i <= 9; i++) {
    result.avg = 0.0;
    result.ci_hw = 0.0;
    result.lag_1 = 0.0;
    avg_interarrival_time = 5.0 / 0.1 / i;
    avg_service_time = 5.0;
    next_seed_interarrival = seed_array[0];
    next_seed_service = seed_array[1];
    mm_one_queue_simulator_for_batch_means(nr_customer, avg_interarrival_time, avg_service_time, &next_seed_interarrival, &next_seed_service, nr_batch, batch_size, initial_bias, correlation_bound, half_alpha, eps_relative, &result); 

    utilization_factor = avg_service_time / avg_interarrival_time;

    /* utilization, sample_avg, sample_ci_hw, round */
    printf("%f %f %f %f\n", utilization_factor, result.avg, result.ci_hw, result.lag_1);
  }

  return 0;
}
