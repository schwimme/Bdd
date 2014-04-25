/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/

#include"node.h"

unsigned int LIST_END;

tError nodeInit(tGarbage * gar,unsigned int size){
  if(!(gar->nodes = malloc(sizeof(tBddNode)*size))) return E_GAR_MALLOC;
  gar->free = gar->nodes;
  for(unsigned int i = 0; i < size-1; i++)
    gar->free[i].nextFree = &(gar->free[i+1]);
 
  gar->free[size-1].nextFree = NULL;
  return E_OK;
}

void nodeDestroy(tGarbage * gar) {
  free(gar->nodes);
}

void nodeIncRef(tBddNode * node){
  node->ref++;
}

void nodeDecRef(tBddNode * node){
  node->ref--;
}

tBddNode * nodeGetNode(tGarbage * gar) {
  tBddNode * result = gar->free;
  nodeIncRef(result);
  gar->free = gar->free->nextFree;
  return result;
}

void nodeFreeNode(tGarbage * gar, tBddNode * node) {
  tBddNode * ptr = gar->free;
  gar->free = node;
  node->nextFree = ptr;
}
