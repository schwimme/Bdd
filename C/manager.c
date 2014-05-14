/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/


#include"manager.h"

// extern variables
tBddNode * bddTrue;
tBddNode * bddFalse;

tError bddInit(tManager * bdd,unsigned int size) {

  // initialization of allocated structs
  if(nodeInit(&(bdd->nodes),size)) return E_GAR_MALLOC;
  if(labelsInit(&(bdd->variables))) return E_INIT_MALLOC;
  if(labelsInit(&(bdd->terminals))) return E_INIT_MALLOC;
  if(cacheInit(&(bdd->cache),128)) return E_CACHE_MALLOC;
  // set free nodes
  bdd->free = &(bdd->nodes->nodes[0]);
  
  // create first terminals
  if(bddCreateTerminal(bdd,"false",&bddFalse)) return E_FREE_NODES;
  if(bddCreateTerminal(bdd,"true",&bddTrue)) return E_FREE_NODES;
  
  // init cache
  return E_OK;
}

void bddDestroy(tManager * bdd){
  // free resources
  nodeDestroy(bdd->nodes);
  labelsDestroy(bdd->variables);
  labelsDestroy(bdd->terminals);
  cacheDestroy(bdd->cache);
}



tBddNode * bddGetNode(tManager * bdd) {
  tBddNode * res = bdd->free; 
  bdd->free = bdd->free->nextFree;
  
  // if you're out of free nodes try allocate new block of garbage
  if(!bdd->free){
    tGarbage * gar;
    nodeInit(&gar,BDD_SMALL);

    gar->next = bdd->nodes;
    bdd->nodes = gar;

    // set new free nodes
    bdd->free = &(gar->nodes[0]);
  }
  return res;
}

tError bddCreateTerminal(tManager * bdd, char * label, tBddNode ** result){
  unsigned int labelIndex; 
  tError e; // possible error
  
  *result = bddGetNode(bdd); // create terminal
  if(!(*result)) return E_FREE_NODES;
  
  // set node values
  e = labelsInsert(bdd->terminals,label,&labelIndex);
  if(e) return e;
  
  (*result)->var = labelIndex;
  
  (*result)->nextFree = NULL;
  (*result)->high     = NULL;
  (*result)->low      = NULL;
  return E_OK;
}

tError bddNewNode(tManager *bdd, unsigned int label, tBddNode * high,tBddNode *low,tBddNode **result) {
  
  *result = bddGetNode(bdd); // create node
  if(!(*result)) return E_FREE_NODES;
  
  
  (*result)->var = label;
  (*result)->high = high;
  (*result)->low = low;
  (*result)->ref = 1;
  (*result)->nextFree = NULL;
  
  return E_OK;
}

tError bddCreateNode(tManager *bdd, char *label, tBddNode * high,tBddNode *low,tBddNode **result) {
  // node exist already
  tError e;
  unsigned int labelIndex;
  e = labelsInsert(bdd->variables,label,&labelIndex);
  if(e) return e;
  
  *result = cacheCheck  (bdd->cache,high, low, labelIndex);
  if(*result) return E_OK;
  
  if(bddNewNode(bdd,labelIndex,high,low,result)) return E_FREE_NODES;
  
  e = cacheInsert(bdd->cache,*result);
  if(e) return e;
  
  return E_OK;
}
void printNodeValue(tManager *bdd,tBddNode *x) {
  if(isTerminal(x)) 
    printf("%s\n",bdd->terminals->lab[x->var]);
  else 
    printf("%s\n",bdd->variables->lab[x->var]);
}

void printTree(tManager * bdd, tBddNode * x){

  printNodeValue(bdd, x);  
  if(isTerminal(x)) return;

  for(unsigned int i = 0;i<=x->var;i++)
    printf(" ");
  printf("+ ");
  printTree(bdd,x->high);
  
  
  for(unsigned int i = 0;i<=x->var;i++)
    printf(" ");
  printf("- ");
  printTree(bdd,x->low);
}


void printNodeInfo(tManager *bdd, tBddNode *node){
  if(isTerminal(node)){
    printf("Address:\t%p\n",(void*)node);
    printf("Terminal:\t"); printNodeValue(bdd,node);
  } else if(!(node->nextFree)){
    printf("Address:\t%p\n",(void*)node);
    printf("Node:\t"); printNodeValue(bdd,node);
    printf("Order:\t%d\n",node->var);
    printf("Ref:\t%d\n",node->ref);
    printf("High:\t");printNodeValue(bdd,node->high);
    printf("Low:\t");printNodeValue(bdd,node->low);
  } else {
    printf("Node is not in use\n");
  }
}


void nodeIncRef(tBddNode * node){
  node->ref++;
}

void nodeFree(tManager *bdd, tBddNode * node) {
  // insert node back to manager
  tBddNode * tmp = bdd->free;
  bdd->free = node;
  node->nextFree = tmp;
}

void nodeDecRef(tManager *bdd, tBddNode * node){
  node->ref--;
  // if ref == 0, set node free and decrement successors
  if(node->ref == 0) {
    if(!isTerminal(node->high)) nodeDecRef(bdd,node->high);
    if(!isTerminal(node->low))  nodeDecRef(bdd,node->low);
    nodeFree(bdd,node);
    cacheDelete(bdd->cache,node);
  }
}


