#ifndef TELLER_H
#define TELLER_H

//#include "customer.h"
//#include "q_template.h"
//#include <pthread.h>

class Teller
{

public:
  int id;
  int count;
  int customerCount;
  int waitTimeStart;

  // Use this as a linked list to keep all customers
  QTemplate<Customer *> customers;
  // Keep track of wait time
  QTemplate<int> waitTimes;

  Teller(int x);

  void saveCustomer(Customer *customer_ptr);

  void getCustomer();

  static void *execute(void *arg);
};

#endif