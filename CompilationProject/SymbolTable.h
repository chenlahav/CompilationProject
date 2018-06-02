#pragma once
#include <stdio.h>
#include "LinkList.h"
#include "Symbol.h"

#define SIZE 10

typedef LinkList* SymbolTable[SIZE];

void initSymbolTable(SymbolTable symbolTable);
unsigned int hashCode(char* name);
Symbol *lookup(LinkList* symbolTable[], char* key);
void insertToSymbolTable(SymbolTable symbolTable,  Symbol *value);
