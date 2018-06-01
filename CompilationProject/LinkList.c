#include <stdio.h>
#include "LinkList.h"

SymbolNode *initSymbolNode(Symbol data)
{
	SymbolNode *new_node = (Symbol*)malloc(sizeof(SymbolNode));
	new_node->data = data;
	new_node->next = NULL;
	
	return new_node;
}

LinkList *initLinkList()
{
	LinkList *list = (LinkList*)malloc(sizeof(LinkList));
	list->head = NULL;

	return list;
}

void insertToLinkList(LinkList* list, Symbol data)
{
	SymbolNode *new_node = initSymbolNode(data);
	if (list->head != NULL)
	{
		new_node->next = list->head;
	}

	list->head = new_node;
}