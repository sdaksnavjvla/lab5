#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mysort.h"
#include "repository.h"

int cmpName(Drug* d1, Drug* d2)
{
	/*
		compare by name
	*/
	return strcmp(d1->name, d2->name);
}

int cmpQuantity(Drug* d1, Drug* d2)
{
	/*
		compare by quantity
	*/
	if (d1->quantity == d2->quantity)
		return 0;
	else
		if (d1->quantity < d2->quantity)
			return -1;
		else
			return 1;
}

void sort(MyList* l, ComparingFunction cmpf, int direction) 
{	
	/*
		Sort in place
		cmpf - comparing relation
		direction can be 1 for ascending and -1 for descending
	*/
	for (int i = 0; i < getSizeDrugs(l); i++) 
	{
		for (int j = i + 1; j < getSizeDrugs(l); j++)
		{
			Drug p1 = getDrug(l, i);
			Drug p2 = getDrug(l, j);
			if (cmpf(&p1, &p2) == direction) 
			{
				setDrug(l, i, p2);
				setDrug(l, j, p1);
			}
		}
	}
}

void testSort()
{
	MyList* l = createEmpty();
	assert(addDrug(l, createDrug(1, "ospamox", 200, 10)) == 1);
	assert(addDrug(l, createDrug(2, "memoplus", 100, 10)) == 1);
	assert(addDrug(l, createDrug(3, "memoplus1", 100, 10)) == 1);
	sort(l, cmpName, 1);
	assert(l->elements[0].id == 2);
	assert(l->elements[1].id == 3);
	destroyList(&l);
}