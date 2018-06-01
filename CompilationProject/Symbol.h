#pragma once

typedef enum eROLE
{
	variable,
	user_defined_type

}eROLE;

typedef enum eCATEGORY
{
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