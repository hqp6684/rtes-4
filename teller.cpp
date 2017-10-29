#include "teller.h"

class Teller
{

public:
  int id;
  int customerNum;
  int timeWait;
  Teller(int x);
};

Teller::Teller(int x) : id(x) {}

void Teller::increateseCustomerCount()
{
  customerCount++;
}