%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "Token.h"
	#include "Parser.h"
	void insertAndPrintToken(eTOKENS kind, char* lexeme, int line_number);
	int line_number = 1;
	char* tokens[]= 
	{
		"addition",
		"subtraction",
		"multiplication",
		"division",
		"power",
		"increment",
		"equal",
		"not_equal",
		"less",
		"great",
		"less_equal",
		"greater_equal",
		"assignment",
		"pointer",
		"address",
		"id",
		"int_num",
		"real_num",
		"block",
		"begin",
		"end",
		"type",
		"is",
		"integer",
		"real",
		"array",
		"of",
		"when",
		"do",
		"default",
		"end_when",
		"for",
		"end_for",
		"malloc",
		"free",
		"size_of",
		"colon",
		"semicolon",
		"open_parentheses",
		"close_parentheses",
		"open_brackets",
		"close_brackets",
		"eof"
	};
%}

DIGIT [0-9]
INT_NUM {DIGIT}+
REAL_NUM {DIGIT}+[.]{DIGIT}+

%%
"+" { insertAndPrintToken(TOKEN_ADDITION, yytext, line_number);return;}
"-" { insertAndPrintToken(TOKEN_SUBTRACTION, yytext, line_number); return;}
"*" { insertAndPrintToken(TOKEN_MULTIPLICATION, yytext, line_number); return;}
"/" { insertAndPrintToken(TOKEN_DIVISION, yytext, line_number); return;}
"**" { insertAndPrintToken(TOKEN_POWER, yytext, line_number); return;}

"++" { insertAndPrintToken(TOKEN_INCREMENT, yytext, line_number); return;}
"&" { insertAndPrintToken(TOKEN_ADDRESS, yytext, line_number); return;}

"==" { insertAndPrintToken(TOKEN_EQUAL, yytext, line_number); return;}
"!=" { insertAndPrintToken(TOKEN_NOT_EQUAL, yytext, line_number); return;}
"<" { insertAndPrintToken(TOKEN_LESS, yytext, line_number); return;}
">" { insertAndPrintToken(TOKEN_GREAT, yytext, line_number); return;}
"<=" { insertAndPrintToken(TOKEN_LESS_EQUAL, yytext, line_number); return;}
">=" { insertAndPrintToken(TOKEN_GREATER_EQUAL, yytext, line_number); return;}

"=" { insertAndPrintToken(TOKEN_ASSIGNMENT, yytext, line_number); return;}

"^" { insertAndPrintToken(TOKEN_POINTER, yytext, line_number); return;}

{INT_NUM} { insertAndPrintToken(TOKEN_INT_NUM, yytext, line_number); return;}

{REAL_NUM} { insertAndPrintToken(TOKEN_REAL_NUM, yytext, line_number); return;}
 
"block" { insertAndPrintToken(TOKEN_BLOCK, yytext, line_number); return;}
"begin" { insertAndPrintToken(TOKEN_BEGIN, yytext, line_number); return;}
"end" { insertAndPrintToken(TOKEN_END, yytext, line_number); return;}
"type" { insertAndPrintToken(TOKEN_TYPE, yytext, line_number); return;}
"is" { insertAndPrintToken(TOKEN_IS, yytext, line_number); return;}
"integer" { insertAndPrintToken(TOKEN_INTEGER, yytext, line_number); return;}
"real" { insertAndPrintToken(TOKEN_REAL, yytext, line_number); return;}
"array" { insertAndPrintToken(TOKEN_ARRAY, yytext, line_number); return;}
"of" { insertAndPrintToken(TOKEN_OF, yytext, line_number); return;}
"when" { insertAndPrintToken(TOKEN_WHEN, yytext, line_number); return;}
"do" { insertAndPrintToken(TOKEN_DO, yytext, line_number); return;}
"default" { insertAndPrintToken(TOKEN_DEFAULT, yytext, line_number); return;}
"end_when" { insertAndPrintToken(TOKEN_END_WHEN, yytext, line_number); return;}
"for" { insertAndPrintToken(TOKEN_FOR, yytext, line_number); return;}
"end_for" { insertAndPrintToken(TOKEN_END_FOR, yytext, line_number); return;}
"malloc" { insertAndPrintToken(TOKEN_MALLOC, yytext, line_number); return;}
"size_of" { insertAndPrintToken(TOKEN_SIZE_OF, yytext, line_number); return;}
"free" { insertAndPrintToken(TOKEN_FREE, yytext, line_number); return;}

[a-zA-Z]+(_?[a-zA-Z0-9]+)* { insertAndPrintToken(TOKEN_ID, yytext, line_number); return;}

":" { insertAndPrintToken(TOKEN_COLON, yytext, line_number); return;}
";" { insertAndPrintToken(TOKEN_SEMICOLON, yytext, line_number); return;}
"(" { insertAndPrintToken(TOKEN_OPEN_PARENTHESES, yytext, line_number); return;}
")" { insertAndPrintToken(TOKEN_CLOSE_PARENTHESES, yytext, line_number); return;}
"[" { insertAndPrintToken(TOKEN_OPEN_BRACKETS, yytext, line_number); return;}
"]" { insertAndPrintToken(TOKEN_CLOSE_BRACKETS, yytext, line_number); return;}

\n { line_number++; }
\t|" "|"--".* { }
<<EOF>> {create_and_store_token(TOKEN_EOF, "", line_number); return;}
. { fprintf(yyout_lex, "The character '%s' at line: %d does not begin any legal token in the language.\n", yytext, line_number); return;}

%%

void main(int argc, char* argv[])
{
	//test1
	yyin = fopen("C:\\temp\\test1.txt","r");
	yyout_lex = fopen("C:\\temp\\test1_308334309_203698808_lex.txt","w");
	yyout_syntactic = fopen("C:\\temp\\test1_308334309_203698808_syntactic.txt", "w");
	yyout_semantic = fopen("C:\\temp\\test1_308334309_203698808_semantic.txt", "w");
	parse_program();
	fclose(yyin);
	fclose(yyout_lex);
	fclose(yyout_syntactic);
	fclose(yyout_semantic);

	YY_lex_RESTART();
	line_number = 1;

	//test2
	yyin = fopen("C:\\temp\\test2.txt","r");
	yyout_lex = fopen("C:\\temp\\test2_308334309_203698808_lex.txt","w");
	yyout_syntactic = fopen("C:\\temp\\test2_308334309_203698808_syntactic.txt", "w");
	yyout_semantic = fopen("C:\\temp\\test2_308334309_203698808_semantic.txt", "w");
	parse_program();
	fclose(yyin);
	fclose(yyout_lex);
	fclose(yyout_syntactic);
	fclose(yyout_semantic);
}

void insertAndPrintToken(eTOKENS kind, char* lexeme, int line_number)
{
	create_and_store_token(kind, lexeme, line_number);
	fprintf(yyout_lex, "Token of kind '%s' was found at line: %d, lexeme: '%s'.\n",tokens[kind], line_number, lexeme);
}