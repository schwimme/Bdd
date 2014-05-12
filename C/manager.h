/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/


#ifndef  _MANAGER_H_
#define _MANAGER_H_

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
  unsigned int var;
  tBddNode *high, *low, *record;
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


tBddNode *cacheCheck(tManager *,tBddNode *);
void cacheDelete(tManager *,tBddNode *);
tError cacheInsert(tManager *,tBddNode *);


tError bddInit(tManager *, unsigned int);
void bddDestroy(tManager *);
tError bddCreateTerminal(tManager *,char *,tBddNode **);
tError bddCreateNode(tManager *, char *, tBddNode **);
tError mtbddCreateNode(tManager *bdd, char *label,tBddNode *,tBddNode *, tBddNode **);
tError bddNewNode(tManager *, char *, tBddNode *, tBddNode *,tBddNode **);
void printNodeValue(tManager *,tBddNode *);
void printTree(tManager *, tBddNode *);
void printNodeInfo(tManager *, tBddNode *);


#endif // _MANAGER_H_