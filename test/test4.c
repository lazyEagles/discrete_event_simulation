
#include <random_generator.h>
#include <stdio.h>

#define SEQUENCE_SIZE 10000
#define SEED_TABLE_SIZE 10000
int main(void) {
  long seed_table[SEED_TABLE_SIZE];
  long next_seed_1;
  long next_seed_2;
  double random_time_1;
  double random_time_2;
  double average_rate_1 = 0.1;
  double average_rate_2 = 0.2;
  int i;

  read_seed_table(seed_table, SEED_TABLE_SIZE, "../data/seed_table_size_10000_interval_100000_seed_1.txt");
  next_seed_1 = seed_table[10];
  next_seed_2 = seed_table[30];

  for (i = 0; i < 20; i++) {
    random_time_1 = exponential_random_generator(average_rate_1, &next_seed_1);
    random_time_2 = exponential_random_generator(average_rate_2, &next_seed_2);
  
    printf("random_time_1: %f\n", random_time_1);
    printf("random_time_2: %f\n", random_time_2);
  }
  
  return 0;
}
