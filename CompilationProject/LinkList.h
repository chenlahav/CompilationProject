#pragma once
#include "Symbol.h"

typedef struct Node
{
	Symbol data;
	struct Node *next;
}Node;

typedef struct LinkList
{
	Node* head;
}LinkList;

void insertToLinkList(LinkList* list, Symbol data)
{
	Node* new_node = (Node*)malloc(sizeof(Node*));
	new_node->data = data;
	if (new_node != NULL)
	{
		new_node->next = list->head;
	}
	list->head = new_node;
	
}

