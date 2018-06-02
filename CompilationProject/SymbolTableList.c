#include "SymbolTablesList.h"
#include <stdio.h>



SymbolTableNode* InitSymbolTableNode(LinkList *symbolTable)
{
	SymbolTableNode* new_node = (SymbolTableNode*)malloc(sizeof(SymbolTableNode));
	*new_node->SymbolTable = symbolTable;
	new_node->Next = NULL;
	return new_node;
}


SymbolTablesList* InitSymbolTablesList()
{
	SymbolTablesList *list = (SymbolTablesList*)malloc(sizeof(SymbolTablesList));
	list->Head = NULL;
}

SymbolTableNode* Pop(SymbolTablesList* symbolTableList)
{
	if (symbolTableList->Head == NULL)
	{
		return NULL;
	}

	SymbolTableNode* symbolTableNodeToRetun = symbolTableList->Head;
	symbolTableList->Head = symbolTableList->Head->Next;
	return symbolTableNodeToRetun;
}

void push(LinkList* symbolTable, SymbolTablesList* symbolTableList)
{
	SymbolTableNode* currentHead = symbolTableList->Head;
	symbolTableList->Head = initSymbolNode(symbolTable);
	symbolTableList->Head->Next = currentHead;
}

Symbol Find(SymbolTablesList* symbolTableList, char* Key)
{
	SymbolTableNode* currentNode = symbolTableList->Head;
	while (currentNode != null)
	{
		lookup()
		currentNode->SymbolTable
		currentNode = currentNode->Next;
	}
}