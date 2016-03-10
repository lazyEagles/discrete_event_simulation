
#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#define SEED_TABLE_SIZE 10000
#define MOD_OPERAND_1 ((1L << 31) - 1)

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
 
#endif
