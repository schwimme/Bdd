#include"cache.h"

unsigned int cacheHash(tBddNode * high, tBddNode * low, unsigned int var){
  unsigned int res;
  if(high == low) res = var;
  else res = var + 5;
  return res % HSIZE;
}

tError cacheGarInit( tCacheGar ** new, unsigned int size){
  // garbage
  if(!((*new) = malloc(sizeof(tCacheGar)))) return E_CACHE_MALLOC; 
  
  // nodes in garbage
  if(!((*new)->nodes = calloc(sizeof(tCacheItem),size))) return E_CACHE_MALLOC;
  
  // connect like list
  for(unsigned int i = 0; i<size;i++){
    (*new)->nodes[i].next = &((*new)->nodes[i+1]);
  }
  // last is null
  (*new)->nodes[size-1].next = NULL;
  return E_OK;
  
}

tError cacheInit(tCache **c, unsigned int size) {
  // cache struct
  if(!((*c) = malloc(sizeof(tCache)))) return E_CACHE_MALLOC;
  // hash table
  if(!((*c)->hash = calloc(sizeof(tCacheItem*),HSIZE))) return E_CACHE_MALLOC;
  // garbage
  if(cacheGarInit(&((*c)->gar),size)) return E_CACHE_MALLOC;
  
  // connect garbage like list 
  (*c)->gar->next = NULL;

  // set free nodes
  (*c)->free = &((*c)->gar->nodes[0]);
  
  return E_OK;
}

void cacheDestroy(tCache * c){
  // through all garbages
  for(tCacheGar * iterator = c->gar; iterator != NULL; iterator = c->gar){
    free(iterator->nodes);
    c->gar = c->gar->next;
    free(iterator);
  }
  free(c->hash);
  free(c);
}

tError cacheInsert(tCache * c, tBddNode * node) {
  if(!c->free) { // if cache is full allocate new garbage and add in list
    tCacheGar * new;
    if(cacheGarInit(&new,64)) return E_CACHE_MALLOC;
      c->free = &(new->nodes[0]);
      new->next = c->gar;
      c->gar = new;
  }
  
  // new cache record
  tCacheItem * rec = c->free;
  c->free = c->free->next;

  // values
  rec->high = node->high;
  rec->low  = node->low;
  rec->var  = node->var;
  rec->address = node;

  // insert in hash table
  unsigned int index = cacheHash(node->high, node->low, node->var);
  rec->next = c->hash[index];
  c->hash[index] = rec;
  
  return E_OK;  
}

tBddNode * cacheCheck(tCache * c, tBddNode * high, tBddNode * low, unsigned int var) {
  // get index
  unsigned int index = cacheHash(high,low,var);
  
  tCacheItem * iterator = c->hash[index];
  while(iterator != NULL) {
    if(iterator->high == high &&
       iterator->low  == low  &&
       iterator->var  == var) {
        return iterator->address; // record exists
    }
    iterator = iterator->next;
  }
  return NULL; // record not exist
}

void cacheDelete(tCache * c, tBddNode * node){
  unsigned int index = cacheHash(node->high,node->low,node->var);
  if(!c->hash[index]) return;
  tCacheItem * first = c->hash[index]->next;
  tCacheItem * second = c->hash[index];
  
  if(node == second->address){ // first record
    c->hash[index] = second->next;
    // add to free list
    second->next=c->free;
    c->free = second;
    return;
  } else {
    while(first != NULL) { // it isn't first record
      if(first->address == node){ // check current
        second->next = first->next;
        // add to free list
        first->next = c->free;
        c->free = first;
        return;
      }
      first = first->next; // succ current and carriage
      second = second->next;
    }
  }
}
