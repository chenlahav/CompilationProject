#pragma once
#include "SymbolTable.h"


typedef struct SymbolTableNode
{
	SymbolTable* symbolTable;
	struct SymbolTableNode* Next;
}SymbolTableNode;

typedef struct SymbolTablesList
{
	 SymbolTableNode* Head;

}SymbolTablesList;


SymbolTableNode* InitSymbolTableNode(SymbolTable symbolTable);
SymbolTablesList* InitSymbolTablesList();
void pop(SymbolTablesList* symbolTableList);
void push(SymbolTable symbolTable, SymbolTablesList* symbolTableList);
Symbol* Find(SymbolTablesList* symbolTableList, char* Key);
Symbol* Find_type(SymbolTablesList* symbolTableList, char* Key);
