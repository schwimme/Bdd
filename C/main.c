/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/

/*
  Modul:    head - test file
*/
#include"bdd.h"



int main(){
  tError e;
  
  tManager manager;
  tBddNode *a,*b;
  
  e = bddInit(&manager,BDD_SMALL);
  if(e) bddThrowError(e);
  
  
  e = bddCreateNode(&manager,"a",&a);
  if(e) bddThrowError(e);
  a = apply(&manager,a,NULL,bddNeg);
  
  e = bddCreateNode(&manager,"b",&b);
  if(e) bddThrowError(e);
  b = apply(&manager,b,NULL,bddNeg);
  
  a = apply(&manager,a,b,bddAnd);
  printTree(&manager,a);

  bddDestroy(&manager);
  return 0;
}