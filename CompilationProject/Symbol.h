#pragma once

typedef enum eROLE
{
	variable,
	user_defined_type

}eROLE;

typedef enum eCATEGORY
{
	null,
	basic,
	array,
	pointer

}eCATEGORY;

typedef struct Symbol
{
	char* Name;
	eROLE Role;
	char* Type;
	eCATEGORY Category;
	char* SubType;
	int Size;

}Symbol;

Symbol* currentSymbol;

void create_new_symbol();