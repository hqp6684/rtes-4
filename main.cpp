#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string>

#include "global.h"
#include "q_template.h"
#include "customer.h"
#include "teller.h"
#include <time.h>
#include <stdlib.h>

// Define Global variables
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
QTemplate<Customer *> *sharedQ_ptr = nullptr;
bool bankIsClosed = false;
bool mainQIsEmpty = true;

void delayProgram(double secondsToDelay)
{
    clock_t startTime = clock(); //Start timer
    cout << startTime <<endl;

    double secondsPassed;
    // double secondsToDelay = atof(argv[1]);
    std::cout << "Time to delay: " << secondsToDelay << std::endl;
    bool flag = true;
    while (flag)
    {
        secondsPassed = (clock() - startTime) / CLOCKS_PER_SEC;
        cout<<secondsPassed<<endl;
        if (secondsPassed >= secondsToDelay)
        {
            std::cout << secondsPassed << " seconds have passed" << std::endl;
            flag = false;
        }
    }
}

bool is_closed_time(clock_t start_time){

    double open_duration = 10;
    double timePassed;
    // cout << start_time <<endl;
    // cout << clock() <<endl;
    // cout << CLOCKS_PER_SEC <<endl;

    timePassed = (double) (clock()-start_time) / CLOCKS_PER_SEC;

    std::cout << "Time passed: " << timePassed << endl;

    if(timePassed >= open_duration )
    {
        std::cout << "Time to closed" << endl;
        return true;
    }else{
        std::cout << "Time remainng: " << (open_duration-timePassed) << endl;
        return false;
    }
}


int main(void)
{

    clock_t bank_start_time = clock();

    QTemplate<Customer *> custQ;
    // update global pointer for the above Q
    sharedQ_ptr = &custQ;

    // Keep track of all created Customers
    int customerCount = 0;


    Teller *teller_1 = new Teller(1);
    Teller *teller_2 = new Teller(2);
    Teller *teller_3 = new Teller(3);

    // Create thread holders
    pthread_t threadA;
    pthread_t threadB;
    pthread_t threadC;

    pthread_create(&threadA, NULL, &Teller::execute, (void *)teller_1);
    pthread_create(&threadB, NULL, &Teller::execute, (void *)teller_2);
    // pthread_create(&threadC, NULL, &Teller::execute, (void *)teller_3);


    while(!is_closed_time(bank_start_time)){

        // if(pthread_mutex_trylock(&mutex) == 0){
        // }else{
        // }

        if(sharedQ_ptr->isEmpty()){
            mainQIsEmpty = true;
        }else{
            mainQIsEmpty = false;
        }

        pthread_mutex_lock(&mutex);
        customerCount++;
        Customer *cust = new Customer(customerCount);

        clock_t timeEnter = clock();
        sharedQ_ptr->enQ(cust);


        // Update time entered Q
        cust->setTimeEnterQ(timeEnter);

        cout << "Enqueue new customer: " << customerCount <<endl;

        pthread_mutex_unlock(&mutex);

        // useconds_t v1 = rand() % 1000000;
        // sleep 
        // usleep(v1);
        sleep(1);

    }

    bankIsClosed = true;

    // Customer *cust_ptr = nullptr;

    // for(int i = 0; i <= customerCount; i++){

    //     sharedQ_ptr->deQ(cust_ptr);
    //     cout << cust_ptr->id << endl;
    // }

    // sleep();


    while (1)
    {
        sleep(1);
    }

    // cout << "We have a queue to hold names." << endl;
    // cout << "Our queue of names is " << (strque.isEmpty() ? "Empty" : "Not Empty");

    // cout << "We will put three names into our queue." << endl;

    //Enqueueing names...
    // for (int n = 0; n < 3; n++)
    // {
    //     customer *cust = new customer(n);
    //     custq.enq(cust);

    //     // cout << "Enter name: " << endl;
    //     // getline(cin, word);
    //     // strque.enQ(word);
    // }

    // Customer *cust_ptr = nullptr;
    // for (int n = 0; n < 3; n++)
    // {
    //     // strque.deQ(word);
    //     sharedQ_ptr->deQ(cust_ptr);
    //     cout << cust_ptr->id << endl;
    // }

    return 0;
}

