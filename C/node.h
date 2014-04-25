/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/

/*
  Modul:      node
  
  Interface:
    struct BddNode (tBddNode)
      struct BddNode * high
      struct BddNode * low
      unsigned int     var
      unsigned int     ref
      struct BddNode * nextFree
    
    struct Garbage (tGarbage)
      tBddNode * nodes
      tBddNode * free    


    tError     nodeInit    (tGarbage *,unsigned int);
    void       nodeDestroy (tGarbage *);
    tBddNode * nodeGetNode (tGarbage *);
    void       nodeFreeNode(tGarbage *, tBddNode *);
    void       nodeIncRef  (tBddNode *);
    void       nodeDecRef  (tBddNode *);


*/

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
  tBddNode * free;    // list of free nodes
}tGarbage;

/**
 * init array of nodes and list of free nodes
 * 1. param -> garbage that will be initialized
 * 2. param -> number of allocated items
 * returns  -> E_OK iff success
 */
tError nodeInit(tGarbage *,unsigned int);

/**
 * free resources of garbage
 * 1. param -> garbage for destroying
 */
void nodeDestroy(tGarbage *);

/**
 * get pointer to first free node
 * 1. param -> garbage where you search
 * returns  -> NULL if there are no free nodes else pointer to first free node
 */
tBddNode * nodeGetNode(tGarbage *);
/**
 * insert node to free list
 * 1. param -> gargabe where you working
 * 2. param -> free node
 */
void nodeFreeNode(tGarbage *, tBddNode *);

/**
 * Inc/Dec reference counter in node
 * 1. param -> node
 */
void nodeIncRef(tBddNode *);
void nodeDecRef(tBddNode *);

#endif // _NODE_H_