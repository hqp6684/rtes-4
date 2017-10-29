#include <pthread.h>
#include <iostream>

#include "global.h"
#include "teller.h"
#include "customer.h"
#include <unistd.h>

Teller::Teller(int x) : id(x)
{
  count = 0;
}
void Teller::saveCustomer(Customer *customer)
{
  customers.enQ(customer);
}

void Teller::getCustomer()
{
  int timer = 0;
  int hasLook = 0;

  Customer *cust_ptr = nullptr;
  sharedQ_ptr->deQ(cust_ptr);
  customers.enQ(cust_ptr);
  cout << "Get Customer" << endl;
}

void *Teller::execute(void *arg)
{

  int tmp = 0;

  Teller *ptr = static_cast<Teller *>(arg);

  while (1)
  {
    pthread_mutex_lock(&mutex);
    tmp = ptr->count++;
    pthread_mutex_unlock(&mutex);
    printf("My Id is %d\n", ptr->id);
    printf("Count is %d\n", tmp);

    /* snooze for 1 second */
    sleep(1);
  }

  return 0;
}