
#include <customer.h>

struct customer *init_customer(int customer_no) {
  struct customer *customer;
  customer = (struct customer *) malloc(sizeof(struct customer));
  if (!customer) {
    exit(1);
  }
  customer->no = customer_no;
  return customer;
}
