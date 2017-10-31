#ifndef GLOBAL_H
#define GLOBAL_H

#include <pthread.h>
#include "q_template.h"
#include "customer.h"

#define nullptr NULL

/*
System | Real time
100 ms  =   60s
??  ms  =   28800s
28800*100/60
48000ms = 28800s = 8 hours
Hence, 48000ms = 48 seconds
*/

// #define OPEN_DURATION_IN_SECONDS 48
#define OPEN_DURATION_IN_SECONDS 5
// 100ms = 1 miunute
#define ONE_MINUTE_IN_MICROSECONDS 100000

extern pthread_mutex_t mutex;

extern QTemplate<Customer *> *sharedQ_ptr;

extern bool bankIsClosed;
extern bool mainQIsEmpty;

extern bool teller1Done;
extern int teller1AverageWaitTime;
extern bool teller2Done;
extern int teller2AverageWaitTime;
extern bool teller3Done;
extern int teller3AverageWaitTime;

extern int maxWaitTime;
extern int maxTransTime;
extern int maxQLength;

extern int toMinute(int time);

#endif
