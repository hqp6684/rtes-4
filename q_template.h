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

    //Destructor
    ~QTemplate();

    //Operations

    void enQ(T);
    void deQ(T &);
    bool isEmpty() const;

    void destroyQ();
};
#endif