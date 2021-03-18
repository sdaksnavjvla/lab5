#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int isInt(char* string)
{
	/*
		check if given string is a number
		return 0 if not, 1 if true
	*/
	unsigned k = 0;
	if (string[0] == '-')
		k = 1;
	for (unsigned i = k; i < strlen(string); i++)
		if (isdigit(string[i]) == 0)
			return 0;
	return 1;
}

int typeValidator(char id[5], char name[30], char quantity[1000], char concentration[1000])
{
	/*
		check if given data is correct
	*/
	if (isInt(id) == 0 || isInt(quantity) == 0 || isInt(concentration) == 0 || strcmp(name, "") == 0)
		return 0;
	return 1;
}

int isEmpty(char* string)
{
	/*
		check if given string is empty
		return 0 if not, 1 if true
	*/
	if (string[0] == '\0')
		return 1;
	return 0;
}

void testConverters()
{
	assert(isInt("235235") == 1);
	assert(isInt("-235235") == 1);
	assert(isInt("2352a35") == 0);
	assert(isInt("--235235") == 0);
	assert(isEmpty("") == 1);
	assert(isEmpty("235235") == 0);
}

void testTypeValidator()
{
	assert(typeValidator("1","ospa","asd","1a") == 0);
	assert(typeValidator("1", "ospa", "200", "15") == 1);
}

void testUtils()
{
	testConverters();
	testTypeValidator();
}