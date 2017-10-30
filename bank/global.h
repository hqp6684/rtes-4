#ifndef GLOBAL_H
#define GLOBAL_H

#include <pthread.h>
#include "q_template.h"
#include "customer.h"

#define nullptr NULL

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


#endif
