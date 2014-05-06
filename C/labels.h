/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/


#ifndef _LABELS_H_
#define _LABELS_H_

#include<string.h> /* because of strcmp() */
#include<stdlib.h> /* because of realloc()*/


#include"errors.h"

typedef struct Labels{
  char **       lab;   // table of strings
  unsigned int  count; // number of strings
}tLabels;


tError labelsInit(tLabels **);
void labelsDestroy(tLabels *);

tError labelsInsert(tLabels *, char *, unsigned int *);


#endif // _LABELS_H_