#ifndef MM_ONE_QUEUE_H
#define MM_ONE_QUEUE_H

enum server_state {IDLE, BUSY};

struct mm_one_simulation_result {
  double average_customer_in_system_time;
};

void mm_one_queue_simulator(long nr_customer, double average_interarrival_time, double average_service_time, long *next_seed_interarrival, long *next_seed_service, struct mm_one_simulation_result *result); 
#endif
