/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/

#include"node.h"


tError nodeInit(tGarbage ** gar,unsigned int size){
  if(!(*gar = malloc(sizeof(tGarbage)))) return E_INIT_MALLOC;

  // clearing malloc of nodes
  if(!((*gar)->nodes = calloc(size,sizeof(tBddNode)))) return E_GAR_MALLOC;


  // list of free nodes
  for(unsigned int i = 0; i < size-1; i++)
    (*gar)->nodes[i].nextFree = &((*gar)->nodes[i+1]);

  // set last node to end of list
  (*gar)->nodes[size-1].nextFree = NULL;
  
  // you are last garbage
  (*gar)->next = NULL;
  return E_OK;
}

void nodeDestroy(tGarbage * gar) {
  tGarbage * iterator = gar, *tmp;
  
  // through all pieces of garbage free nodes and self
  while(iterator != NULL) { 
    tmp = iterator;
    iterator = iterator->next;
    free(tmp->nodes);
    free(tmp);
  }

}


