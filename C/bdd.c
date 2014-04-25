/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/


#include"bdd.h"


tError bddInit(tBddRoot * bdd,unsigned int size) {
  // allocation of necessary structs
  if(!(bdd->nodes = malloc(sizeof(tGarbage)))) return E_INIT_MALLOC;
  if(!(bdd->variables = malloc(sizeof(tLabels)))) return E_INIT_MALLOC;
  if(!(bdd->terminals = malloc(sizeof(tLabels)))) return E_INIT_MALLOC;
  
  // initialization of allocated structs
  if(nodeInit(bdd->nodes,size)) return E_GAR_MALLOC;
  labelsInit(bdd->variables);
  labelsInit(bdd->terminals);
  
  return E_OK;
}

void bddDestroy(tBddRoot * bdd){
  // free resources
  nodeDestroy(bdd->nodes);
  labelsDestroy(bdd->variables);
  labelsDestroy(bdd->terminals);
  
  // free structs
  free(bdd->variables);
  free(bdd->terminals);
  free(bdd->nodes);
}

tError bddCreateTerminal(tBddRoot * bdd, char * label, tBddNode ** result){
  unsigned int labelIndex; 
  tError e; // possible error
  
  *result = nodeGetNode(bdd->nodes); // create node
  if(!(*result)) return E_FREE_NODES;
  
  e = labelsInsert(bdd->terminals,label,&labelIndex);
  if(e) return e;
  
  (*result)->var = labelIndex;
  
  (*result)->nextFree = NULL;
  (*result)->high     = NULL;
  (*result)->low      = NULL;
  return E_OK;
}

tError bddCreateNode(tBddRoot *bdd, char *label, tBddNode *high, tBddNode *low, tBddNode **result) {
  unsigned int labelIndex; 
  tError e; // possible error
  
  *result = nodeGetNode(bdd->nodes); // create node
  if(!(*result)) return E_FREE_NODES;
  
  e = labelsInsert(bdd->terminals,label,&labelIndex);
  if(e) return e;
  
  (*result)->var = labelIndex;
  
  (*result)->nextFree = NULL;
  (*result)->high     = high;
  (*result)->low      = low;
  return E_OK;
}
