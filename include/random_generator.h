
#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#define SEED_TABLE_SIZE 10000
#define MOD_OPERAND_1 ((1L << 31) - 1)
#define ARRIVAL_RATE_TABLE_SIZE 256
#define PI 3.1415926

struct arrival_rate_table {
  double time[ARRIVAL_RATE_TABLE_SIZE];
  double mean_time_between_arrivals[ARRIVAL_RATE_TABLE_SIZE];
  double arrival_rate[ARRIVAL_RATE_TABLE_SIZE];
  long size;
  double max_arrival_rate;
};

long ibm_random_generator(long seed); 
double random_generator(long *next_seed);
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
double normal_cos_random_generator(long *next_seed1, long *next_seed2);
double normal_sin_random_generator(long *next_seed1, long *next_seed2);
double erlang_random_generator(long k, double theta, long *next_seed_array);
double approximation_inverse_cdf_normal_distribution(double r);
void bivariate_normal_random_generator(double x[2], double avg[2], double dev[2], double correlation, long *next_seed1, long *next_seed2);
double avg_sequence(double *seq, long size);
double dev_sequence(double *seq, long size);
double corr_sequence(double *seq[2], long size); 
double sample_lag1_corr_sequence(double *seq, long size);
double normal_random_generator(double avg, double dev, long *next_seed1, long *next_seed2);
double corr_t_t_1(double cov_t_t_1, double dev);
double dev_epsilen(double corr, double dev);
/* AR(1) model */
double time_series_random_generator(double x_t_1, double x_avg, double x_t_t_1_corr, double dev_epsilen);
/* EAR(1) model */
double time_series_ear_random_generator(double x_t_1, double corr, double avg_rate, long *next_seed_r, long *next_seed_eps);
#endif
