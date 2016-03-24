
#include "random_generator.h"
#include <stdio.h>

#define SEQUENCE_SIZE 10000
#define SEED_TABLE_SIZE 10000
int main(void) {
  double r[4] = {0.0, 0.5, 0.8, 1.0};
  double probability; 
  long next_seed = 100;
  double result1, result2;
  int i;
  for (i = 0; i < 10; i++) {
    probability = (double) next_seed / MOD_OPERAND_1;
    result1 = empirical_discrete_inverse_transform(r, 4, probability);
    result2 = empirical_geometric_inverse_transform(probability, 0.4);
    next_seed = ibm_random_generator(next_seed);
    printf("probability: %11g, result1: %g, result2: %ld\n", probability, result1, (long) result2); 
  }
/*
  probability = 0.83;
  result = empirical_inverse_transform(x, r, 5, probability);
  printf("probability: %g, result: %g\n", probability, result); 
*/
  return 0;
}
