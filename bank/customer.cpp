#include "global.h"
#include "customer.h"

Customer::Customer(int x)
    : id(x)
{
}

void Customer::setTimeEnterQ(int time)
{
    timeEnterQ = time;
};

void Customer::setTimeLeaveQ(int time)
{
    timeLeaveQ = time;
    int waitedTime = timeEnterQ - timeLeaveQ;
    if (waitedTime > maxWaitTime)
    {
        maxWaitTime = waitedTime;
    }
};

void Customer::setTimeFinish(int time)
{
    timeFinish = time;
    //  int transTime = timeFinish - timeEnterQ;
    //  if(transTime > maxTransTime){
    //      maxTransTime = transTime;
    //  }
}