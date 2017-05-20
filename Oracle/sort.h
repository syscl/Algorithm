
#ifndef __SORT_H__
#define __SORT_H__

#include "syscl_lib.h"

//
// sort function proto declare here
//
char *sort(char *);
void quicksort(char *str, int, int);
int  part(char *, int, int); 
void exchange(char *, char *);

#endif