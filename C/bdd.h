/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/

/*
  Modul:      bdd
  
  Interface:
    struct BddRoot (tBddRoot)
      tGarbage *   nodes;
      tLabels  *   variables;
      tLabels  *   terminals;

    tError bddInit   (tBddRoot *, unsigned int);
    void   bddDestroy(tBddRoot *);
    int    bddIsEmpty(tBddRoot *);
*/

/// TODO ///
/// 
/// Simply parser (+ * !)
/// Apply
/// Cache
///
/// /// ///



#ifndef  _BDD_H_
#define _BDD_H_

#include<stdlib.h>


#include"errors.h"
#include"node.h"
#include"labels.h"


#define BDD_SMALL  (unsigned int) 64     // 5 logical variables
#define BDD_MEDIUM (unsigned int) 256    // 7 
#define BDD_BIG    (unsigned int) 1024   // 9 




typedef struct Manager{
  tGarbage *   nodes;     // all avaible nodes for current bdd
  tBddNode *   free;      // all free nodes
  tLabels  *   variables; // all labels for variables
  tLabels  *   terminals; // all labels for terminal values
}tManager;

/**
 * allocate nodes and set root, variables and terminals to null
 * 1. param -> bdd that will be inited
 * 2. param -> number of allocated nodes
 * return   -> E_OK iff success
 */
tError bddInit(tManager *, unsigned int);

/**
 * free all resources of bdd
 * 1. param -> bdd to release
 */
void bddDestroy(tManager *);

tError bddCreateTerminal(tManager *,char *,tBddNode **);
tError bddCreateNode(tManager *, char *,tBddNode *,tBddNode *, tBddNode **);

#endif // _BDD_H_