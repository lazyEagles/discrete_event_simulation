
#include "customer.h"
#include <stdlib.h>

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
