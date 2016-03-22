
#ifndef CUSTOMER_H
#define CUSTOMER_H

struct customer {
  int no;
  double service_time;
};

struct customer *init_customer(int customer_no); 
void add_service_time_to_customer(struct customer *customer, double service_time);
double get_service_time_from_customer(struct customer *customer);

#endif
