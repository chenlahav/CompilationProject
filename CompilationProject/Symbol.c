#include "Symbol.h"
#include <stdio.h>

void create_new_symbol()
{
	currentSymbol = (Symbol*)malloc(sizeof(Symbol));
	currentSymbol->Size = -1;
	currentSymbol->Type = NULL;
	currentSymbol->Category = null;
	currentSymbol->SubType = NULL;
}