#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "drug.h"
#include "utils.h"

Drug* createDrug(int id, char* name, int quantity, int concentration)
{
	/*
		create new Drug
		return drug
	*/
	Drug* rez;
	rez = malloc(sizeof(Drug));
	rez->id = id;
	size_t nrC = strlen(name) + 1;
	rez->name = malloc(sizeof(char) * nrC);
	strcpy_s(rez->name, nrC, name);
	rez->quantity = quantity;
	rez->concentration = concentration;
	return rez;
}

void destroyDrug(Drug* d)
{
	/*
		dealocate memory occupied by drug
	*/
	free(d->name);
	d->id = -1;
	d->name = NULL;
	d->quantity = -1;
	d->concentration = -1;
	free(d);
}

Drug* copyDrug(Drug* d)
{
	/*
		create a copy for the Drug
		deep copy - copy all the subparts
	*/
	return createDrug(d->id, d->name, d->quantity, d->concentration);
}

int validate(Drug* d)
{
	//if (isInt(d.id) == 0)
		//return -1;
	//else
		if (d->id < 0)
			return 1;
	if (strlen(d->name) == 0)
		return 2;
	//if (isInt(d.quantity) == 0)
		//return -3;
	//else
		if (d->quantity < 0)
			return 3;
	//if (isInt(d.concentration) == 0)
		//return -4;
	//else
		if (d->concentration < 0)
			return 4;
	return 0;
}

void testCreateDestroyDrug()
{
	Drug* d = createDrug(1, "ospamox", 200, 10);
	assert(d->id == 1);
	assert(strcmp(d->name, "ospamox") == 0);
	assert(d->quantity == 200);
	assert(d->concentration == 10);
	
	destroyDrug(d);
	assert(d->id == -1);
	assert(d->name == NULL);
	assert(d->quantity == -1);
	assert(d->concentration == -1);
}