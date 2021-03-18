#pragma once

#include "repository.h"

typedef struct
{
	MyList* allDrugs;
} DrugStore;

DrugStore createDrugStore();
void destroyStore(DrugStore* store);
int addDrugService(DrugStore* store, int id, char* name, int quantity, int concentration);
MyList* getAllDrugs(DrugStore* store);
int editDrugService(DrugStore* store, int id, char* name, int quantity, int concentration);
int findDrugService(DrugStore* store, int id);
int deleteDrugService(DrugStore* store, int id);
MyList* sortByName(DrugStore* store, int direction);
MyList* sortByQuantity(DrugStore* store, int direction);
MyList* filterByQuantity(DrugStore* store, int value);
MyList* filterByName(DrugStore* store, char value);
void testService();