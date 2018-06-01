#include <stdio.h>
#include "LinkList.h"
#include "SymbolTable.h"
#include "Symbol.h"

void initSymbolTable()
{
	int i;
	for (i = 0; i < SIZE; i++)
	{
		SymbolTable[i] = initLinkList();
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

Symbol *lookup(char* key) { 
	//get the hash 
	int hashIndex = hashCode(key);

	Node* currentNode = SymbolTable[hashIndex]->head;

	//move in array until an empty 
	while (currentNode != NULL) 
	{
		if (currentNode->data.Name == key)
			return &(currentNode->data);

		//go to next cell
		currentNode = currentNode->next;
	}

	return NULL;
}

void insertToSymbolTable(Symbol value) 
{
	//get the hash 
	int hashIndex = hashCode(value.Name);

	Symbol *lookupResult= lookup(value.Name);
	if (lookupResult == NULL)
	{
		insertToLinkList(SymbolTable[hashIndex], value);
	}
}