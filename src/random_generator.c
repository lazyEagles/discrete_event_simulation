
#include <random_generator.h>
#include <stdio.h>
#include <stdlib.h>

long ibm_random_generator(long seed) {
  long mod_operand = (1L << 31) - 1;
  long mul_operand = 7 * 7 * 7 * 7 * 7;
  long result = (mul_operand * seed) % mod_operand;

  return result;
}

/*

size: the number of seeds in the table
interval: the number of numbers in a stream

*/
void print_ibm_random_generator_seed(long size, long interval, long seed) {
  long count;
  long sub_count;
  long next_seed;
  long i;
  printf("%12ld ", seed);
  next_seed = seed;
  for (count = 1; count < size; count++) {
    for (sub_count = 0; sub_count < interval; sub_count++) {
      next_seed = ibm_random_generator(next_seed);
    }
    printf("%12ld", next_seed);
    if ((count % 5) == 4) {
      printf("\n");
    } else {
      printf(" ");
    }
  }
}

/*
sequence: random number sequence.
sequence_size: the number of random number sequence.
seed_no: 0~9999
*/
void random_sequence_generator(double *sequence, long sequence_size, long seed_no, char *seed_table) {
  static long seed[SEED_TABLE_SIZE];
  static int is_read = 0;
  if (!is_read) {
    read_seed_table(seed, SEED_TABLE_SIZE, seed_table);
    is_read = 1;
  }
  long i;
  long next_seed = seed[seed_no];
  sequence[0] = (double) next_seed / MOD_OPERAND_1;
  for (i = 1; i < sequence_size; i++) {
    next_seed = ibm_random_generator(next_seed);
    sequence[i] = (double) next_seed / MOD_OPERAND_1;
  }
}

void read_seed_table(long *seed, long size, char *seed_table) {
  FILE *fd = fopen(seed_table, "r");
  if (!fd) {
    fprintf(stderr, "Error: opening %s fails.\n", seed_table);
    exit(1);
  }

  long i;
  for (i = 0; i < size; i++) {
    fscanf(fd, "%ld", &seed[i]);
  }
}

double kolmogorov_smirnov_test(double *sequence, long sequence_size) {
  double max_d_plus = -1.0;
  double max_d_minus = -1.0;
  double one_over_n = 1.0 / sequence_size;
  double i_over_n = one_over_n;
  double i_minus_one_over_n = 0.0;
  int i;
  qsort(sequence, sequence_size, sizeof(double), compare_double);
  for (i = 0; i < sequence_size; i++) {
    if ((i_over_n - sequence[i]) > max_d_plus) {
      max_d_plus = i_over_n - sequence[i];
    }
    if ((sequence[i] - i_minus_one_over_n) > max_d_minus) {
      max_d_minus = sequence[i] - i_minus_one_over_n;
    }
    i_minus_one_over_n = i_over_n;
    i_over_n = i_over_n + one_over_n;
    printf("R[%d]: %g\n", i, sequence[i]);
  }
  printf("N: %ld\n", sequence_size);
  printf("D+: %f\n", max_d_plus);
  printf("D-: %f\n", max_d_minus);
  return (max_d_plus > max_d_minus) ? max_d_plus : max_d_minus;
}

int compare_double(const void *a, const void *b) {
  if (*(double *)a < *(double *)b) {
    return -1;
  } else if (*(double *)a == *(double *)b) {
    return 0;
  } else {
    return 1;
  }
}
