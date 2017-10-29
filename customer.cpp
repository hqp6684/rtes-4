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
};

void Customer::setTimeFinish(int time)
{
    timeFinish = time;
}