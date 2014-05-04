/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/

/*
  Modul:      errors
  
  Interface:
    enum Error (tError)
      E_OK = 0
      E_INIT_MALLOC
      E_GAR_MALLOC
      E_LAB_MALLOC
      E_FREE_NODES

    const char * ERRORS[]
      
    bddThrowError(tError)
*/
#ifndef _ERRORS_H_
#define _ERRORS_H_

#include<stdio.h>

typedef enum Error {
  E_OK = 0,
  E_INIT_MALLOC,
  E_GAR_MALLOC,
  E_LAB_MALLOC,
  E_FREE_NODES,
  E_MALLOC_CACHE
} tError;

/**
 * Exit failure with display current error
 * 1. param -> error code
 */
#define bddThrowError(E){\
  fprintf(stderr,"%s\n",ERRORS[E-1]);\
}

/**
 * persist strings of all errors
 */
extern const char * ERRORS[];

#endif // _ERRORS_H_