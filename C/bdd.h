/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/


#ifndef  _BDD_H_
#define _BDD_H_

#include"manager.h"

tBddNode * apply(tManager *,tBddNode*,tBddNode*,tBddNode*(*)());

tBddNode * bddOr(tBddNode *,tBddNode*);
tBddNode * bddNor(tBddNode *,tBddNode*);
tBddNode * bddAnd(tBddNode *,tBddNode*);
tBddNode * bddNand(tBddNode *,tBddNode*);
tBddNode * bddXor(tBddNode *,tBddNode*);
tBddNode * bddNeg(tBddNode *,tBddNode*);

#endif // _BDD_H_