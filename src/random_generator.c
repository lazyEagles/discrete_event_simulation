
#include <random_generator.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Kolmogorov-Smirnov Critical Values */
static double kol_smi_critical_value[35][3] = {
/*  0.10   0.05   0.01 */
  {0.950, 0.975, 0.995}, 
  {0.776, 0.842, 0.929},
  {0.642, 0.708, 0.828},
  {0.564, 0.624, 0.733},
  {0.510, 0.565, 0.669}, /* 5 */
  {0.470, 0.521, 0.618},
  {0.438, 0.486, 0.577},
  {0.411, 0.457, 0.543},
  {0.388, 0.432, 0.514},
  {0.368, 0.410, 0.490}, /* 10 */
  {0.352, 0.391, 0.468},
  {0.338, 0.375, 0.450},
  {0.325, 0.361, 0.433},
  {0.314, 0.349, 0.418},
  {0.304, 0.338, 0.404}, /* 15 */
  {0.295, 0.328, 0.392},
  {0.286, 0.318, 0.381},
  {0.278, 0.309, 0.371},
  {0.272, 0.301, 0.363},
  {0.264, 0.294, 0.356}, /* 20 */
  {0.240, 0.270, 0.320}, /* 25 */
  {0.220, 0.240, 0.290}, /* 30 */
  {0.210, 0.230, 0.270}  /* 35 */
/* 1.22/sqrt(n), 1.36/sqrt(n), 1.63/sqrt(n) */
};

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

double kol_smi_compute_d(double *sequence, long sequence_size) {
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

int kol_smi_test(long sequence_size, double probability_reject, double d) {
  if (sequence_size <= 0) {
    exit(1);
  }
  int probability_level;
  double constant[3] = {1.22, 1.36, 1.63};

  if (probability_reject >= 0.1) {
    probability_level = 0;
  } else if (probability_reject >= 0.05) {
    probability_level = 1;
  } else if (probability_reject >= 0.01) {
    probability_level = 2;
  } else {
    exit(1);
  }
  if (sequence_size > 35) {
    return (d < (constant[probability_level]/sqrt((double) sequence_size))) ? 1 : 0;
  }
  if (sequence_size > 30) {
    return (d < kol_smi_critical_value[22][probability_level]) ? 1 : 0;
  }
  if (sequence_size > 25) {
    return (d < kol_smi_critical_value[21][probability_level]) ? 1 : 0;
  }
  if (sequence_size > 20) {
    return (d < kol_smi_critical_value[20][probability_level]) ? 1 : 0;
  }
  return (d < kol_smi_critical_value[sequence_size-1][probability_level]) ? 1 : 0;
}
