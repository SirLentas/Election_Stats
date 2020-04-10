#include "hashFunctions.h"
#include <iostream>
using namespace std;

int h1(const char *key,int TABLE_SIZE)
{
   const char *str = key;
   return *str% TABLE_SIZE;
}

int h2(const char *key,int TABLE_SIZE)//sdbm
{
   const char *str = key;
   unsigned int hash = 0;
   int c;
   while (c = *str++)
      hash = c + (hash << 6) + (hash << 16) - hash;
   return hash % TABLE_SIZE;
}

int h3(int h1,int h2,int i,int TABLE_SIZE)
{
  return (h1*i*h2)%TABLE_SIZE;
}
