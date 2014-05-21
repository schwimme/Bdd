/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/

#include "../bdd.h"
#include "../measurement.h"


char * names[33] = {
"x1","x2"  ,"x3" ,"x4" ,"x5" ,"x6" ,"x7" ,"x8",
"x9","x10" ,"x11","x12","x13","x14","x15","x16",
"x17","x18","x19","x20","x21","x22","x23","x24",
"x25","x26","x27","x28","x29","x30","x31","x32",
"x33"
};

int main(){
  measurementStart();
  
  // <CODE>
  tManager mgr;
  tBddNode *x_i,*f,*tmp;
  
  bddInit(&mgr,16);
  
  bddCreateNode(&mgr,names[0],bddTrue,bddFalse,&f);
  
  for(int i = 1; i < 33 ; i++){
    bddCreateNode(&mgr,names[i],bddTrue,bddFalse,&x_i);
    tmp = bddApply(&mgr,f,x_i,bddOr);
    nodeDecRef(&mgr,x_i);
    nodeDecRef(&mgr,f);
    f = tmp;
  }
  bddDestroy(&mgr);

  // </CODE>
  
  measurementEnd();

  measurementDiff();
  
  return 0;
}