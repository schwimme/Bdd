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
  bddInit(&mgr,BDD_SMALL);
  bddDestroy(&mgr);

  // </CODE>

  measurementEnd();
  measurementDiff();
  
  return 0;
}