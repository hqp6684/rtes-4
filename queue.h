#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUE_SIZE 10
#include <iostream>

class Q
{
private:
  int qArray[MAX_QUEUE_SIZE];
  int frontIndex, rearIndex;

public:
  Q();
  bool isEmpty(void);
  bool isFull(void);
  void enQ(int);
  void deQ(void);
  int front(void);
};
#endif