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
  tBddNode *a;
  
  e = bddInit(&manager,BDD_SMALL);
  if(e) bddThrowError(e);
  
  
  /* Create a */
  e = bddCreateNode(&manager,"a",&a);
  if(e) bddThrowError(e);
  
  a = apply(&manager,a,NULL,&bddNeg);
  
  printTree(&manager,a);

  

  bddDestroy(&manager);
  return 0;
}