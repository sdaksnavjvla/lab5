#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <string.h>
#include "drug.h"
#include "repository.h"
#include "service.h"
#include "utils.h"
#include "mysort.h"

void createNewDrug(DrugStore* store)
{
	/*
		input parameters and store drug
		print errors
	*/
	char id[5], name[30], quantity[1000], concentration[1000];
	printf("Give id: ");
	scanf_s("%s", &id, 5);
	printf("Give name: ");
	scanf_s("%s", name, 30);
	printf("Give quantity: ");
	scanf_s("%s", &quantity, 1000);
	printf("Give concentration: ");
	scanf_s("%s", &concentration, 1000);
	int typeError = typeValidator(id, name, quantity, concentration);
	if (typeError == 0)
		printf("Id, quantity and concentration fields can only be positive integers.\n");
	else
	{
		int error = addDrugService(store, atoi(id), name, atoi(quantity), atoi(concentration));
		if (error == 10)
			printf("Duplicate id found.\n");
		if (error != 0)
			printf("Invalid drug.\n");
		else
			printf("Operation successful.\n");
	}
	printf("\n");
}

void printAllDrugs(MyList* l)
{
	/*
		print drugs
		show error message if there are no stored drugs
	*/
	if (getSizeDrugs(l) == 0)
		printf("No data has been found.\n");
	else
	{
		printf("Drugs:\n");
		for (int i = 0; i < getSizeDrugs(l); i++)
		{
			Drug* d = getDrug(l, i);
			printf("Id: %d; Name: %s; Quantity: %d, Concentration: %d\n", d->id, d->name, d->quantity, d->concentration);
		}
	}
	printf("\n");
}

void showAllDrugs(DrugStore* store)
{
	MyList* allDrugs = getAllDrugs(store);
	printAllDrugs(allDrugs);
	destroyList(allDrugs);
}

void editNewDrug(DrugStore* store)
{
	/*
		input drug's id to edit and new parameters
		check if id is already in the store
		update the drug
		show error messages
	*/
	char id[5], name[30], quantity[1000], concentration[1000];
	printf("Give id: ");
	scanf_s("%s", &id, 5);
	printf("Give name: ");
	scanf_s("%s", name, 30);
	printf("Give quantity: ");
	scanf_s("%s", &quantity, 1000);
	printf("Give concentration: ");
	scanf_s("%s", &concentration, 1000);
	int typeError = typeValidator(id, name, quantity, concentration);
	if (typeError == 0)
		printf("Id, quantity and concentration fields can only be positive integers.\n");
	else
	{
		int error = editDrugService(store, atoi(id), name, atoi(quantity), atoi(concentration));
		if (error == 10)
			printf("Id was not found.\n");
		else
		{
			if (error != 0)
				printf("Invalid drug.\n");
			else
				printf("Operation successful.\n");
		}
	}
	printf("\n");
}

void deleteNewDrug(DrugStore* store)
{
	/*
		delete a drug given the id
		id must exist
	*/
	char id[5];
	printf("Give id: ");
	scanf_s("%s", &id, 5);
	int typeError = typeValidator(id, "name", "1", "1");
	if (typeError == 0)
		printf("Id field can only be positive integers.\n");
	else
	{
		int error = deleteDrugService(store, atoi(id));
		if (error == 10)
			printf("Id was not found.\n");
		else
		{
			if (error != 0)
				printf("Invalid drug.\n");
			else
				printf("Operation successful.\n");
		}
	}
	printf("\n");
}

void orderByName(DrugStore* store, int direction)
{
	/*
		sort by name
		direction can be ascending (1) or descending (-1)
	*/
	MyList* allDrugs = sortByName(store, direction);
	printAllDrugs(allDrugs);
	destroyList(allDrugs);
}

void orderByQuantity(DrugStore* store, int direction)
{
	/*
		sort by quantity
		direction can be ascending (1) or descending (-1)
	*/
	MyList* allDrugs = sortByQuantity(store, direction);
	printAllDrugs(allDrugs);
	destroyList(allDrugs);
}

void filterDrugsByName(DrugStore* store)
{
	/*
		filter by name
		show drugs whose first letter matches given value
	*/
	char string[256];
	printf("Give character to filter by: ");
	int ns = scanf_s("%s", string, 256);
	if (ns != 1)
		ns = 1;
	string[strlen(string)] = '\0';
	if (strlen(string) > 1)
		printf("Strings are not allowed, only single characters.\n");
	else
	{
		MyList* allDrugs = filterByName(store, string[0]);
		printAllDrugs(allDrugs);
		destroyList(allDrugs);
	}
}

void filterDrugsByQuantity(DrugStore* store)
{
	/*
		filter by quantity
		show drugs whose quantity is less than given value
	*/
	char value[1000];
	printf("Give quantity to filter by: ");
	scanf_s("%s", value, 1000);
	int typeError = typeValidator("1", "name", value, "1");
	if (typeError == 0)
		printf("This field can only be a positive integer.\n");
	else
	{
		if (value < 0)
			printf("This field can only be a positive integer.\n");
		else
		{
			MyList* allDrugs = filterByQuantity(store, atoi(value));
			printAllDrugs(allDrugs);
			destroyList(allDrugs);
		}
	}
}

void testAll()
{
	testCreateDestroyDrug();
	testMyList();
	//testService();
	testUtils();
	testSort();
}

void run()
{
	printf("Drug Store\n\n\n");
	DrugStore store = createDrugStore();
	int kill = 1;
	while (kill) {
		printf("1. Add Drug\n2. Show all drugs\n3. Edit drug.\n4. Delete drug\n5. Order drugs by name (ascending)\n6. Order drugs by name (descending)\n7. Order drugs by quantity(ascending)\n8. Order drugs by quantity(descending)\n9. Filter by initial name\n10. Filter by quantity\n0. Exit\nGive command:");
		int cmd = 0;
		scanf_s("%d", &cmd);
		switch (cmd) {
		case 1:
			createNewDrug(&store);
			break;
		case 2:
			showAllDrugs(&store);
			break;
		case 3:
			editNewDrug(&store);
			break;
		case 4:
			deleteNewDrug(&store);
			break;
		case 5:
			orderByName(&store, 1);
			break;
		case 6:
			orderByName(&store, -1);
			break;
		case 7:
			orderByQuantity(&store, 1);
			break;
		case 8:
			orderByQuantity(&store, -1);
			break;
		case 9:
			filterDrugsByName(&store);
			break;
		case 10:
			filterDrugsByQuantity(&store);
			break;
		case 0:
			printf("Bye bye");
			kill = 0;
			break;
		default:
			printf("Unknown command.\n");
		}
	}
	destroyStore(&store);
}

int main()
{
	testAll();
	run();
	_CrtDumpMemoryLeaks();
	return 0;
}