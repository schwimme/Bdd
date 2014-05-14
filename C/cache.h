/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/


#ifndef  _CACHE_H_
#define _CACHE_H_

#define HSIZE 197

#include <stdlib.h>
#include "errors.h"
#include "node.h" 


typedef struct CacheItem{
  unsigned int var;
  tBddNode *high, *low, *address;
  struct CacheItem * next;
} tCacheItem;

typedef struct CacheGar{
  tCacheItem * nodes;
  struct CacheGar * next;
} tCacheGar;

typedef struct Cache {
  tCacheGar * gar;
  tCacheItem * free;
  tCacheItem ** hash;
} tCache;

tError  cacheInit(tCache **, unsigned int);
void    cacheDestroy(tCache *);

tError      cacheInsert (tCache *, tBddNode *); 
void        cacheDelete (tCache *, tBddNode *);
tBddNode *  cacheCheck  (tCache *, tBddNode *, tBddNode *, unsigned int);


#endif // _CACHE_H_