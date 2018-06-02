#pragma once
#include "SymbolTable.h"


typedef struct SymbolTableNode
{
	LinkList* SymbolTable[SIZE];
	struct SymbolTableNode* Next;
}SymbolTableNode;

typedef struct SymbolTablesList
{
	 SymbolTableNode* Head;

}SymbolTablesList;


SymbolTableNode* InitSymbolTableNode(LinkList* symbolTable);
SymbolTablesList* InitSymbolTablesList();
void pop(SymbolTablesList* symbolTableList);
void push(LinkList* symbolTable[SIZE], SymbolTablesList* symbolTableList);
Symbol* Find(SymbolTablesList* symbolTableList, char* Key);
