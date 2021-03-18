#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "service.h"
#include "mysort.h"

DrugStore createDrugStore()
{
	DrugStore rez;
	rez.allDrugs = createEmpty();
	return rez;
}

void destroyStore(DrugStore* store)
{
	destroyList(store->allDrugs);
}

int addDrugService(DrugStore* store, int id, char* name, int quantity, int concentration)
{
	/*
		add a drug to the store
	*/
	Drug* d = createDrug(id, name, quantity, concentration);
	int errorCode = validate(d);
	if (errorCode != 0)
	{
		destroyDrug(d);
		return errorCode;
	}
	int repoError = addDrug(store->allDrugs, d);
	if (repoError == 0)
	{
		destroyDrug(d);
		return 10;
	}
	return 0;
}

MyList* getAllDrugs(DrugStore* store)
{
	/*
		Filter pets in the store
		typeSubstring - cstring
		return all pets where typeSubstring is a substring of the type
	*/
	return copyList(store->allDrugs);
}

int findDrugService(DrugStore* store, int id)
{
	/*
		find drug given the id
		return -1 if not found, the position otherwise
	*/
	for (int i = 0; i < getSizeDrugs(store->allDrugs); i++)
	{
		Drug* d = getDrug(store->allDrugs, i);
		if (d->id == id)
			return i;
	}
	return -1;
}

int editDrugService(DrugStore* store, int id, char* name, int quantity, int concentration)
{
	/*
		edit drug given the parameters
		return error codes: 1-4 -> negative numbers or empty string, 10 -> id was not found
	*/
	Drug *d = createDrug(id, name, quantity, concentration);
	int errorCode = validate(d);
	if (errorCode != 0)
	{
		destroyDrug(d);
		return errorCode;
	}
	int pos = findDrugService(store, id);
	if (pos == -1)
	{
		destroyDrug(d);
		return 10;
	}
	Drug *d1 = getDrug(store->allDrugs, pos);
	destroyDrug(d1);
	editDrug(store->allDrugs, d, pos);
	return 0;
}

int deleteDrugService(DrugStore* store, int id)
{
	/*
		delete a drug given the id
		return 10 if id was not found, 1 if id is negative or 0 otherwise
	*/
	int pos = findDrugService(store, id);
	if (pos == -1)
		return 10;
	Drug *d = getDrug(store->allDrugs, pos);
	/*
	int errorCode = validate(d);
	if (errorCode != 0)
	{
		destroyDrug(&d);
		return errorCode;
	}
	*/
	deleteDrug(store->allDrugs, pos);
	destroyDrug(d);
	return 0;
}

MyList* sortByName(DrugStore* store, int direction)
{
	/*
		sort by name
		direction can be ascending (1) or descending (-1)
	*/
	MyList* l = copyList(store->allDrugs);
	sort(l, cmpName, direction);
	return l;
}

MyList* sortByQuantity(DrugStore* store, int direction)
{
	/*
		sort by quantity
		direction can be ascending (1) or descending (-1)
	*/
	MyList* l = copyList(store->allDrugs);
	sort(l, cmpQuantity, direction);
	return l;
}

MyList* filterByQuantity(DrugStore* store, int value)
{
	/*
		filter drugs
		return all drugs whose quantity is less than given value
	*/
	MyList* rez = createEmpty();
	for (int i = 0; i < getSizeDrugs(&store->allDrugs); i++)
	{
		Drug* p = getDrug(store->allDrugs, i);
		if (p->quantity < value)
			addDrug(rez, copyDrug(p));
	}
	return rez;
}

MyList* filterByName(DrugStore* store, char value)
{
	/*
		filter drugs
		return all drugs whose name begin with given char value
	*/
	MyList* rez = createEmpty();
	for (int i = 0; i < getSizeDrugs(&store->allDrugs); i++)
	{
		Drug *p = getDrug(store->allDrugs, i);
		if (p->name[0] == value)
			addDrug(rez, copyDrug(p));
	}
	return rez;
}

void testAddDrug() 
{
	DrugStore store = createDrugStore();
	addDrugService(&store, 1, "a", 200, 10);
	addDrugService(&store, 2, "b", 200, 20);
	assert(addDrugService(&store, 2, "b", 200, 20) == 10);
	assert(getSizeDrugs(store.allDrugs) == 2);
	assert(findDrugService(&store, 1) == 0);
	assert(findDrugService(&store, 3) == -1);
	int errorCode = addDrugService(&store, -1, "a", 200, 10);
	assert(errorCode != 0);
	errorCode = addDrugService(&store, 1, "", 200, 10);
	assert(errorCode != 0);
	errorCode = addDrugService(&store, 1, "a", -200, 10);
	assert(errorCode != 0);
	errorCode = addDrugService(&store, 1, "a", 200, -10);
	assert(errorCode != 0);

	MyList* l = getAllDrugs(&store);
	//assert(l->elements[0].id == 1);
	//assert(l->elements[1].id == 2);

	destroyStore(&store);
	destroyList(&l);
}

void testEditDrugService()
{
	DrugStore store = createDrugStore();
	addDrugService(&store, 1, "a", 200, 10);
	editDrugService(&store, 1, "b", 300, 110);
	assert(editDrugService(&store, 2, "b", 300, 110) == 10);
	assert(editDrugService(&store, 1, "b", -300, 110) == 3);
	//assert(store.allDrugs.elements[0].quantity == 300);
	destroyStore(&store);
}

void testDeleteDrugService()
{
	DrugStore store = createDrugStore();
	addDrugService(&store, 1, "a", 200, 10);
	deleteDrugService(&store, 1);
	assert(getSizeDrugs(&store.allDrugs) == 0);
	assert(deleteDrugService(&store, 1) == 10);
	assert(deleteDrugService(&store, -2) == 10);
	destroyStore(&store);
}


void testSortByNameAndQuantity()
{
	DrugStore store = createDrugStore();
	addDrugService(&store, 1, "a", 200, 10);
	addDrugService(&store, 2, "b", 100, 20);
	addDrugService(&store, 3, "c", 250, 20);
	addDrugService(&store, 4, "d", 250, 20);
	MyList* l = sortByName(&store, -1);
	//assert(l->elements[0].id == 4);
	destroyList(&l);
	MyList* l1 = sortByQuantity(&store, 1);
	//assert(l1->elements[0].id == 2);
	destroyList(&l1);
	destroyStore(&store);
}

void testFilterByQuantityAndName()
{
	DrugStore store = createDrugStore();
	addDrugService(&store, 1, "a", 200, 10);
	addDrugService(&store, 2, "ab", 100, 20);
	addDrugService(&store, 3, "c", 250, 20);
	MyList* l = filterByQuantity(&store, 101);
	//assert(l.elements[0].id == 2);
	destroyList(&l);
	MyList* l1 = filterByName(&store, 'a');
	//assert(l1.elements[0].id == 1);
	//assert(l1.elements[1].id == 2);
	//assert(getSizeDrugs(&l1) == 2);
	destroyList(&l1);
	destroyStore(&store);
}

void testService()
{
	testAddDrug();
	testEditDrugService();
	testDeleteDrugService();
	testSortByNameAndQuantity();
	testFilterByQuantityAndName();
}