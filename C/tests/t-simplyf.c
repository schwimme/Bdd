/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/

#include "../bdd.h"
#include "../measurement.h"

int main(){
  measurementStart();
  // <CODE>
  
  tManager mgr;
  tBddNode *a,*b,*c,*d,*e;
  bddInit(&mgr,BDD_SMALL);
  
  bddCreateNode(&mgr,"a",bddTrue, bddFalse, &a);  // a
  bddCreateNode(&mgr,"b",bddFalse, bddTrue, &b);  // !b

  d = bddApply(&mgr,a,b,bddAnd);                  // (a * !b) 
  bddCreateNode(&mgr,"c",bddFalse, bddTrue, &c);  // !c
  
  e = bddApply(&mgr,d,c,bddAnd);                  // (a * !b * !c)
  nodeDecRef(&mgr,d);
  nodeDecRef(&mgr,c);
  
  d = bddApply(&mgr,a,NULL,bddNeg);               // !a
  nodeDecRef(&mgr,a);
  
  c = bddApply(&mgr,b,NULL,bddNeg);               // !(!b) = b
  nodeDecRef(&mgr,b);
  
  b = bddApply(&mgr,c,d,bddAnd);                  //  (!a * b)
  nodeDecRef(&mgr,c);
  nodeDecRef(&mgr,d);
  
  d = bddApply(&mgr,e,b,bddOr);
  // </CODE>
  measurementEnd();
  measurementDiff();
  
  return 0;
}