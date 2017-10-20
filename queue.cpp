#include <iostream>
#include "queue.h"
Q::Q()
    : frontIndex(-1),
      rearIndex(-1)
{
    // frontIndex = rearIndex = -1;
}

bool Q::isEmpty()
{
    return (frontIndex == -1 && rearIndex == -1);
}

// To check whether Queue is full or not
bool Q::isFull()
{
    return (rearIndex + 1) % MAX_QUEUE_SIZE == frontIndex ? true : false;
}

void Q::enQ(int element)
{
    std::cout << "Enqueuing " << element << " \n";
    if (isFull())
    {
        std::cout << "Error: Queue is Full\n";
        return;
    }
    if (isEmpty())
    {
        frontIndex = rearIndex = 0;
    }
    else
    {
        rearIndex = (rearIndex + 1) % MAX_QUEUE_SIZE;
    }
    qArray[rearIndex] = element;
}

//     // Removes an element in Q from front end
void Q::deQ()
{
    std::cout << "Dequeuing \n";
    if (isEmpty())
    {
        std::cout << "Error: Queue is empty\n";
        return;
    }
    // Accout the case when Q has only 1 element
    else if (frontIndex == rearIndex)
    {
        rearIndex = frontIndex = -1;
    }
    else
    {
        frontIndex = (frontIndex + 1) % MAX_QUEUE_SIZE;
    }
}

int Q::front()
{
    if (frontIndex == -1)
    {
        std::cout << "Error : cannot return front from empty Q\n";
        return -1;
    }
    return qArray[frontIndex];
}
