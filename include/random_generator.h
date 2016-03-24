
#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#define SEED_TABLE_SIZE 10000
#define MOD_OPERAND_1 ((1L << 31) - 1)
#define ARRIVAL_RATE_TABLE_SIZE 256

struct arrival_rate_table {
  double time[ARRIVAL_RATE_TABLE_SIZE];
  double mean_time_between_arrivals[ARRIVAL_RATE_TABLE_SIZE];
  double arrival_rate[ARRIVAL_RATE_TABLE_SIZE];
  long size;
  double max_arrival_rate;
};

long ibm_random_generator(long seed); 
void print_ibm_random_generator_seed(long size, long interval, long seed); 
void random_sequence_generator(double *sequence, long sequence_size, long seed_no, char *seed_table);
void read_seed_table(long *seed, long size, char *seed_table); 
double kol_smi_compute_d(double *sequence, long sequence_size);
int compare_double(const void *a, const void *b); 
int kol_smi_test(long sequence_size, double probability_reject, double d);
double chi_square_compute(double *sequence, long sequence_size, long interval_size);
double autocorrelation_compute(double *sequence, long sequence_size, long start, long interval);
double exponential_inverse_transform(double average_rate, double probability);
double exponential_random_generator(double average_rate, long *seed);
double empirical_inverse_transform(double x[], double r[], long size, double probability);
double empirical_discrete_inverse_transform(double r[], long size, double probability);
double empirical_geometric_inverse_transform(double r, double p);
double poisson_inverse_transform(double alpha, long *next_seed);
double nonstationary_poisson_process_random_generator(struct arrival_rate_table *arrival_rate_table, long *next_seed1, long *next_seed2);
 
#endif
