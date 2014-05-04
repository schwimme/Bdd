/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/


#ifndef  _BDD_H_
#define _BDD_H_

#include<stdlib.h>
#include<stdio.h>


#include"errors.h"
#include"node.h"
#include"labels.h"

#define BDD_SMALL  (unsigned int) 64     // 5 logical variables
#define BDD_MEDIUM (unsigned int) 256    // 7 
#define BDD_BIG    (unsigned int) 1024   // 9 


#define isTerminal(t) (!(t->high))



typedef struct Cache{
  tBddNode * record;
  struct Cache * next;
} tCache;


typedef struct Manager{
  tGarbage *   nodes;     // all avaible nodes for current bdd
  tBddNode *   free;      // all free nodes
  tLabels  *   variables; // all labels for variables
  tLabels  *   terminals; // all labels for terminal values
  tCache   *   cache;     // used nodes
}tManager;

extern tBddNode * bddTrue;
extern tBddNode * bddFalse;

void nodeIncRef(tBddNode *);
void nodeDecRef(tManager *,tBddNode *);


tError cacheCheck(tManager *,tBddNode **); 


tError bddInit(tManager *, unsigned int);
void bddDestroy(tManager *);
tError bddCreateTerminal(tManager *,char *,tBddNode **);
tError bddCreateNode(tManager *, char *, tBddNode **);
void printNodeValue(tManager *,tBddNode *);


#endif // _BDD_H_