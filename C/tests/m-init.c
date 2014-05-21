/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/

#include "../bdd.h"

int main(){
  
  tManager mgr;
  bddInit(&mgr,BDD_SMALL);
  bddDestroy(&mgr);
  
  return 0;
}