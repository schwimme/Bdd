/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/

#ifndef _ERRORS_H_
#define _ERRORS_H_

#include<stdio.h>

typedef enum Error {
  E_OK = 0,
  E_INIT_MALLOC,
  E_GAR_MALLOC,
  E_LAB_MALLOC,
  E_FREE_NODES,
  E_CACHE_MALLOC
} tError;

#define bddThrowError(E,bdd){\
  fprintf(stderr,"%s\n",ERRORS[E-1]);\
  bddDestroy(bdd);\
  return 1;\
}

extern const char * ERRORS[];

#endif // _ERRORS_H_