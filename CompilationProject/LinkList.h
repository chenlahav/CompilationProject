#pragma once
#include "Symbol.h"

typedef struct SymbolNode
{
	Symbol data;
	struct SymbolNode *next;
}SymbolNode;

typedef struct LinkList
{
	SymbolNode* head;
}LinkList;

LinkList *initLinkList();

SymbolNode *initSymbolNode(Symbol data);

void insertToLinkList(LinkList* list, Symbol data);

