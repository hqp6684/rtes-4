#include <iostream>
// #include <string>
#include "q_template.h"

using namespace std;

template <class T>
QTemplate<T>::QTemplate()
{
    front = NULL;
    back = NULL;
    qNum = 0;
}

template <class T>
QTemplate<T>::~QTemplate()
{
    destroyQ();
}

template <class T>
void QTemplate<T>::enQ(T val)
{
    qNode *newNode;

    //Create new node, have it hold val
    newNode = new qNode;
    newNode->data = val;
    newNode->next = NULL;

    //Change front and back pointers,
    //depending if the q is empty or already contains data

    if (isEmpty())
    {
        front = newNode;
        back = newNode;
    }
    else
    {
        back->next = newNode;
        back = newNode;
    }

    //update number of items in q
    qNum++;
}
// clock_gettime
template <class T>
void QTemplate<T>::deQ(T &val)
{
    qNode *temp;

    if (isEmpty())
    {
        cout << "No data currently qd" << endl;
    }
    else
    {
        //Store data from front node in val
        val = front->data;
        //Remove front node, delete
        temp = front;
        front = front->next;
        delete temp;

        //Update qNum
        qNum--;
    }
}

template <class T>
bool QTemplate<T>::isEmpty() const
{
    bool empty;

    if (qNum > 0)
        empty = false;
    else
        empty = true;

    return empty;
}

template <class T>
void QTemplate<T>::destroyQ()
{
    T temp;

    while (!isEmpty())
    {
        deQ();
    }
}