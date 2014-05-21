/**************************/
/**       xtrosk00       **/
/**   Bachelors Thesis   **/
/**     A BDD Library    **/
/**************************/

#include "measurement.h"
#include <stdio.h>

struct timeval begin;
struct timeval end;
struct timeval diff;

void timeDiff() {
  long int d = (end.tv_usec + 1000000 * end.tv_sec) - (begin.tv_usec + 1000000 * begin.tv_sec);
  diff.tv_sec = d / 1000000;
  diff.tv_usec = d % 1000000;
}

void timePrint(struct timeval *tv) {
  char buffer[30];
  time_t curtime;

  curtime = tv->tv_sec;
  strftime(buffer, 30, "%m-%d-%Y  %T", localtime(&curtime));
  printf("%s.%06ld\n", buffer, tv->tv_usec);
}


void measurementStart(){
  gettimeofday(&begin, NULL);
  printf("Measurment begin at ");
  timePrint(&begin);
}

void measurementEnd(){
  gettimeofday(&end, NULL);
  printf("Measurment ends at  ");
  timePrint(&end);
}
void measurementDiff(){
  printf("Total time          ");
  timeDiff();
  printf("%ld.%06ld\n", diff.tv_sec, diff.tv_usec);
}