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
  tBddNode *x,*y,*z;
  
  e = bddInit(&manager,BDD_SMALL);
  if(e) bddThrowError(e);
  
  e = bddCreateNode(&manager,"x1",&x);
  if(e) bddThrowError(e);
  
  
  e = bddCreateNode(&manager,"x2",&y);
  if(e) bddThrowError(e);
  
  
  z = apply(&manager,x,y,&bddOr);
  if(e) bddThrowError(e);
  
  
  e = bddCreateNode(&manager,"x3",&y);
  if(e) bddThrowError(e);
  
  
  x = apply(&manager,z,y,&bddXor);
  
  printTree(&manager,x);

  

  bddDestroy(&manager);
  return 0;
}