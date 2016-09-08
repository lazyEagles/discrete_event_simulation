
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MOD_OPERAND_1 ((1L << 31) - 1)
#define QUEUE_LEN 512
#define SEED_TABLE_SIZE 10000

enum server_state {IDLE, BUSY};
enum event_type {ARRIVAL, DEPARTURE};

/* data structure */

struct queue {
  void* array[QUEUE_LEN];
  int in;
  int out;
  int count;  
};

struct customer {
  int no;
  double service_time;
  double arrival_time;
  double departure_time;
};

struct event {
  enum event_type event_type;
  double clock_time;
  void *content;
  struct event *next;
};

/* function */

/* for random number generator */
long ibm_random_generator(long seed) {
  long mod_operand = (1L << 31) - 1;
  long mul_operand = 7 * 7 * 7 * 7 * 7;
  long result = (mul_operand * seed) % mod_operand;

  return result;
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

/* for queue */
void init_queue(struct queue *queue) {
  queue->in = 0;
  queue->out = 0;
  queue->count = 0;
}

void enqueue(struct queue *queue, void *entity) {
  if (queue->count >= QUEUE_LEN) {
    exit(1);
  }
  queue->array[queue->in] = entity;
  queue->in = (queue->in + 1) % QUEUE_LEN;
  queue->count++;
}

void *dequeue(struct queue *queue) {
  void *result;
  if (queue->count <= 0) {
    exit(1);
  }
  result = queue->array[queue->out];
  queue->out = (queue->out + 1) % QUEUE_LEN;
  queue->count--;
  return result;
}

/* for customer */
struct customer *init_customer(int customer_no) {
  struct customer *customer;
  customer = (struct customer *) malloc(sizeof(struct customer));
  if (!customer) {
    exit(1);
  }
  customer->no = customer_no;
  customer->service_time = 0.0;
  customer->arrival_time = 0.0;
  customer->departure_time = 0.0;
  return customer;
}

void add_service_time_to_customer(struct customer *customer, double service_time) {
  if (!customer) {
    exit(1);
  }
  customer->service_time = service_time;
}

double get_service_time_from_customer(struct customer *customer) {
  return customer->service_time;
}

/* for event */
void add_event(struct event **event_list, enum event_type event_type, double clock_time, void *content) {
  struct event *event;
  struct event *ptr;
  struct event *prev;
  event = (struct event *) malloc(sizeof(struct event));
  if (!event) {
    fprintf(stderr, "ERROR: malloc fails!\n");
    exit(1);
  }
  event->event_type = event_type;
  event->clock_time = clock_time;
  event->content = content;
  event->next = NULL;
  /* initial */
  if (!(*event_list)) {
    *event_list = event;
    return;
  } 
  /* insert into suitable position */
  prev = NULL;
  for (ptr = *event_list; (ptr != NULL) && (ptr->clock_time < event->clock_time); ptr = ptr->next) {
    prev = ptr;
  }
  event->next = ptr;
  if (!prev) {
    *event_list = event;
  } else {
    prev->next = event;
  }
}

void pop_event(struct event **event_list) {
  if (!(*event_list)) {
    exit(1);
  }
  *event_list = (*event_list)->next;
}

/* return NULL if no event in event list */
struct event *get_event(struct event *event_list) {
  return event_list;
}

void mm_one_queue_simulator(long nr_customer, double average_interarrival_time, double average_service_time, long *next_seed_interarrival, long *next_seed_service) {
  struct event *event_list = NULL;
  struct queue system_queue;
  enum server_state server_state = IDLE;
  double system_clock = 0.0;
  struct event *event;

  enum event_type event_type;
  int customer_number = 0;
  double clock_time;
  double arrival_time;
  double interarrival_time;
  double departure_time;
  double service_time;

  struct customer *customer;

  double lamda_interarrival_rate = 1.0 / average_interarrival_time; /* interarrival rate: lamda = 1 / average_time */
  double mu_service_rate = 1.0 / average_service_time; /* service_rate: mu = 1 / arverage_service_time */

  double total_customer_in_system_time = 0.0; 
  /* initial system */
  init_queue(&system_queue);

  /* step 0: initial first event and add into event list */
#ifdef DEBUG
  printf("Info: simulation starts.\n");
#endif
  if (customer_number < nr_customer) {
    event_type = ARRIVAL;
    clock_time = 1.0;
    customer = init_customer(customer_number);
    customer->arrival_time = clock_time;
    customer_number++;
    add_event(&event_list, event_type, clock_time, (void *) customer);
  }
  /* step 1: pop event from event list */
  event = get_event(event_list);
  while (event) {
    /* step 2: addvance clock */
    system_clock = event->clock_time;
    pop_event(&event_list);
    /* get customer */
    customer = (struct customer *) event->content;
    event->content = NULL;
    switch (event->event_type) {
      case ARRIVAL:
#ifdef DEBUG
        /* print info */
        printf("Info: [time: %12f] [customer: %8d] event: ARRIVAL\n", system_clock, customer->no);
#endif
        /* generate service time */
        service_time = exponential_random_generator(mu_service_rate, next_seed_service);
        add_service_time_to_customer(customer, service_time);
        /* step 3: update state */
        if (server_state == IDLE) {
          server_state = BUSY;
          /* set service time and departure time */
          service_time = customer->service_time;
          departure_time = system_clock + service_time;
          event_type = DEPARTURE;
          customer->departure_time = departure_time;
          add_event(&event_list, event_type, departure_time, (void *) customer);
        } else if (server_state == BUSY) {
          /* add customer into queue */
          enqueue(&system_queue, (void *) customer);
        }
        /* step 4: generate future event into event list */
        /* if customer_number < nr_customer, generate next arrival event */
        if (customer_number < nr_customer) {
          interarrival_time = exponential_random_generator(lamda_interarrival_rate, next_seed_interarrival);
          arrival_time = system_clock + interarrival_time;
          event_type = ARRIVAL;
          customer = init_customer(customer_number);
          customer->arrival_time = arrival_time;
          customer_number++;
          add_event(&event_list, event_type, arrival_time, (void *) customer);
        }
     
        break;
      case DEPARTURE:
        /* print info */
        printf("Info: [time: %12f] --------------------------------------- [customer: %8d] event: DEPARTURE\n", system_clock, customer->no);
        total_customer_in_system_time += customer->departure_time - customer->arrival_time;
        free(customer);
        customer = NULL;
        /* step 3: update state */
        if (system_queue.count > 0) {
          customer = (struct customer *) dequeue(&system_queue);
          /* set service time and departure time */
          service_time = get_service_time_from_customer(customer);
          departure_time = system_clock + service_time;
          event_type = DEPARTURE;
          customer->departure_time = departure_time;
          add_event(&event_list, event_type, departure_time, (void *) customer);
        } else if (system_queue.count == 0) {
          server_state = IDLE;
        }

        /* step 4: generate future event into event list */
        break;
      default:
        fprintf(stderr, "Error: unkown event type.\n");
        exit(EXIT_FAILURE);
    }
    free(event);
    event = NULL;

    /* get next event */
    event = get_event(event_list);
  }
  printf("Info: event list is empty.\n");
  printf("Info: simulation ends.\n");
}

int main() {
  long seed_table[SEED_TABLE_SIZE];
  long seed_array[2];
  long nr_customer = 1000;
  double avg_interarrival_time = 10.0;
  double avg_service_time = 5.0;

  read_seed_table(seed_table, SEED_TABLE_SIZE, "../data/seed_table_size_10000_interval_100000_seed_1.txt");
  seed_array[0] = seed_table[10];
  seed_array[1] = seed_table[30];

  mm_one_queue_simulator(nr_customer, avg_interarrival_time, avg_service_time, &seed_array[0], &seed_array[1]);

  return 0;
}
