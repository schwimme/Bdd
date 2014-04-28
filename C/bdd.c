/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/


#include"bdd.h"


tError bddInit(tManager * bdd,unsigned int size) {

  // initialization of allocated structs
  if(nodeInit(&(bdd->nodes),size)) return E_GAR_MALLOC;
  if(labelsInit(&(bdd->variables))) return E_INIT_MALLOC;
  if(labelsInit(&(bdd->terminals))) return E_INIT_MALLOC;
  
  bdd->free = &(bdd->nodes->nodes[0]);
  return E_OK;
}

void bddDestroy(tManager * bdd){
  // free resources
  nodeDestroy(bdd->nodes);
  labelsDestroy(bdd->variables);
  labelsDestroy(bdd->terminals);
  
}

tBddNode * bddGetNode(tManager * bdd) {
  tBddNode * res = bdd->free;
  bdd->free = bdd->free->nextFree;
  
  // ToDo
  return res;
}

tError bddCreateTerminal(tManager * bdd, char * label, tBddNode ** result){
  unsigned int labelIndex; 
  tError e; // possible error
  
  *result = bddGetNode(bdd); // create node
  if(!(*result)) return E_FREE_NODES;
  
  e = labelsInsert(bdd->terminals,label,&labelIndex);
  if(e) return e;
  
  (*result)->var = labelIndex;
  
  (*result)->nextFree = NULL;
  (*result)->high     = NULL;
  (*result)->low      = NULL;
  return E_OK;
}

tError bddCreateNode(tManager *bdd, char *label, tBddNode *high, tBddNode *low, tBddNode **result) {
  unsigned int labelIndex; 
  tError e; // possible error
  
  *result = bddGetNode(bdd); // create node
  if(!(*result)) return E_FREE_NODES;
  
  e = labelsInsert(bdd->terminals,label,&labelIndex);
  if(e) return e;
  
  (*result)->var = labelIndex;
  
  (*result)->nextFree = NULL;
  (*result)->high     = high;
  (*result)->low      = low;
  return E_OK;
}
