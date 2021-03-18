#ifndef MYSORT_H_
#define MYSORT_H_

#include "repository.h"
/*
	return 0 if equal, 1 if o1>o2, -1 otherwise
*/
typedef int(*ComparingFunction)(Drug* o1, Drug* o2);

int cmpName(Drug* d1, Drug* d2);
int cmpQuantity(Drug* d1, Drug* d2);
void sort(MyList* l, ComparingFunction cmpf, int direction);
void testSort();

#endif

