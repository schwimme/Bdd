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
  tBddNode *a, *b, *c, *d, *tmp;
  
  e = bddInit(&manager,BDD_SMALL);
  if(e) bddThrowError(e,&manager);

  e = bddCreateNode(&manager,"a",bddTrue,bddFalse,&a);    // a
  if(e) bddThrowError(e,&manager);

  e = bddCreateNode(&manager,"b",bddFalse,bddTrue,&b);    // !b priamo
  if(e) bddThrowError(e,&manager);

  e = bddCreateNode(&manager,"c",bddTrue,bddFalse,&tmp);  // c
  if(e) bddThrowError(e,&manager);
  c = bddApply(&manager,tmp,NULL,bddNeg);                 // !c pomocou apply
  nodeDecRef(&manager,tmp);
  
  e = bddCreateNode(&manager,"d",bddTrue,bddFalse,&d);    // d
  if(e) bddThrowError(e,&manager);
  
  tmp = bddApply(&manager,a,b,bddAnd);               // a * !b
  nodeDecRef(&manager,a);
  nodeDecRef(&manager,b);
  
  a = bddApply(&manager,c,d,bddAnd);                // !c * d
  nodeDecRef(&manager,c);
  nodeDecRef(&manager,d);
  
  b = bddApply(&manager,a,tmp,bddOr);               // (a * !b) + (!c * d)
  nodeDecRef(&manager,a);
  nodeDecRef(&manager,tmp);

  printNodeInfo(&manager,b->high->high);
  printNodeInfo(&manager,b->low);

  bddDestroy(&manager);
  return 0;
}