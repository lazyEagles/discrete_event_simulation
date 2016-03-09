
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
  double chi_square = chi_square_compute(sequence, SEQUENCE_SIZE, 10);
/*
  printf("=============\n");
  for (i = 0; i < 100; i++) {
    printf("%d: %g\n", i, sequence[i]);
  }
*/
  printf("chi_square: %12f\n", chi_square);
  
  return 0;
}
