/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/

/*
  Modul:    head - test file
*/
#include"bdd.h"
#include<stdio.h>


int main(){
  tManager manager;
  tBddNode *false,*true,*x;
  tError e;
  e = bddInit(&manager,BDD_SMALL);
  if(e) bddThrowError(e);
  
  e = bddCreateTerminal(&manager,"false",&false);
  if(e) bddThrowError(e);

  e = bddCreateTerminal(&manager,"true",&true);
  if(e) bddThrowError(e);
  
  e = bddCreateNode(&manager,"x",true,false,&x);
  if(e) bddThrowError(e);

  bddDestroy(&manager);
  return 0;
}