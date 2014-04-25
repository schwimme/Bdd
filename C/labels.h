/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/

/*
  Modul:      labels
  
  Interface:
    struct Labels (tLabels)
      char **       lab
      unsigned int  count
      
    void labelsInit(tLabels *);
    tError labelsInsert(tLabels *, char *, int *);
    void labelsDestroy(tLabels *);
*/

#ifndef _LABELS_H_
#define _LABELS_H_

#include<string.h> /* because of strcmp() */
#include<stdlib.h> /* because of realloc()*/


#include"errors.h"

typedef struct Labels{
  char **       lab;   // table of strings
  unsigned int  count; // number of strings
}tLabels;

/**
 * labels initialization, sets lab to NULL and count to 0
 * 1. param -> labels for initialization
 */
void labelsInit(tLabels *);

/**
 * free all labels in lab
 * 1. param -> labels for destroy
 */
void labelsDestroy(tLabels *);

/**
 * insert new label and return his position
 * 1. param -> where will be added
 * 2. param -> what  will be added
 * 3. param -> return position
 * returns  -> E_OK iff success
 */
tError labelsInsert(tLabels *, char *, unsigned int *);


#endif // _LABELS_H_