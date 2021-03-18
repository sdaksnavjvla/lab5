#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "repository.h"

MyList* createEmpty()
{
	/*
		create an empty list
	*/
	MyList* rez;
	rez = malloc(sizeof(MyList*));
	rez->length = 0;
	rez->capacity = 2;
	rez->elements = malloc(sizeof(void*) * rez->capacity);
	return rez;
}

void destroyList(MyList* l)
{
	/*
		deallocate drugs
	*/
	for (int i = 0; i < l->length; i++)
	{
		destroyDrug(l->elements[i]);
	}
	free(l->elements);
	l->elements = NULL;
	l->length = 0;
}

Drug* getDrug(MyList* l, int poz)
{
	/*
		Get an element from the list
		poz - position of the element, need to be valid
		return element of the given position
	*/
	return l->elements[poz];
}

Drug setDrug(MyList* l, int poz, Drug d)
{
	/*
		Modify the element on the given position
		return the overwrited element
	*/
	Drug rez = l->elements[poz];
	l->elements[poz] = d;
	return rez;
}

int getSizeDrugs(MyList* l)
{
	/*
		return number of elements in the list
	*/
	return l->length;
}

void ensureCapacity(MyList* l)
{
	/*
		allocate more memory if needed
	*/
	if (l->length < l->capacity)
		return; //there is space

	//allocate more memory
	int newCapacity = l->capacity + 2;
	Drug* nElements = malloc(sizeof(Drug) * newCapacity);
	
	//copy elems
	for (int i = 0; i < l->length; i++)
		nElements[i] = l->elements[i];

	//deallocate old vector
	free(l->elements);
	l->elements = nElements;
	l->capacity = newCapacity;
}

int addDrug(MyList* l, Drug d)
{
	/*
		add drug into the list
		check if id is unique
		drug is added at the end of the list
		return 0 if drug could not be added, 1 otherwise
	*/
	//ensureCapacity(l);
	for (int i = 0; i < getSizeDrugs(l); i++)
	{
		Drug currentDrug = getDrug(l, i);
		if (currentDrug.id == d.id)
			return 0;
		else
			if (strcmp(currentDrug.name, d.name) == 0)
			{
				currentDrug.quantity += d.quantity;
				setDrug(l, i, currentDrug);
				return 2;
			}
	}
	ensureCapacity(l);
	l->elements[l->length] = d;
	l->length++;
	return 1;
}

void editDrug(MyList* l, Drug d, int pos)
{
	/*
		edit drug d given the position and data
	*/
	setDrug(l, pos, d);
}

void deleteDrug(MyList* l, int pos)
{
	/*
		delete drug d given the position
	*/
	for (int i = pos; i < l->length - 1; i++)
		l->elements[i] = l->elements[i + 1];
	//destroyDrug(&l->elements[l->length]);
	l->length--;
}

MyList copyList(MyList* l)
{
	/*
		Make a shallow copy of the list
		return Mylist containing the same elements as l
	*/
	MyList* rez = createEmpty();
	for (int i = 0; i < getSizeDrugs(l); i++)
	{
		Drug* d = getDrug(l, i);
		addDrug(rez, copyDrug(&d));
	}
	return rez;
}




















































void testCreateList()
{
	MyList l = createEmpty();
	assert(getSizeDrugs(&l) == 0);
	destroyList(&l);
}

void testIterateList()
{
	MyList l = createEmpty();
	assert(addDrug(&l, createDrug(1, "ospamox", 200, 10)) == 1);
	assert(addDrug(&l, createDrug(2, "memoplus", 100, 10)) == 1);
	Drug d1 = createDrug(2, "memoplus1", 100, 10);
	assert(addDrug(&l, d1) == 0);
	destroyDrug(&d1);
	Drug d2 = createDrug(3, "ospamox", 100, 10);
	assert(addDrug(&l, d2) == 2);
	destroyDrug(&d2);
	assert(getSizeDrugs(&l) == 2);
	Drug d = getDrug(&l, 0);

	assert(d.id == 1);
	assert(strcmp(d.name, "ospamox") == 0);
	assert(d.quantity == 300);
	assert(d.concentration == 10);
	d = getDrug(&l, 1);
	assert(d.id == 2);
	destroyList(&l);
	assert(getSizeDrugs(&l) == 0);
}

void testEditDrug()
{
	MyList l = createEmpty();
	//assert(addDrug(&l, createDrug(1, "ospamox", 200, 10)) == 1);
	//editDrug(&l, createDrug(2, "a", 5, 10), 0);

	Drug d1 = createDrug(1, "ospamox", 200, 10);
	assert(addDrug(&l, d1) == 1);
	editDrug(&l, createDrug(2, "a", 5, 10), 0);
	destroyDrug(&d1);

	Drug d = getDrug(&l, 0);
	assert(d.id == 2);
	assert(strcmp(d.name, "a") == 0);
	assert(d.quantity == 5);
	assert(d.concentration == 10);
	destroyList(&l);
}

void testDeleteDrug()
{
	MyList l = createEmpty();
	Drug d1 = createDrug(1, "ospamox", 200, 10);
	Drug d2 = createDrug(2, "ospamox1", 200, 10);
	assert(addDrug(&l, d1) == 1);
	assert(addDrug(&l, d2) == 1);
	destroyDrug(&d1);
	destroyDrug(&d2);
	deleteDrug(&l, 0);
	assert(getSizeDrugs(&l) == 1);
	deleteDrug(&l, 0);
	destroyList(&l);
}

void testCopyList()
{
	MyList l = createEmpty();
	addDrug(&l, createDrug(1, "ospamox", 200, 10));
	addDrug(&l, createDrug(2, "memoplus", 100, 10));
	MyList l2 = copyList(&l);
	assert(getSizeDrugs(&l2) == 2);
	destroyList(&l);
	destroyList(&l2);
}

void testMyList()
{
	testCreateList();
	testIterateList();
	testEditDrug();
	testDeleteDrug();
	testCopyList();
}