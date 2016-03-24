
#include "random_generator.h"
#include <stdio.h>

#define SEQUENCE_SIZE 10000
#define SEED_TABLE_SIZE 10000
int main(void) {
  double x[5] = {0.25, 0.5, 1.0, 1.5, 2.0};
  double r[5] = {0.0, 0.31, 0.41, 0.66, 1.0};
  double probability; 
  long next_seed = 2;
  double result;
  int i;
  for (i = 0; i < 10; i++) {
    probability = (double) next_seed / MOD_OPERAND_1;
    result = empirical_inverse_transform(x, r, 5, probability);
    next_seed = ibm_random_generator(next_seed);
    printf("probability: %g, result: %g\n", probability, result); 
  }
  probability = 0.83;
  result = empirical_inverse_transform(x, r, 5, probability);
  printf("probability: %g, result: %g\n", probability, result); 
  return 0;
}
