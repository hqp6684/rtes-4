#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string>

#include "q_template.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int count = 0;

void *function1(void *arg)
{
    int tmp = 0;

    while (1)
    {
        pthread_mutex_lock(&mutex);
        tmp = count++;
        pthread_mutex_unlock(&mutex);
        printf("Count is %d\n", tmp);

        /* snooze for 1 second */
        sleep(1);
    }

    return 0;
}

void *function2(void *arg)
{
    int tmp = 0;

    while (1)
    {
        pthread_mutex_lock(&mutex);
        tmp = count--;
        pthread_mutex_unlock(&mutex);
        printf("** Count is %d\n", tmp);

        /* snooze for 2 seconds */
        sleep(2);
    }

    return 0;
}

int main(void)
{
    // pthread_t threadA;
    // pthread_t threadB;
    // pthread_create(&threadA, NULL, &function1, NULL);
    // pthread_create(&threadB, NULL, &function2, NULL);

    // /* Let the threads run for 60 seconds. */
    // sleep(60);
    
    string word;
    int number;
     
    QTemplate<string> strque;
    QTemplate<int> intque;


    cout << "We have a queue to hold names." << endl;
	cout << "Our queue of names is " << (strque.isEmpty() ? "Empty" : "Not Empty");

	cout << "We will put three names into our queue." << endl;

	//Enqueueing names...
	for (int n = 0; n < 3; n++)
	{
		cout << "Enter name: " << endl;
		getline(cin, word);
		strque.enQ(word);
	}

	cout << "Our queue of names is " << (strque.isEmpty() ? "still empty" : "no longer empty");
	cout << "The program will read back the names in the order they were entered.\n";

	for (int n = 0; n < 3; n++)
	{
		strque.deQ(word);
		cout << word << endl;
	}

    return 0;
}