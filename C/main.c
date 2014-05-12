/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/

/*
  Modul:    head - test file
*/
#include"bdd.h"

tBddNode * Soff;
tBddNode * Sset;
tBddNode * Scount;

tBddNode * func(tBddNode * x, tBddNode * y) {
  if(x == y) return x;
  if(x == Soff || y == Soff) return Soff;
  return Scount;
}

int main(){
  tError e;
  tManager manager;
  tBddNode *a,*b,*c;

  e = bddInit(&manager,BDD_SMALL);
  if(e) bddThrowError(e);
  
  bddCreateTerminal(&manager,"S_off",&Soff);
  bddCreateTerminal(&manager,"S_set",&Sset);
  bddCreateTerminal(&manager,"S_count",&Scount);
  
  mtbddCreateNode(&manager,"X_on_off",Sset,Soff,&a);
  mtbddCreateNode(&manager,"X_set_count",Sset,Scount,&b);

  c = bddApply(&manager,a,b,func);
  // bddCreateNode(&manager,"A",&a);       // A
  // bddCreateNode(&manager,"B",&b);       // B
  // a = bddApply(&manager,a,b,bddAnd);    // (A * B)



  printTree(&manager,c);

  bddDestroy(&manager);
  return 0;
}