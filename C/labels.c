/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/

#include"labels.h"

tError labelsInit(tLabels **l){
  if(!(*l = malloc(sizeof(tLabels)))) return E_INIT_MALLOC;
  (*l)->lab = NULL;
  (*l)->count = 0;
  
  return E_OK;
}

tError labelsInsert(tLabels *l, char * label, unsigned int * position) {
  
  for(unsigned int i = 0; i < l->count; i++){ // check all labels
    if(!strcmp(label,l->lab[i])) { // if label exist yet, return position
      *position = i;
      return E_OK;
    }
  }
  // create new label
  *position = l->count++; 
  
  // new position for label
  if(!(l->lab = realloc(l->lab,l->count*sizeof(char *)))) return E_LAB_MALLOC;

  l->lab[l->count-1] = label;
  return E_OK;
}

void labelsDestroy(tLabels *l){
  free(l->lab);
  free(l);
}