/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/

#include"bdd.h"

tBddNode * _apply(tManager *bdd, tBddNode *x, tBddNode *y,tBddNode*(*func)()) {
  tBddNode * result;
  tBddNode *xh,*xl,*yh,*yl;
  if(isTerminal(x) && isTerminal(y)){ // both are terminals, run func
    result = func(x,y);
    return result;

  } else if(isTerminal(x)) { // only x is terminal
    bddNewNode(bdd,bdd->variables->lab[y->var],&result);
    xh = x; xl = x;
    yh = y->high; yl = y->low;
  } else if(isTerminal(y)) { // only y is terminal
    bddNewNode(bdd,bdd->variables->lab[x->var],&result);
    xh = x->high; xl = x->low;
    yh = y; yl = y;
  } else { // anyone is not terminals
    if(x->var == y->var){ // labels are equal
      bddNewNode(bdd,bdd->variables->lab[x->var],&result);
      xh = x->high; xl = x->low;
      yh = y->high; yl = y->low;
    } else if(x->var < y->var) { // x is over y
      bddNewNode(bdd,bdd->variables->lab[x->var],&result);
      xh = x->high; xl = x->low;
      yh = y; yl = y;
    } else { // y is over x
      bddNewNode(bdd,bdd->variables->lab[y->var],&result);
      xh = x; xl = x;
      yh = y->high; yl = y->low;
    }
  }
  
  result->high = _apply(bdd,xh,yh,func);
  result->low = _apply(bdd,xl,yl,func);
  if(result->high == result->low) result = result->low;
  
  tBddNode * cached = cacheCheck(bdd,result);
  if(cached){
    nodeDecRef(bdd,result);
    result = cached;
  } else {
    cacheInsert(bdd,result);
  }
  return result;
}


tBddNode * apply(tManager *bdd, tBddNode *x, tBddNode *y, tBddNode*(*func)()) {
  tBddNode * result;
  if(func == bddNeg) {
    y = x;
    result = _apply(bdd,x,y,bddNand);
    nodeDecRef(bdd,x);
  }else { 
    result = _apply(bdd,x,y,func);
    nodeDecRef(bdd,x);
    nodeDecRef(bdd,y);
  }
  return result;
}





////////////////////////////////////////////////////
tBddNode * bddNeg(tBddNode *x,tBddNode*y) {
  if(x==y) return NULL; // stupid code because of [-Wunused-parameter]
  return NULL;
}
tBddNode * bddOr(tBddNode *x,tBddNode*y){
  if(x == bddTrue || y == bddTrue) return bddTrue;
  return bddFalse;
}
tBddNode * bddNor(tBddNode *x,tBddNode*y){
  if(x == bddTrue || y == bddTrue) return bddFalse;
  return bddTrue;
}
tBddNode * bddAnd(tBddNode *x,tBddNode*y){
  if(x == bddTrue && y == bddTrue) return bddTrue;
  return bddFalse;
}
tBddNode * bddNand(tBddNode *x,tBddNode*y){
  if(x == bddTrue && y == bddTrue) return bddFalse;
  return bddTrue;
}

tBddNode * bddXor(tBddNode *x,tBddNode*y){
  if(x == y) return bddFalse;
  return bddTrue;
}
