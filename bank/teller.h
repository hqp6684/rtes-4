#ifndef TELLER_H
#define TELLER_H

//#include "customer.h"
//#include "q_template.h"
//#include <pthread.h>

class Teller
{

public:
  int id;
  // int count;
  // int customerCount;
  int waitTimeStart;
  bool isDone;

  // Use this as a linked list to keep all customers
  QTemplate<Customer *> customers;
  // Keep track of wait time
  // QTemplate<int> waitTimes;
  int waitSum;

  Teller(int x);

  void saveCustomer();

  void getCustomer();

  void serveCustomer(Customer *customer_ptr);
  void report();


  static void *execute(void *arg);
};

#endif