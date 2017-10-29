#ifndef GLOBAL_H
#define GLOBAL_H

#include <pthread.h>
#include "q_template.h"
#include "customer.h"

extern pthread_mutex_t mutex;

extern QTemplate<Customer *> *sharedQ_ptr;

#endif
