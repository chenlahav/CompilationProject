#ifndef TOKEN_H
#define TOKEN_H
#include "stdio.h"

extern FILE *yyin, *yyout;

typedef enum eTOKENS
{
	TOKEN_ADDITION,
	TOKEN_SUBTRACTION,
	TOKEN_MULTIPLICATION,
	TOKEN_DIVISION,
	TOKEN_POWER,
	TOKEN_INCREMENT,
	TOKEN_EQUAL,
	TOKEN_NOT_EQUAL,
	TOKEN_LESS,
	TOKEN_GREAT,
	TOKEN_LESS_EQUAL,
	TOKEN_GREATER_EQUAL,
	TOKEN_ASSIGNMENT,
	TOKEN_POINTER,
	TOKEN_ADDRESS,
	TOKEN_ID,
	TOKEN_INT_NUM,
	TOKEN_REAL_NUM,
	TOKEN_BLOCK,
	TOKEN_BEGIN,
	TOKEN_END,
	TOKEN_TYPE,
	TOKEN_IS,
	TOKEN_INTEGER,
	TOKEN_REAL,
	TOKEN_ARRAY,
	TOKEN_OF,
	TOKEN_WHEN,
	TOKEN_DO,
	TOKEN_DEFAULT,
	TOKEN_END_WHEN,
	TOKEN_FOR,
	TOKEN_END_FOR,
	TOKEN_MALLOC,
	TOKEN_FREE,
	TOKEN_SIZE_OF,
	TOKEN_COLON,
	TOKEN_SEMICOLON,
	TOKEN_OPEN_PARENTHESES,
	TOKEN_CLOSE_PARENTHESES,
	TOKEN_OPEN_BRACKETS,
	TOKEN_CLOSE_BRACKETS
}eTOKENS;

typedef struct Token
{
	eTOKENS kind;
	char *lexeme;
	int lineNumber;
}Token;

//char* token_names[] =
//{
//	"addition",
//	"subtraction",
//	"multiplication",
//	"division",
//	"power",
//	"increment",
//	"equal",
//	"not_equal",
//	"less",
//	"great",
//	"less_equal",
//	"greater_equal",
//	"assignment",
//	"pointer",
//	"address",
//	"id",
//	"int_num",
//	"real_num",
//	"block",
//	"begin",
//	"end",
//	"type",
//	"is",
//	"integer",
//	"real",
//	"array",
//	"of",
//	"when",
//	"do",
//	"default",
//	"end_when",
//	"for",
//	"end_for",
//	"malloc",
//	"free",
//	"size_of",
//	"colon",
//	"semicolon",
//	"open_parentheses",
//	"close_parentheses",
//	"open_brackets",
//	"close_brackets"
//};

typedef struct Node
{
	Token *tokensArray;
	struct Node *prev;
	struct Node *next;
} Node;

void create_and_store_token(eTOKENS kind, char* lexeme, int numOfLine);
Token *next_token();
Token *back_token();
void match(eTOKENS kind);
void print_error(eTOKENS expected_token, eTOKENS actual_token, int line_number, char current_lexeme);

#endif