#include <pthread.h>
#include <iostream>

#include "global.h"
#include "teller.h"
#include "customer.h"
#include <unistd.h>
#include <time.h>

Teller::Teller(int x) : id(x)
{
  // count = 0;
  isDone = false;
  waitSum = 0;
}

// Save customer into teller's Q
void Teller::saveCustomer()
{
  cout << "Teller " << id << " is getting customer from  the main Q" << endl;

  int timeNow = clock();

  Customer *cust_ptr = nullptr;
  sharedQ_ptr->deQ(cust_ptr);
  cust_ptr->setTimeLeaveQ(timeNow);
  customers.enQ(cust_ptr);

  // Unlock mutex, relase Q
  pthread_mutex_unlock(&mutex);

  // record wait time
  int waitTimeEnded = timeNow - waitTimeStart;
  if (waitTimeEnded > maxWaitTime)
  {
    maxWaitTime = waitTimeEnded;
  };

  waitSum += waitTimeEnded;

  serveCustomer(cust_ptr);
};

// Serve customer
void Teller::serveCustomer(Customer *cust_ptr)
{

  cout << "Teller " << id << " is serving Customer " << cust_ptr->id << endl;
  // Force teller to sleep with a random time to simuate working time
  // From 1 - 10 sec
  useconds_t randomTime = rand() % (ONE_MINUTE_IN_MICROSECONDS * 6);
  // sleep
  usleep(randomTime);

  // Update time finish
  cust_ptr->setTimeFinish(clock());
  cout << "Teller " << id << " finished serving Customer " << cust_ptr->id << endl;
}

void Teller::getCustomer()
{
  // printf("Teller %d started \n\r", id);

  bool flag = true;
LOOP:
  while (flag)
  {

    // Try to get the lock
    if (pthread_mutex_trylock(&mutex) == 0)
    {
      // Check if the main Q is empty
      if (sharedQ_ptr->isEmpty())
      {

        // Exit loop if time to close
        if (bankIsClosed)
        {
          flag = false;
        }
        else
        {
          // Start wait timer;
          if (waitTimeStart == 0)
          {
            waitTimeStart = clock();
          }
        }

        // Release mutex and go back to loop
        pthread_mutex_unlock(&mutex);

        useconds_t randomTime = rand() % ONE_MINUTE_IN_MICROSECONDS * 5;

        cout << "There is no customer in the Q, Teller " << id << " will check back in " << randomTime / ONE_MINUTE_IN_MICROSECONDS << "minutes" << endl;
        usleep(rand() % randomTime);
        // sleep(1);
        goto LOOP;
      }
      else
      {
        // Get customer from the main Q
        saveCustomer();
      }
    }
    else
    {
      // start timer
      if (waitTimeStart == 0)
      {
        waitTimeStart = clock();

        useconds_t randomTime = rand() % ONE_MINUTE_IN_MICROSECONDS * 5;

        cout << "Main Q is busy, Teller " << id << " will be back again in" << randomTime / ONE_MINUTE_IN_MICROSECONDS << "minutes" << endl;
        usleep(randomTime);
      }
    }
  }

  // Report
  report();
}

void *Teller::execute(void *arg)
{

  int tmp = 0;

  Teller *ptr = static_cast<Teller *>(arg);

  ptr->getCustomer();
}

void Teller::report()
{

  pthread_mutex_lock(&mutex);

  cout << "\r\n\r\n\r\n--------" << endl;
  cout << "Teller " << id << " served " << customers.getLength() << " customers\r\n\r\n"
       << endl;

  int averageWaitTime = waitSum / customers.getLength();
  while (!customers.isEmpty())
  {
    Customer *cust_ptr = nullptr;
    customers.deQ(cust_ptr);

    int servedTime = cust_ptr->timeFinish - cust_ptr->timeEnterQ;

    // servedTime = toMinute(servedTime);
    // cout << servedTime << endl;

    if (servedTime > maxTransTime)
    {
      maxTransTime = servedTime;
    };

    sharedQ_ptr->enQ(cust_ptr);
  }
  // for(int i = 0; i <customers.getLength(); i++){
  // }
  switch (id)
  {
  case 1:
    teller1AverageWaitTime = averageWaitTime;
    teller1Done = true;
    break;
  case 2:
    teller2AverageWaitTime = averageWaitTime;
    teller2Done = true;
    break;
  case 3:
    teller3AverageWaitTime = averageWaitTime;
    teller3Done = true;
    break;
  default:
    break;
  };
  pthread_mutex_unlock(&mutex);
}
