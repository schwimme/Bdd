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


void printTree(tManager * bdd, tBddNode * x){

  printNodeValue(bdd, x);  
  
  if(isTerminal(x)) return;
  
  printTree(bdd,x->low);
  printTree(bdd,x->high);
}

int main(){
  tError e;
  
  tManager manager;
  tBddNode *x,*y,*z;
  
  e = bddInit(&manager,BDD_SMALL);
  if(e) bddThrowError(e);
  
  e = bddCreateNode(&manager,"x",&x);
  if(e) bddThrowError(e);
  
  e = bddCreateNode(&manager,"x",&y);
  if(e) bddThrowError(e);
  
  e = bddCreateNode(&manager,"x",&z);
  if(e) bddThrowError(e);

  printf("%d\n",x->ref);
  printf("%p\n%p\n",(void*)x,(void*)y);

  //printTree(&manager,x);
  //printTree(&manager,y);

  
  bddDestroy(&manager);
  return 0;
}