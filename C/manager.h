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
#include"cache.h"

#define BDD_SMALL  (unsigned int) 64     // 5 logical variables
#define BDD_MEDIUM (unsigned int) 256    // 7 
#define BDD_BIG    (unsigned int) 1024   // 9 


#define isTerminal(t) (!(t->high))



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



tError bddInit(tManager *, unsigned int);
void bddDestroy(tManager *);
tError bddCreateTerminal(tManager *,char *,tBddNode **);
tError bddCreateNode(tManager *, char *, tBddNode *, tBddNode *,tBddNode **);
tError bddNewNode(tManager *, unsigned int, tBddNode *, tBddNode *,tBddNode **);

void printNodeValue(tManager *,tBddNode *);
void printTree(tManager *, tBddNode *);
void printNodeInfo(tManager *, tBddNode *);


#endif // _MANAGER_H_