#pragma once
#include <stdio.h>
#include "LinkList.h"
#include "Symbol.h"

#define SIZE 10

LinkList* CreateSymbolTable();
void initSymbolTable(LinkList* symbolTable[]);
unsigned int hashCode(char* name);
Symbol *lookup(LinkList* symbolTable[], char* key);
void insertToSymbolTable(LinkList* symbolTable[],  Symbol *value);
