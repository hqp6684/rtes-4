#ifndef TELLER_H
#define TELLER_H

#include "customer.h"
#include "q_template.h"

class Teller
{

public:
  int id;
  int customerCount;
  int;
  QTemplate<Customer> customers;
  QTemplate<int> waitTimes;

  Teller(int x);

  void increaseCustomerCount();

  void getCustomer();
};

#endif