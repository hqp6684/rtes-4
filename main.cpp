#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string>

#include "global.h"
#include "q_template.h"
#include "customer.h"
#include "teller.h"
#include <list>

// Define Global variables
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
QTemplate<Customer *> *sharedQ_ptr = nullptr;

int main(void)
{

    QTemplate<string> strque;
    QTemplate<Customer *> custQ;

    // std::list<pthread_t> pthreads(3);

    // Teller tellers[3];
    // pthread_t pthreads[3];

    Teller *teller_1 = new Teller(1);
    Teller *teller_2 = new Teller(2);
    Teller *teller_3 = new Teller(3);
    // update global variable;
    sharedQ_ptr = &custQ;

    pthread_t threadA;
    // pthread[0] = threadA;
    pthread_t threadB;
    pthread_t threadC;

    // for (int i = 0; i < 2; i++)
    // {
    //     tellers[i] = new Teller(i + 1);

    //     pthread_create(&pthread[i], &Teller::execute, (void *)tellers[i]);
    // }

    pthread_create(&threadA, NULL, &Teller::execute, (void *)teller_1);
    pthread_create(&threadB, NULL, &Teller::execute, (void *)teller_2);
    pthread_create(&threadC, NULL, &Teller::execute, (void *)teller_3);
    sleep(30);

    // cout << "We have a queue to hold names." << endl;
    // cout << "Our queue of names is " << (strque.isEmpty() ? "Empty" : "Not Empty");

    // cout << "We will put three names into our queue." << endl;

    //Enqueueing names...
    for (int n = 0; n < 3; n++)
    {
        Customer *cust = new Customer(n);
        custQ.enQ(cust);

        // cout << "Enter name: " << endl;
        // getline(cin, word);
        // strque.enQ(word);
    }

    cout << "Our queue of names is " << (strque.isEmpty() ? "still empty" : "no longer empty");
    cout << "The program will read back the names in the order they were entered.\n";

    Customer *cust_ptr = nullptr;
    for (int n = 0; n < 3; n++)
    {
        // strque.deQ(word);
        sharedQ_ptr->deQ(cust_ptr);
        cout << cust_ptr->id << endl;
    }

    return 0;
}