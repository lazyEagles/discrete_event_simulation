
#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#define SEED_TABLE_SIZE 10000
#define MOD_OPERAND_1 ((1L << 31) - 1)

long ibm_random_generator(long seed); 
void print_ibm_random_generator_seed(long size, long interval, long seed); 
void random_sequence_generator(double *sequence, long sequence_size, long seed_no, char *seed_table);
void read_seed_table(long *seed, long size, char *seed_table); 
double kolmogorov_smirnov_test(double *sequence, long sequence_size);
int compare_double(const void *a, const void *b); 
 
#endif
