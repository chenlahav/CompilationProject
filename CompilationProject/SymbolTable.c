#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkList.h"
#include "Symbol.h"

#define SIZE 100

LinkList* SymbolTable[SIZE];

unsigned int hashCode(char* name)
{
	unsigned int result = 5381;
	unsigned char *p;

	p = (unsigned char *)name;

	while (*p != '\0') {
		result = (result << 5) + result + (unsigned int)tolower(*p);
		++p;
	}

	return result;
}

struct Symbol *lookup(char* key) { 
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

	if (SymbolTable[hashIndex] == NULL)
	{
		LinkList *link_list = (LinkList*) malloc(sizeof(LinkList));
		SymbolTable[hashIndex] = link_list;
		insertToLinkList(SymbolTable[hashIndex], value);
	}

	else
	{
		Symbol *lookupResult= lookup(value.Name);
		if (lookupResult == NULL)
		{
			insertToLinkList(SymbolTable[hashIndex], value);
		}
	}
}