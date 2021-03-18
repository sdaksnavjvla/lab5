#pragma once
#include "drug.h"
#include "vector_dinamic.h"

typedef struct
{
	VectorDinamic* elements;
} MyList;

MyList* createEmpty();
void destroyList(MyList* l);
Drug* getDrug(MyList* l, int poz);
Drug* setDrug(MyList* l, int poz, Drug* d);
int getSizeDrugs(MyList* l);
void ensureCapacity(MyList* l);
int addDrug(MyList* l, Drug* d);
void editDrug(MyList* l, Drug* d, int pos);
void deleteDrug(MyList* l, int pos);
MyList* copyList(MyList* l);
void testMyList();