#pragma once
#include <stdio.h>
#include "LinkList.h"
#include "Symbol.h"

#define SIZE 10

LinkList* SymbolTable[SIZE];

void initSymbolTable();
unsigned int hashCode(char* name);
Symbol *lookup(LinkList** symbolTable, char* key);
void insertToSymbolTable(LinkList** symbolTable, Symbol *value);
