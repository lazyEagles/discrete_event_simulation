
#include "random_generator.h"
#include <stdio.h>

#define SEQUENCE_SIZE 10000
#define SEED_TABLE_SIZE 10000
int main(void) {
  double n;
  double alpha = 10; /* arrival rate */
  long next_seed = 100;
  int i, j;
  for (i = 0; i < 10; i++) {
    printf("arrival rate: %4g, n:", alpha);
    for (j = 0; j < 10; j++) {
      n = poisson_inverse_transform(alpha, &next_seed);
      printf("%4g", n); 
    }
    printf("\n");
    alpha += 10;
  }
  return 0;
}
