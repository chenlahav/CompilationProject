#pragma once
#include <stdio.h>
#include "LinkList.h"
#include "Symbol.h"

#define SIZE 100

LinkList* SymbolTable[SIZE];

void initSymbolTable();
unsigned int hashCode(char* name);
Symbol *lookup(char* key);
void insertToSymbolTable(Symbol *value);
