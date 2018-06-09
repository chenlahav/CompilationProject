#include "SymbolTablesList.h"
#include <stdio.h>


SymbolTableNode* InitSymbolTableNode(SymbolTable symbolTable)
{
	SymbolTableNode* new_node = (SymbolTableNode*)malloc(sizeof(SymbolTableNode));
	new_node->symbolTable = symbolTable;
	new_node->Next = NULL;
	return new_node;
}

SymbolTablesList* InitSymbolTablesList()
{
	SymbolTablesList *list = (SymbolTablesList*)malloc(sizeof(SymbolTablesList));
	list->Head = NULL;
	return list;
}

void pop(SymbolTablesList* symbolTableList)
{
	if (symbolTableList->Head == NULL)
	{
		return;
	}

	SymbolTableNode* symbolTableNodeToDelete = symbolTableList->Head;
	symbolTableList->Head = symbolTableList->Head->Next;

	free (symbolTableNodeToDelete);
}

void push(SymbolTable symbolTable, SymbolTablesList* symbolTableList)
{
	SymbolTableNode* currentHead = symbolTableList->Head;
	symbolTableList->Head = InitSymbolTableNode(symbolTable);
	symbolTableList->Head->Next = currentHead;
}

Symbol* Find(SymbolTablesList* symbolTableList, char* Key)
{
	Symbol* symbolToReturn;

	SymbolTableNode* currentNode = symbolTableList->Head;
	while (currentNode != null)
	{
		symbolToReturn = lookup(currentNode->symbolTable, Key);
		if (symbolToReturn != null)
		{
			return symbolToReturn;
		}
		currentNode = currentNode->Next;
	}

	return null;
}

Symbol* Find_type(SymbolTablesList* symbolTableList, char* Key)
{
	Symbol* symbolToReturn;

	SymbolTableNode* currentNode = symbolTableList->Head;
	while (currentNode != null)
	{
		symbolToReturn = lookup(currentNode->symbolTable, Key);
		if (symbolToReturn != null)
		{
			if(symbolToReturn->Role == user_defined_type)
				return symbolToReturn;
		}
		currentNode = currentNode->Next;
	}

	return null;
}