#ifndef QTEMPLATE_H
#define QTEMPLATE_H

#include <iostream>

using namespace std;
#pragma once

template <class T>
class QTemplate
{
private:
  //Struct for nodes
  struct qNode
  {
    T data;      //Node's value
    qNode *next; //Pointer
  };

  qNode *front; //Pointer, holds the front of the q
  qNode *back;  //Pointer, holds the back of the q

  int qNum; //Tracks number of items in q

public:
  //Constructor
  QTemplate();

  //Operations

  void enQ(T);
  void deQ(T &);
  int getLength() const;
  bool isEmpty() const;
};

template <class T>
QTemplate<T>::QTemplate()
{
  front = NULL;
  back = NULL;
  qNum = 0;
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
int QTemplate<T>::getLength() const
{
  return qNum;
}

#endif