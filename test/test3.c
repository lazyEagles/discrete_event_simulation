
#include <random_generator.h>
#include <stdio.h>

#define SEQUENCE_SIZE 10000
int main(void) {
/*
  print_ibm_random_generator_seed(10, 100000, 1); 
*/
  double sequence[SEQUENCE_SIZE];
  double d;
  random_sequence_generator(sequence, SEQUENCE_SIZE, 1, "../data/seed_table_size_10000_interval_100000_seed_1.txt");
  int i;
/*
  for (i = 0; i < 100; i++) {
    printf("%g\n", sequence[i]);
  }
*/
  double z0 = autocorrelation_compute(sequence, SEQUENCE_SIZE, 10, 100);
/*
  printf("=============\n");
  for (i = 0; i < 100; i++) {
    printf("%d: %g\n", i, sequence[i]);
  }
*/
  printf("z0: %12f\n", z0);
  
  return 0;
}
