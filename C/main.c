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
  tBddNode * a, * b, *tmp;
  
  e = bddInit(&manager,BDD_SMALL);
  if(e) bddThrowError(e,&manager);

  e = bddCreateNode(&manager,"a",bddTrue,bddFalse,&a);
  if(e) bddThrowError(e,&manager);

  e = bddCreateNode(&manager,"b",bddTrue,bddFalse,&b);
  if(e) bddThrowError(e,&manager);
  
  tmp = bddApply(&manager,a,b,bddAnd);
  
  printTree(&manager,tmp);

  bddDestroy(&manager);
  return 0;
}