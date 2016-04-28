
/* mm1 queue */

#include "mm_one_queue.h"
#include "random_generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_cdf.h>

#define SEQUENCE_SIZE 1000
#define SEED_TABLE_SIZE 10000
#define VALUE_SIZE 20
#define MAX_ROUND 1000

int main(void) {
  long seed_table[SEED_TABLE_SIZE];
  long seed_array[4];
  long nr_customer = 1000;
  double avg_interarrival_time = 10.0;
  double avg_service_time = 5.0;
  struct mm_one_simulation_result result;
  double half_alpha = 0.01;
  double eps_relative = 0.05;
  double t;
  double h;
  double dev;
  double s;
  double ci_bound;
  double each_round_customer_in_system_time[MAX_ROUND];
  double avg_customer_in_system_time = 0.0;

  int i;
  long round = 0;

  read_seed_table(seed_table, SEED_TABLE_SIZE, "../data/seed_table_size_10000_interval_100000_seed_1.txt");
  seed_array[0] = seed_table[10];
  seed_array[1] = seed_table[30];
  seed_array[2] = seed_table[50];
  seed_array[3] = seed_table[70];

  for (round = 0; round < 2; round++) {
    mm_one_queue_simulator(nr_customer, avg_interarrival_time, avg_service_time, &seed_array[0], &seed_array[1], &result);
    each_round_customer_in_system_time[round] = result.average_customer_in_system_time;
  }
  t = gsl_cdf_tdist_Pinv(1.0-half_alpha,round - 1);
  avg_customer_in_system_time = avg_sequence(each_round_customer_in_system_time, round);
  dev = dev_sequence(each_round_customer_in_system_time, round);
  s = dev * dev;
  h = t * s / sqrt((double) round);
  ci_bound = avg_customer_in_system_time * eps_relative;
  printf("t:%f\n", t);
  printf("h:%f\n", h);
  printf("ci_bound:%f\n", ci_bound);

  while (h >= ci_bound) {
    mm_one_queue_simulator(nr_customer, avg_interarrival_time, avg_service_time, &seed_array[0], &seed_array[1], &result);
    each_round_customer_in_system_time[round] = result.average_customer_in_system_time;
    round++;

    t = gsl_cdf_tdist_Pinv(1.0-half_alpha,round - 1);
    avg_customer_in_system_time = avg_sequence(each_round_customer_in_system_time, round);
    dev = dev_sequence(each_round_customer_in_system_time, round);
    s = dev * dev;
    h = t * s / sqrt((double) round);
    ci_bound = avg_customer_in_system_time * eps_relative;
    printf("round:%ld\n", round);
    printf("avg_time:%f\n", avg_customer_in_system_time);
    printf("t:%f\n", t);
    printf("h:%f\n", h);
    printf("ci_bound:%f\n", ci_bound);
  }
  return 0;
}
