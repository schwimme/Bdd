/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/

#include"bdd.h"

tBddNode * _apply(tManager *bdd, tBddNode *x, tBddNode *y,tBddNode*(*func)(tBddNode *, tBddNode *)) {
  tBddNode * result;
  tBddNode *xh,*xl,*yh,*yl;
  tBddNode * high, *low;
  unsigned int var;
  if(isTerminal(x) && isTerminal(y)){ // both are terminals, run func
    result = func(x,y);
    return result;
  } else if(isTerminal(x)) { // only x is terminal
    var = y->var;
    xh = x; xl = x;
    yh = y->high; yl = y->low;
  } else if(isTerminal(y)) { // only y is terminal
    var = x->var;
    xh = x->high; xl = x->low;
    yh = y; yl = y;
  } else { // anyone is not terminals
    if(x->var == y->var){ // labels are equal
      var = x->var;
      xh = x->high; xl = x->low;
      yh = y->high; yl = y->low;
    } else if(x->var < y->var) { // x is over y
      var = x->var;
      xh = x->high; xl = x->low;
      yh = y; yl = y;
    } else { // y is over x
      var = y->var;
      xh = x; xl = x;
      yh = y->high; yl = y->low;
    }
  }
  
  high = _apply(bdd,xh,yh,func);
  low = _apply(bdd,xl,yl,func);
  
  
  if(high == low){ 
    return low;
  } else {
    tBddNode * cached = cacheCheck(bdd->cache,high,low,var);
    if(cached){
      nodeIncRef(cached);
      return cached;
    } else {
      bddNewNode(bdd,var,high,low,&result);
      cacheInsert(bdd->cache,result);
      return result;
    }
  }
}


tBddNode * bddApply(tManager *bdd, tBddNode *x, tBddNode *y, tBddNode*(*func)()) {
  tBddNode * result;

  if(func == bddNeg) {
    result = _apply(bdd,x,x,bddNand);
  }else { 
    result = _apply(bdd,x,y,func);
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

tBddNode * bddImp(tBddNode *x,tBddNode*y){
  if(x == bddTrue && y == bddFalse) return bddFalse;
  return bddTrue;
}
