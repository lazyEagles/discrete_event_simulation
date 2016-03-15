#include "customer.h"
#include "event_list.h"
#include "queue.h"
#include "random_generator.h"
#include <stdio.h>
#include <stdlib.h>

#define SEED_TABLE_SIZE 10000

enum server_state {IDLE, BUSY};

int main(int argc, char *argv[]) {

  if (argc != 5) {
    fprintf(stderr, "Usage: ./simulation_template average_interarrival_time average_service_time seed_no_interarrival seed_no_service\n");
    return 0;
  }
  struct event *event_list = NULL;
  struct queue system_queue;
  enum server_state server_state = IDLE;
  double system_clock = 0.0;
  struct event *event;

  enum event_type event_type;
  int customer_number;
  double clock_time;
  double arrival_time;
  double interarrival_time;
  double departure_time;
  double service_time;

  struct customer *customer;

  /* generate 2 independent random sequence of 10^6 */

  double average_interarrival_time = atof(argv[1]); /* default 10s */
  double lamda_interarrival_rate = 1.0 / average_interarrival_time; /* interarrival rate: lamda = 1 / average_time */
  double average_service_time = atof(argv[2]); /* average_service_time < average_interarrival_tiem */
  double mu_service_rate = 1.0 / average_service_time; /* service_rate: mu = 1 / arverage_service_time */
  /* lamda/mu < 1 */

  long seed_table[SEED_TABLE_SIZE];
  long seed_no_interarrival = atol(argv[3]);
  long seed_no_service = atol(argv[4]);
  long next_seed_interarrival;
  long next_seed_service;
  /* initial system */
  read_seed_table(seed_table, SEED_TABLE_SIZE, "../data/seed_table_size_10000_interval_100000_seed_1.txt");
  next_seed_interarrival = seed_table[seed_no_interarrival];
  next_seed_service = seed_table[seed_no_service];

  init_queue(&system_queue);

  /* step 0: initial first event and add into event list */
  event_type = ARRIVAL;
  clock_time = 1.0;
  customer_number = 0;

  customer = init_customer(customer_number);
  customer_number++;
  add_event(&event_list, event_type, clock_time, (void *) customer);

  /* step 1: pop event from event list */
  event = get_event(event_list);
  if (!event) {
    fprintf(stderr, "Error: event list is empty.\n");
    exit(EXIT_FAILURE);
  }



  while (event) {
    /* step 2: addvance clock */
    system_clock = event->clock_time;
    pop_event(&event_list);
    /* get customer */
    customer = (struct customer *) event->content;
    event->content = NULL;
    switch (event->event_type) {
      case ARRIVAL:
        /* print info */
        printf("ARRIVAL: time: %12f customer: %d\n", system_clock, customer->no);
        /* step 3: update state */
        if (server_state == IDLE) {
          server_state = BUSY;
          /* generate service time and departure time */
          service_time = exponential_random_generator(mu_service_rate, &next_seed_service);
          departure_time = system_clock + service_time;
          event_type = DEPARTURE;
          add_event(&event_list, event_type, departure_time, (void *) customer);
        } else if (server_state == BUSY) {
          /* add customer into queue */
          enqueue(&system_queue, (void *) customer);
        }
        /* step 4: generate future event into event list */
        /* generate next arrival event */
        interarrival_time = exponential_random_generator(lamda_interarrival_rate, &next_seed_interarrival);
        arrival_time = system_clock + interarrival_time;
        event_type = ARRIVAL;
        customer = init_customer(customer_number);
        customer_number++;
        add_event(&event_list, event_type, arrival_time, (void *) customer);
     
        break;
      case DEPARTURE:
        /* print info */
        printf("DEPARTURE: time: %12f customer: %d\n", system_clock, customer->no);
        free(customer);
        customer = NULL;
        /* step 3: update state */
        if (system_queue.count > 0) {
          customer = (struct customer *) dequeue(&system_queue);
          /* generate service time and departure time */
          service_time = exponential_random_generator(mu_service_rate, &next_seed_service);
          departure_time = system_clock + service_time;
          event_type = DEPARTURE;
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

    /* step 5: update statics */

    /* free memory */
    free(event);
    event = NULL;
    
    /* get next event */
    event = get_event(event_list);
  }

  printf("End: event list is empty.\n");

  return 0;
}
