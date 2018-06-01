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


