#include "Token.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/* This package describes the storage of tokens identified in the input text.
* The storage is a bi-directional list of nodes.
* Each node is an array of tokens; the size of this array is defined as TOKEN_ARRAY_SIZE.
* Such data structure supports an efficient way to manipulate tokens.

There are three functions providing an external access to the storage:
- function create_and_store_tokens ; it is called by the lexical analyzer when it identifies a legal token in the input text.
- functions next_token and back_token; they are called by parser during the syntax analysis (the second stage of compilation)
*/

int currentIndex = 0;
Node* currentNode = NULL;
#define TOKEN_ARRAY_SIZE 100

/*
* This function creates a token and stores it in the storage.
*/
void create_and_store_token(eTOKENS kind, char* lexeme, int numOfLine)
{ 
	// case 1: there is still no tokens in the storage.
	if (currentNode == NULL)
	{
		currentNode = (Node*)malloc(sizeof(Node));

		if(currentNode == NULL)
		{
			fprintf(yyout,"\nUnable to allocate memory! \n"); 
			exit(0);
		}
		currentNode->tokensArray = (Token*)malloc(sizeof(Token)*TOKEN_ARRAY_SIZE);
		if(currentNode->tokensArray == NULL)
		{
			fprintf(yyout,"\nUnable to allocate memory! \n"); 
			exit(0);
		}
		currentNode->prev = NULL;
		currentNode->next = NULL;
	}

	// case 2: at least one token exsits in the storage.
	else
	{
		// the array (the current node) is full, need to allocate a new node
		if (currentIndex == TOKEN_ARRAY_SIZE - 1)
		{
			currentIndex = 0;
			currentNode->next = (Node*)malloc(sizeof(Node));

			if(currentNode == NULL)
			{
				fprintf(yyout,"\nUnable to allocate memory! \n"); 
				exit(0);
			}
			currentNode->next->prev = currentNode;
			currentNode = currentNode->next;
			currentNode->tokensArray = (Token*)malloc(sizeof(Token)*TOKEN_ARRAY_SIZE);

			if(currentNode->tokensArray == NULL)
			{
				fprintf(yyout,"\nUnable to allocate memory! \n"); 
				exit(0);
			}
			currentNode->next = NULL;
		}

		// the array (the current node) is not full
		else
		{
			currentIndex++;
		}
	}

	currentNode->tokensArray[currentIndex].kind = kind;
	currentNode->tokensArray[currentIndex].lexeme = (char*)malloc(sizeof(char)*(strlen(lexeme)+1));
	strcpy(currentNode->tokensArray[currentIndex].lexeme, lexeme);
	currentNode->tokensArray[currentIndex].lineNumber = numOfLine;
}

/*
* This function returns the token in the storage that is stored immediately before the current token (if exsits).
*/
Token *back_token() 
{ 
	// there is still no tokens in the storage.
	if (currentNode == NULL)
	{
		return NULL;
	}

	//current Token is the first Token in the TokenArray.
	if(currentIndex == 0)
	{
		//the current Token is the first Token in the TokenStore.
		if(currentNode->prev == NULL)
		{
			return NULL;
		}
		//return the last Token in the previous Node.
		else
		{
			currentNode = currentNode->prev;
			currentIndex = TOKEN_ARRAY_SIZE-1;
			return &currentNode->tokensArray[currentIndex];
		}
	}
	//return the previous index in the same Node.
	else
	{
		currentIndex--;
		return &currentNode->tokensArray[currentIndex];
	}

}

/*
* If the next token already exists in the storage (this happens when back_token was called before this call to next_token): 
*  this function returns the next stored token.
* Else: continues to read the input file in order to identify, create and store a new token (using yylex function);
*  returns the token that was created.
*/
Token *next_token() 
{ 
	// there is still no tokens in the storage.
	if (currentNode == NULL)
	{
		yylex();
		return &currentNode->tokensArray[currentIndex];
	}

	//current Token is the last Token in the TokenArray.
	if(currentIndex == TOKEN_ARRAY_SIZE-1)
	{
		//The current Token is the last Token in the TokenStore.
		if(currentNode->next == NULL)
		{
			yylex();
			return &currentNode->tokensArray[currentIndex];
			
		}
		//return the first Token in the next Node.
		else
		{
			currentNode = currentNode->next;
			currentIndex = 0;
			return &currentNode->tokensArray[currentIndex];
		}
	}
	//return the next index in the same Node.
	else
	{
		currentIndex++;
		return &currentNode->tokensArray[currentIndex];
	}
}

//void print_error(expected_token, actual_token, line_number)
//{
//	// todo - print to output file
//	printf("syntax error, expected token: " + expected_token + "actual token: " + actual_token + "line number: " + line_number);
//}

void match(eTOKENS kind)
{
	Token *next_t = next_token();
	if(next_t->kind != kind)
	{
		print_error(next_t->kind, kind, next_t->lineNumber);
	}
}
