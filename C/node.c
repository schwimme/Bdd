/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/

#include"node.h"

tError nodeGetBlock(tGarbage * gar, unsigned int size, tBddNode ** free) {
  tGarbage * iterator = gar;
  while(iterator->next != NULL) iterator = iterator->next;
  
  if(nodeInit(&(iterator->next),size)) return E_GAR_MALLOC;
  *free = &(iterator->nodes[0]);
  return E_OK;
}

tError nodeInit(tGarbage ** gar,unsigned int size){
  if(!(*gar = malloc(sizeof(tGarbage)))) return E_INIT_MALLOC;

  if(!((*gar)->nodes = malloc(sizeof(tBddNode)*size))) return E_GAR_MALLOC;


  for(unsigned int i = 0; i < size-1; i++)
    (*gar)->nodes[i].nextFree = &((*gar)->nodes[i+1]);

  (*gar)->nodes[size-1].nextFree = NULL;
  
  (*gar)->next = NULL;
  return E_OK;
}

void nodeDestroy(tGarbage * gar) {
  tGarbage * iterator = gar, *tmp;
  while(iterator != NULL) { 
    tmp = iterator;
    iterator = iterator->next;
    free(tmp->nodes);
    free(tmp);
  }

}

void nodeIncRef(tBddNode * node){
  node->ref++;
}

void nodeDecRef(tBddNode * node){
  node->ref--;
}

