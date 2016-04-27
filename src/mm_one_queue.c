
#include "mm_one_queue.h"
#include "event_list.h"
#include "customer.h"
#include "queue.h"
#include "random_generator.h"
#include <stdio.h>
#include <stdlib.h>

void mm_one_queue_simulator(long nr_customer, double average_interarrival_time, double average_service_time, long *next_seed_interarrival, long *next_seed_service, struct mm_one_simulation_result *result) {
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
  printf("Info: simulation ends.\n");
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
        /* print info */
        printf("Info: [time: %12f] [customer: %8d] event: ARRIVAL\n", system_clock, customer->no);
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
  if (result) {
    result->average_customer_in_system_time = total_customer_in_system_time / nr_customer;
    printf("Info: average time of a customer in system: %12f\n", result->average_customer_in_system_time);
  }
  printf("Info: event list is empty.\n");
  printf("Info: simulation ends.\n");
}
