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
}
void Teller::saveCustomer(Customer *customer)
{
  customers.enQ(customer);
}

void Teller::getCustomer()
{
  int timer = 0;
  // cout << "Teller " << id << "started" <<endl;
      printf("Teller %d started \n\r", id);

  bool flag = true;
  LOOP:
  while(flag){

    if(pthread_mutex_trylock(&mutex) == 0){


      if(sharedQ_ptr->isEmpty()){
        if(bankIsClosed){
          flag = false;
        }

        pthread_mutex_unlock(&mutex);
        goto LOOP;
      }
      int timeNow = clock();

      cout << "Teller " <<id <<" is getting customer from  the main Q" <<endl;
      // Get customer from the main Q
      Customer *cust_ptr = nullptr;
      sharedQ_ptr->deQ(cust_ptr);
      customers.enQ(cust_ptr);
      
      
      cust_ptr->setTimeLeaveQ(timeNow);

      // Unlock mutex, relase Q
      pthread_mutex_unlock(&mutex);

      // record wait time
      int waitTimeEnded = timeNow - waitTimeStart;
      waitTimes.enQ(waitTimeEnded);


      cout << "Teller " << id << " is serving Customer " <<cust_ptr->id <<endl;

      // Force teller to sleep with a random time to simuate working time
      // From 1 - 10 sec
      useconds_t randomTime = rand() % 1000000;
        // sleep 
      usleep(randomTime);

      // Update time finish 
      cust_ptr->setTimeFinish(clock());
      cout << "Teller " << id << " finished serving Customer " <<cust_ptr->id <<endl;
      

    }
    else{
      // start timer 
      if(waitTimeStart == 0){
        cout << "Main Q is busy, Teller "<< id << "is waiting"<<endl;
        waitTimeStart = clock();
        // sleep(1);
        useconds_t v1 = rand() % 1000000;
        // sleep 
        usleep(v1);
      }
    }
  }


  printf("Teller has served %d customer\r\n", customers.getLength());

  // if(!bankIsClosed && !sharedQ_ptr->isEmpty()){

  //   cout<< "Bank is closed" << endl;
  //   cout <<"Teller " << id << "stops getting "
  // }
  // else (sharedQ_ptr->isEmpty())
  // {
  //   cout << "Q is empty" << endl;

  // }
  // else
  // {
  //   Customer *cust_ptr = nullptr;
  //   sharedQ_ptr->deQ(cust_ptr);
  //   customers.enQ(cust_ptr);
  // }
  // cout << "Get Customer" << endl;
}

void *Teller::execute(void *arg)
{

  int tmp = 0;

  Teller *ptr = static_cast<Teller *>(arg);

  ptr->getCustomer();

  // while (!bankIsClosed && ptr->isDone )
  // {
  //   // pthread_mutex_lock(&mutex);
  //   // tmp = ptr->count++;
  //   // pthread_mutex_unlock(&mutex);
  //   // printf("My Id is %d\n", ptr->id);
  //   // printf("Count is %d\n", tmp);

  //   /* snooze for 1 second */
  //   // sleep(1);
  // }

  // return 0;
}