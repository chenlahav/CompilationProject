#include <stdio.h>
#include "LinkList.h"

LinkList *initLinkList()
{
	LinkList *list = (LinkList*)malloc(sizeof(LinkList));
	list->head = NULL;

	return list;
}

void insertToLinkList(LinkList* list, Symbol data)
{
	SymbolNode* new_node = (SymbolNode*)malloc(sizeof(SymbolNode*));
	new_node->data = data;
	if (new_node != NULL)
	{
		new_node->next = list->head;
	}
	list->head = new_node;
}