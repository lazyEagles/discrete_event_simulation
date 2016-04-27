
/* mm1 queue */

#include "mm_one_queue.h"
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
  long nr_customer = 1000;
  double avg_interarrival_time = 10.0;
  double avg_service_time = 5.0;
  struct mm_one_simulation_result result;

  int i;

  read_seed_table(seed_table, SEED_TABLE_SIZE, "../data/seed_table_size_10000_interval_100000_seed_1.txt");
  seed_array[0] = seed_table[10];
  seed_array[1] = seed_table[30];
  seed_array[2] = seed_table[50];
  seed_array[3] = seed_table[70];

  mm_one_queue_simulator(nr_customer, avg_interarrival_time, avg_service_time, &seed_array[0], &seed_array[1], &result);

  return 0;
}
