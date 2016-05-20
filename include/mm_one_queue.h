#ifndef MM_ONE_QUEUE_H
#define MM_ONE_QUEUE_H

enum server_state {IDLE, BUSY};

struct mm_one_simulation_result {
  double average_customer_in_system_time;
  long nr_customer;
  double *customer_in_system_time;
};

struct sample_input {
  double avg_interarrival_time;
  double avg_service_time;
  long nr_customer;
  double half_alpha;
  double eps_relative;
};

struct sample_output {
  double sample_avg;
  double sample_dev;
  double sample_ci_hw; /* confidence interval half width */
  long round;
};

struct batch_means_output {
  double avg;
  double ci_hw;
  double lag_1;
};

void mm_one_queue_simulator(long nr_customer, double average_interarrival_time, double average_service_time, long *next_seed_interarrival, long *next_seed_service, struct mm_one_simulation_result *result); 

void estimate_performance_of_mm_one_queue_simulator(struct sample_output *output_data, struct sample_input *input_data, long first_seed_interarrival, long first_seed_service);

void init_mm_one_simulation_result(struct mm_one_simulation_result *result, long nr_customer);

void free_array_in_mm_one_simulation_result(struct mm_one_simulation_result *result);

void mm_one_queue_simulator_with_initial_bias(long nr_customer, double average_interarrival_time, double average_service_time, long *next_seed_interarrival, long *next_seed_service, struct mm_one_simulation_result *result, long initial_bias); 

void mm_one_queue_simulator_for_batch_means(long nr_customer, double average_interarrival_time, double average_service_time, long *next_seed_interarrival, long *next_seed_service, long nr_batch, long batch_size, long initial_bias, double correlation_bound, double half_alpha, double eps_relative, struct batch_means_output *result); 
#endif
