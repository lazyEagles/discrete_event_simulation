
#include <random_generator.h>
#include <stdio.h>

int main(void) {
/*
  print_ibm_random_generator_seed(10, 100000, 1); 
*/
  double sequence[40];
  double d;
  random_sequence_generator(sequence, 40, 0, "../data/seed_table_size_10000_interval_100000_seed_1.txt");
  int i;
  for (i = 0; i < 40; i++) {
    printf("%g\n", sequence[i]);
  }
  printf("======================\n");
  d = kol_smi_compute_d(sequence, 40);
  printf("D: %f\n", d);
  int pass = kol_smi_test(40, 0.01, d);
  if (pass) {
    printf("%f: pass\n", 0.01);
  } else {
    printf("%f: fail\n", 0.01);
  }
  
  return 0;
}
