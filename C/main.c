/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/

/*
  Modul:    head - test file
*/
#include"bdd.h"

tBddNode * Son, *Soff, *Sset, *Scount;

tBddNode * func(tBddNode *x, tBddNode *y){
  if(x == y)                  return x;
  if(x == Soff || y == Soff)  return Soff;
  if(x == Son)                return y;
  if(y == Son)                return x;
  return Scount;
}

int main(){
  tManager mgr;
  // tBddNode *xOnOff, *xSetCount, *tmp;
  
  bddInit(&mgr,BDD_SMALL);

  // bddCreateTerminal(&mgr,"S_on",   &Son);
  // bddCreateTerminal(&mgr,"S_off",  &Soff);
  // bddCreateTerminal(&mgr,"S_set",  &Sset);
  // bddCreateTerminal(&mgr,"S_count",&Scount);
  
  // bddCreateNode(&mgr,"X_on_off",   Son, Soff,  &xOnOff);
  // bddCreateNode(&mgr,"X_count_set",Scount,Sset,&xSetCount);
  
  // tmp = bddApply(&mgr,xOnOff,xSetCount,func);
  // nodeDecRef(&mgr,xOnOff);
  // nodeDecRef(&mgr,xSetCount);
  
  // printTree(&mgr,tmp);
  
  bddDestroy(&mgr);
}