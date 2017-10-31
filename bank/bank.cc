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
bool teller1Done = false;
bool teller2Done = false;
bool teller3Done = false;
int teller1AverageWaitTime = 0;
int teller2AverageWaitTime = 0;
int teller3AverageWaitTime = 0;

int maxWaitTime = 0;
int maxTransTime = 0;
int maxQLength = 0;

int customerCount = 0;

bool is_closed_time(clock_t start_time)
{

    double timePassed;

    timePassed = (double)(clock() - start_time) / CLOCKS_PER_SEC;

    // std::cout << "Time passed: " << timePassed << endl;

    if (timePassed >= OPEN_DURATION_IN_SECONDS)
    {
        // std::cout << "Time to closed" << endl;
        return true;
    }
    else
    {
        // std::cout << "Time remainng: " << (OPEN_DURATION_IN_SECONDS - timePassed) << endl;
        return false;
    }
}

void *receptionist(void *arg)
{
    cout << "Welcome to ABC Bank !!!!" << endl;

    while (!bankIsClosed)
    {

        if (sharedQ_ptr->isEmpty())
        {
            mainQIsEmpty = true;
        }
        else
        {
            mainQIsEmpty = false;
        }

        pthread_mutex_lock(&mutex);
        customerCount++;
        Customer *cust = new Customer(customerCount);

        clock_t timeEnter = clock();
        sharedQ_ptr->enQ(cust);

        // Update time entered Q
        cust->setTimeEnterQ(timeEnter);

        cout << "Enqueuing new customer: " << customerCount << endl;

        // update max queue length
        if (sharedQ_ptr->getLength() > maxQLength)
        {
            maxQLength = sharedQ_ptr->getLength();
        }

        // useconds_t ran1 = rand() % (ONE_MINUTE_IN_MICROSECONDS * 4);
        // usleep(ran1);
        pthread_mutex_unlock(&mutex);
        useconds_t ran2 = rand() % (ONE_MINUTE_IN_MICROSECONDS * 3);
        usleep(ran2);
    }

    cout << "Receptionist is finished" << endl;
    while (1)
    {
        sleep(1);
    }

    return 0;
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
    pthread_t threadD;

    pthread_create(&threadD, NULL, receptionist, NULL);
    pthread_create(&threadA, NULL, &Teller::execute, (void *)teller_1);
    pthread_create(&threadB, NULL, &Teller::execute, (void *)teller_2);
    pthread_create(&threadC, NULL, &Teller::execute, (void *)teller_3);

    while (!is_closed_time(bank_start_time))
    {
    }

    bankIsClosed = true;

    while (!teller1Done && !teller2Done && !teller3Done)
    {
        sleep(1);
    }

    cout << "Total number of customers serviced: " << customerCount + 1 << endl;
    cout << "Maximum customer wait time in the queue: " << maxWaitTime << endl;
    cout << "Maximum transaction time for the tellers: " << maxTransTime << endl;
    cout << "Maximum deep of the queue: " << maxQLength << endl;

    int waitSum = 0;
    int serveSum = 0;
    while (!sharedQ_ptr->isEmpty())
    {

        Customer *cust = new Customer(customerCount);

        sharedQ_ptr->deQ(cust);
        int waitTime = cust->timeLeaveQ - cust->timeEnterQ;
        waitSum += waitTime;

        int serveTime = cust->timeFinish - cust->timeEnterQ;
        serveSum += serveTime;
    }

    cout << "Average time each customer spends waiting in the Q: " << waitSum / (customerCount + 1) << endl;
    cout << "Average time each customer spends with the teller: " << serveSum / maxQLength << endl;
    int tellerWaitSum = teller1AverageWaitTime + teller2AverageWaitTime + teller3AverageWaitTime;
    int tellAverageWait = tellerWaitSum / 3;
    cout << "Average time tellers wait for customer " << tellAverageWait << endl;

    return 0;
}
