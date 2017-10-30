#ifndef CUSTOMER_H
#define CUSTOMER_H

class Customer
{

public:
  int id;
  int timeEnterQ;
  int timeLeaveQ;
  int timeFinish;
  Customer(int x);
  void setTimeEnterQ(int x);
  void setTimeLeaveQ(int x);
  void setTimeFinish(int x);
};

#endif