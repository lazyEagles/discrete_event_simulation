
#include <random_generator.h>
#include <stdio.h>

int main(void) {
/*
  print_ibm_random_generator_seed(10, 100000, 1); 
*/
  double sequence[40];
  double d;
  random_sequence_generator(sequence, 40, 0, "../seed_table.txt");
  int i;
  for (i = 0; i < 40; i++) {
    printf("%g\n", sequence[i]);
  }
  printf("======================\n");
  d = kolmogorov_smirnov_test(sequence, 40);
  printf("D: %f\n", d);
  
  return 0;
}
