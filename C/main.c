/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/

/*
  f(x1,x2,x3) = x1*x2 + x2*!x3
*/
#include"bdd.h"

int main(){
  tError e;     // zachytavanie chybovych stavov

  tManager mgr; // bdd manager
  tBddNode *x1, *x2, *x3; // premenne x1, x2 a x3
  tBddNode *tmp;          // pomocny ukazatel
  e = bddInit(&mgr,BDD_SMALL); // inicializacia managera na velkost bdd_small 
  if(e) bddThrowError(e,&mgr);

  
  // vytvorenie uzlov pre premenne x1 x2 a x3
  // bddCreateNode(manager,label premennej, vysoky naslednik, nizky naslednik, vystup)
  e = bddCreateNode(&mgr,"x1",bddTrue,bddFalse,&x1); 
  if(e) bddThrowError(e,&mgr);
  e = bddCreateNode(&mgr,"x2",bddTrue,bddFalse,&x2);
  if(e) bddThrowError(e,&mgr);
  e = bddCreateNode(&mgr,"x3",bddTrue,bddFalse,&x3);
  if(e) bddThrowError(e,&mgr);
  
  tmp = bddApply(&mgr,x1,x2,bddAnd);  // x1*x2
  nodeDecRef(&mgr,x1); // uzol x1 uz nepotrebujeme
  
  x1 = bddApply(&mgr,x3,NULL,bddNeg); // !x3
  nodeDecRef(&mgr,x3); // uzol x3 uz nepotrebujeme
  
  x3 = bddApply(&mgr,x2,x1,bddAnd);  // x2*!x3
  nodeDecRef(&mgr,x1); // uzol !x3 uz nepotrebujeme
  nodeDecRef(&mgr,x2); // uzol x2 uz nepotrebujeme
  
  x1 = bddApply(&mgr,tmp,x3,bddOr);  // x1*x2 + x2*!x3
  
  printTree(&mgr,x1);
  
  
  bddDestroy(&mgr);
}