/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/


#include"bdd.h"

tBddNode * bddTrue;
tBddNode * bddFalse;

tError bddInit(tManager * bdd,unsigned int size) {

  // initialization of allocated structs
  if(nodeInit(&(bdd->nodes),size)) return E_GAR_MALLOC;
  if(labelsInit(&(bdd->variables))) return E_INIT_MALLOC;
  if(labelsInit(&(bdd->terminals))) return E_INIT_MALLOC;
  
  bdd->free = &(bdd->nodes->nodes[0]);
  
  if(bddCreateTerminal(bdd,"true",&bddTrue)) return E_FREE_NODES;
  if(bddCreateTerminal(bdd,"false",&bddFalse)) return E_FREE_NODES;
  
  bdd->cache = NULL;
  return E_OK;
}

void bddDestroy(tManager * bdd){
  // free resources
  nodeDestroy(bdd->nodes);
  labelsDestroy(bdd->variables);
  labelsDestroy(bdd->terminals);
  tCache * tmp;
  
  for(tCache * iterator = bdd->cache;iterator != NULL; iterator=tmp){
    tmp = iterator->next;
    free(iterator);
  }
}


tError cacheCheck(tManager * bdd,tBddNode ** node){
  for(tCache * iterator = bdd->cache;iterator != NULL; iterator=iterator->next){
    if(iterator->record->var == (*node)->var &&
       iterator->record->high == (*node)->high &&
       iterator->record->low == (*node)->low){
         nodeDecRef(bdd,*node);
         (*node) = iterator->record;
         nodeIncRef(*node);
         return E_OK;
       }
  }
  
 
  tCache * tmp = malloc(sizeof(tCache));
  if(!tmp) return E_MALLOC_CACHE;
  
  tmp->record = *node;
  
  tmp->next = bdd->cache;
  bdd->cache = tmp;
  
  return E_OK; 
}


tBddNode * bddGetNode(tManager * bdd) {
  tBddNode * res = bdd->free;
  bdd->free = bdd->free->nextFree;
  
  // ToDo if you're out of free nodes realloc
  
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

tError bddCreateNode(tManager *bdd, char *label, tBddNode **result) {
  unsigned int labelIndex; 
  tError e; // possible error
  
  *result = bddGetNode(bdd); // create node
  if(!(*result)) return E_FREE_NODES;
  
  e = labelsInsert(bdd->variables,label,&labelIndex);
  if(e) return e;
  
  (*result)->var = labelIndex;
  (*result)->high     = bddTrue;
  (*result)->low      = bddFalse;
  (*result)->ref = 1;

  e = cacheCheck(bdd,result);
  if(e) return(e);
  
  (*result)->nextFree = NULL;
  
  return E_OK;
}

void printNodeValue(tManager *bdd,tBddNode *x) {
  if(isTerminal(x)) 
    printf("%s\n",bdd->terminals->lab[x->var]);
  else 
    printf("%s\n",bdd->variables->lab[x->var]);
}


void nodeIncRef(tBddNode * node){
  node->ref++;
}

void nodeFree(tManager *bdd, tBddNode * node) {
  tBddNode * tmp = bdd->free;
  bdd->free = node;
  node->nextFree = tmp;
}

void nodeDecRef(tManager *bdd, tBddNode * node){
  node->ref--;
  if(node->ref == 0) {
    if(!isTerminal(node->high)) nodeDecRef(bdd,node->high);
    if(!isTerminal(node->low))  nodeDecRef(bdd,node->low);
    nodeFree(bdd,node);
  }
}

