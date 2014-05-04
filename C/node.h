/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/


#ifndef  _NODE_H_
#define _NODE_H_

#include<stdlib.h>
#include"errors.h"

typedef struct BddNode{
  struct BddNode * high, * low; // successors
  unsigned int var;             // variables label
  unsigned int ref;             // ref counter
  struct BddNode * nextFree;    // next free node
}tBddNode;


typedef struct Garbage{
  tBddNode * nodes;   // array of all avaible nodes
  struct Garbage* next;    // list of free nodes
}tGarbage;


tError nodeInit(tGarbage **,unsigned int);
void nodeDestroy(tGarbage *);

#endif // _NODE_H_