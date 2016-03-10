
#include <customer.h>
#include <event_list.h>
#include <queue.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  if (argc != 5) {
    fprintf(stderr, "Usage: ./simulation_template interarrival_seed service_seed average_interarrival_time average_service_time\n");
    return 0;
  }
  struct event *event_list = NULL;
  struct queue system_queue;
  double system_clock = 0.0;
  struct event *event;

  enum event_type;
  int customer_number;
  int clock_time;
  int arrival_time;
  int interarrival_time;
  int departure_time;

  struct customer *customer;

  /* generate 2 independent random sequence of 10^6 */

  long interarrival_seed = atol(argv[1]);
  long service_seed = atol(argv[2]);

  double average_interarrival_time; /* default 10s */
  double lamda; /* interarrival rate: lamda = 1 / average_time */
  double average_service_time; /* average_service_time < average_interarrival_tiem */
  double mu; /* service_rate: mu = 1 / arverage_service_time */
  /* lamda/mu < 1 */

  /* initial system */
  init_queue(&system_queue);

  /* step 0: initial first event and add into event list */
  event_type = ARRIVAL;
  clock_time = 0;
  customer_number = 0;

  customer = init_customer(customer_number);

  add_event(&event_list, event_type, clock_time, (void *) customer);

  /* step 1: pop event from event list */
  event = get_event(event_list);
  if (!event) {
    exit(1);
  }

  /* step 2: addvance clock */
  system_clock = event->clock_time;

  /* step 3: update state */

  while (event) {
    pop_event(&event_list);
    /* step 4: generate future event into event list */

    /* step 5: update statics */

    /* free memory */
    free((struct customer *)event->content);
    free(event);
    
    /* get next event */
    event = get(event_list);
  }

  return 0;
}
