
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

double random_generator(long *next_seed) {
  double r;
  r = (double) (*next_seed) / MOD_OPERAND_1;
  *next_seed = ibm_random_generator(*next_seed);
  return r;
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

double chi_square_compute(double *sequence, long sequence_size, long interval_size) {
  double chi_square = 0.0;
  double *o;
  double *e;
  int i;
  int j;
  o = malloc(interval_size * sizeof(double));
  e = malloc(interval_size * sizeof(double));

  for (i = 0; i < interval_size; i++) {
    e[i] = (double) sequence_size / interval_size;
    o[i] = 0.0;
  }

  qsort(sequence, sequence_size, sizeof(double), compare_double);

  j = 0;
  for (i = 0; i < interval_size; i++) {
    while (j < sequence_size && sequence[j] <= ((double) 1.0 * (i + 1) / interval_size)) {
      o[i]++;
      j++;
    }
  }

  for (i = 0; i < interval_size; i++) {
    chi_square += ((o[i] - e[i]) * (o[i] - e[i]) / e[i]);
  }

  for (i = 0; i < interval_size; i++) {
    printf("O[%d]: %.0f\n", i+1, o[i]);
  }

  free(o);
  free(e);
  o = NULL;
  e = NULL;

  return chi_square;
}

double autocorrelation_compute(double *sequence, long sequence_size, long start, long interval) {
  long m = 0;
  double sum_rr = 0.0; /* sigma_{k=0}^M R_(i+kl)R_(i+(k+1)l) */
  double rho;
  double sigma;
  double z0;
  long prev = start;
  long next = start + interval;
  while (next < sequence_size) {
    m++;
    sum_rr += (sequence[prev] * sequence[next]);
    prev = next;
    next = next + interval;
  }
  m--;
  rho = sum_rr / (m + 1) - 0.25;
  sigma = sqrt(13.0 * m + 7) / (12 * (m + 1));
  z0 = rho / sigma;
  printf("M: %lu\n", m);
  printf("rho: %f\n", rho);
  printf("sigma: %f\n", sigma);
  return z0;
}

double exponential_inverse_transform(double average_rate, double probability) {
  double x, r, lambda;
  r = probability;
  lambda = average_rate;
  x = -1 * log(1-r) / lambda;
  return x;
}

double exponential_random_generator(double average_rate, long *seed) {
  long next_seed = ibm_random_generator(*seed);
  double probability = (double) next_seed / MOD_OPERAND_1;
  double random_number = exponential_inverse_transform(average_rate, probability);
  *seed = next_seed;
  return random_number;
}

double empirical_inverse_transform(double *x, double *r, long size, double probability) {
  int i;
  double result;
  for (i = 0; i < size && probability >= r[i]; i++) {
    /* empty */
  }
  i--;
  result = x[i] + (x[i+1] - x[i]) / (r[i+1] - r[i]) * (probability - r[i]); 
  return result;
}

double empirical_discrete_inverse_transform(double r[], long size, double probability) {
  long i;
  for (i = 0; i < size && probability >= r[i]; i++) {
    /* empty */
  }
  i--;
  return (double) i; 
}

/* r is random variable, 0<= r < 1. p is given probability between 0 and 1 */
double empirical_geometric_inverse_transform(double r, double p) {
  double x;
  x = ceil(log(1-r) / log(1-p) - 1);
  return x;
}

double poisson_inverse_transform(double alpha, long *next_seed) {
  double n;
  long i = 0;
  double product_r = 1.0;
  double probability = (double) (*next_seed) / MOD_OPERAND_1; 
  double e_minus_alpha = exp(-1*alpha);
  for (i = 0; e_minus_alpha <= product_r; i++) {
    product_r = product_r * probability;
    *next_seed = ibm_random_generator(*next_seed);
    probability = (double) (*next_seed)/ MOD_OPERAND_1;
  }
  n = i - 1;
  return n;
}

double nonstationary_poisson_process_random_generator(struct arrival_rate_table *arrival_rate_table, long *next_seed1, long *next_seed2) {
  double r1, r2;
  double arrival_time;
  double inter_arrival_time;
  double ratio_arrival_rate;
  long i;
  arrival_time = 0.0;
  do {
    printf("arrival time:%g\n", arrival_time);
    printf("next_seed1: %ld\n", *next_seed1);
    r1 = random_generator(next_seed1);
    printf("next_seed1: %ld\n", *next_seed1);
    printf("r1: %g\n", r1);
    inter_arrival_time = exponential_inverse_transform(arrival_rate_table->max_arrival_rate, r1);
    printf("inter_arrival_time: %g\n", inter_arrival_time);
    arrival_time = arrival_time + inter_arrival_time;
    for (i = 0; i < arrival_rate_table->size; i++) {
      if (arrival_time < arrival_rate_table->time[i]) {
        break;
      }
    }
    i--;
    ratio_arrival_rate = arrival_rate_table->arrival_rate[i] / arrival_rate_table->max_arrival_rate;
    printf("ratio: %g\n", ratio_arrival_rate);
    r2 = random_generator(next_seed2);
    printf("r2: %g\n", r2);
  } while (r2 > ratio_arrival_rate);
  return arrival_time;
}


double normal_cos_random_generator(long *next_seed1, long *next_seed2) {
  double r1, r2;
  double z;
  r1 = random_generator(next_seed1);
  r2 = random_generator(next_seed2);
  z = sqrt(-2 * log(r1)) * cos(2 * PI * r2);
  return z;
}

double normal_sin_random_generator(long *next_seed1, long *next_seed2) {
  double r1, r2;
  double z;
  r1 = random_generator(next_seed1);
  r2 = random_generator(next_seed2);
  z = sqrt(-2 * log(r1)) * sin(2 * PI * r2);
  return z;
}

/*
 @k: number of random variables
 @theta: average_rate
 @next_seed_array: an array of k seeds
*/
double erlang_random_generator(long k, double theta, long *next_seed_array) {
  double r = 1.0;
  double x;
  long i;
  for (i = 0; i < k; i++) {
    r = r * random_generator(&next_seed_array[i]);
  }
  x = -1.0 * log(r) / k / theta;
  return x;
}

double approximation_inverse_cdf_normal_distribution(double r) {
  double s = pow(r, 0.135);
  double t = pow(1-r, 0.135);
  double x = (s - t) / 0.1975;
  return x;
}

void bivariate_normal_random_generator(double x[2], double avg[2], double dev[2], double correlation, long *next_seed1, long *next_seed2) {
  long another_seed1 = *next_seed1;
  long another_seed2 = *next_seed2;
  double z[2];
  int i;
  z[0] = normal_cos_random_generator(next_seed1, next_seed2);
  z[1] = normal_sin_random_generator(&another_seed1, &another_seed2);
  x[0] = avg[0] + dev[0] * z[0];
  x[1] = avg[1] + dev[0] * (correlation * z[0] + sqrt(1-correlation*correlation) * z[1]);
}

double avg_sequence(double *seq, long size) {
  long i;
  double sum = 0.0;
  double avg;
  for (i = 0; i < size; i++) {
    sum += seq[i];
  }
  avg = sum / size;
}

double dev_sequence(double *seq, long size) {
  long i;
  double avg = avg_sequence(seq, size);
  double sum = 0.0;
  double dev;
  for (i = 0; i < size; i++) {
    sum += ((seq[i] - avg) * (seq[i] - avg));
  }
  dev = sqrt(sum / (size - 1));
  return dev;
}

double corr_sequence(double *seq[2], long size) {
  double avg[2];
  double dev[2];
  double corr;
  double sum = 0.0;
  long i;
  for (i = 0; i < 2; i++) {
    avg[i] = avg_sequence(seq[i], size);
    dev[i] = dev_sequence(seq[i], size);
  }
  for (i = 0; i < size; i++) {
    sum += (seq[0][i] * seq[1][i]);
  }
  sum -= (size * avg[0] * avg[1]);
  corr = sum / (size - 1) / (dev[0]*dev[1]);
  return corr; 
}

double normal_random_generator(double avg, double dev, long *next_seed1, long *next_seed2) {
  double number_N_0_1;
  double number_N_avg_dev2;
  number_N_0_1 = normal_cos_random_generator(next_seed1, next_seed2);
  number_N_avg_dev2 = number_N_0_1 * dev + avg;
  return number_N_avg_dev2;
}

double corr_t_t_1(double cov_t_t_1, double dev) {
  double corr;
  corr = cov_t_t_1 / (dev*dev);
  return corr;
}

double dev_epsilen(double corr, double dev) {
  double dev_e;
  dev_e = sqrt(dev*dev*(1-corr*corr));
  return dev_e;
}

double time_series_random_generator(double x_t_1, double x_avg, double x_t_t_1_corr, double dev_epsilen) {
  double x_t;
  x_t = x_avg + x_t_t_1_corr * (x_t_1 - x_avg) + dev_epsilen;
  return x_t;
}
