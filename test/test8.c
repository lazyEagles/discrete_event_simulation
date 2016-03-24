
#include "random_generator.h"
#include <stdio.h>

#define SEQUENCE_SIZE 10000
#define SEED_TABLE_SIZE 10000

int main(void) {
  struct arrival_rate_table arrival_rate_table = {
    .time = {0 ,60, 120, 180, 240, 300, 360, 420, 480},
    .mean_time_between_arrivals = {15, 12, 7, 5, 8, 10, 15, 20, 20},
    .arrival_rate = {0.0667, 0.0833, 0.1429, 0.2, 0.125, 0.1, 0.0667, 0.05, 0.05},
    .size = 9,
    .max_arrival_rate = 0.2
  };
  long next_seed_1 = 100;
  long next_seed_2 = 200;
  double arrival_time = nonstationary_poisson_process_random_generator(&arrival_rate_table, &next_seed_1, &next_seed_2);
  printf("arrival time: %4g\n", arrival_time );
  return 0;
}
