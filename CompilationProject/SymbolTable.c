#include <stdio.h>
#include "LinkList.h"
#include "SymbolTable.h"
#include "Symbol.h"

void initSymbolTable(SymbolTable symbolTable)
{
	int i;
	for (i = 0; i < SIZE; i++)
	{
		symbolTable[i] = initLinkList();
	}
}

unsigned int hashCode(char* name)
{
	unsigned int result = 5381;
	unsigned char *p;

	p = (unsigned char *)name;

	while (*p != '\0') {
		result = (result << 5) + result + (unsigned int)tolower(*p);
		++p;
	}

	return result % SIZE;
}

Symbol *lookup(LinkList* symbolTable[], char* key) { 
	//get the hash 
	int hashIndex = hashCode(key);
	SymbolNode* currentNode = symbolTable[hashIndex]->head;

	//move in array until an empty 
	while (currentNode != NULL) 
	{
		if (currentNode->data->Name == key)
			return &(currentNode->data);

		//go to next cell
		currentNode = currentNode->next;
	}

	return NULL;
}

void insertToSymbolTable(SymbolTable symbolTable, Symbol *value)
{
	//get the hash 
	int hashIndex = hashCode(value->Name);
	Symbol *lookupResult = lookup(symbolTable, value->Name);
	if (lookupResult == NULL)
	{
		insertToLinkList(symbolTable[hashIndex], value);
	}
}