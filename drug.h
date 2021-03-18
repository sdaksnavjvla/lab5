#pragma once
//#ifndef DRUG_H_
//#define DRUG_H_

typedef struct
{
	int id;
	char* name;
	int quantity;
	int concentration;
} Drug;

Drug* createDrug(int id, char* name, int quantity, int concentration);
void destroyDrug(Drug* d);
Drug* copyDrug(Drug* d);
int validate(Drug d);
void testCreateDestroyDrug();

//#endif /* DRUG_H_*/