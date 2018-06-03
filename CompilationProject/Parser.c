#include "Token.h"
#include "Parser.h"
#include "string.h"
#include "SymbolTable.h"
#include "SymbolTablesList.h"
#include <stdio.h>
#include <stdlib.h>

Token* currentToken = NULL;
SymbolTablesList* symbolTablesList;

char* get_token_name(int token_number)
{
	char* token_names[] =
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
		return token_names[token_number];
}

void parse_program()
{
	symbolTablesList = InitSymbolTablesList();
	fprintf(yyout_syntactic, "PROGRAM -> BLOCK\n");
	parse_block();
}

void parse_block()
{
	fprintf(yyout_syntactic, "BLOCK -> block DEFINITIONS; begin COMMANDS; end\n");
	match(TOKEN_BLOCK);
	SymbolTable symbolTable;
	initSymbolTable(symbolTable);
	push(symbolTable, symbolTablesList);
	parse_definitions();
	match(TOKEN_SEMICOLON);
	match(TOKEN_BEGIN);
	parse_commands();
	match(TOKEN_SEMICOLON);
	match(TOKEN_END);
	pop(symbolTablesList);
}

void parse_definitions()
{
	fprintf(yyout_syntactic, "DEFINITIONS -> DEFINITION DEFINITIONS'\n");
	parse_definition();
	parse_definitions_tag();
}

void parse_definitions_tag()
{
	Token* t = next_token();
	switch (t->kind)
	{
		case TOKEN_SEMICOLON:
		{
			Token* next_t = next_token();
			switch (next_t->kind)
			{
				case TOKEN_BEGIN:
				{
					fprintf(yyout_syntactic, "DEFINITIONS' -> e\n");
					back_token();
					back_token();
					break;
				}
				case TOKEN_ID:
				case TOKEN_TYPE:
				{
					fprintf(yyout_syntactic, "DEFINITIONS' -> ;DEFINITION DEFINITIONS'\n");
					back_token();
					parse_definition();
					parse_definitions_tag();
					break;
				}
				default:
				{
					eTOKENS expected_tokens[] = { TOKEN_ID, TOKEN_TYPE };
					parse_print_error(expected_tokens, next_t->kind, next_t->lineNumber, next_t->lexeme, 2);
					while( next_t->kind != TOKEN_BEGIN && next_t->kind != TOKEN_EOF)
					{
						next_t = next_token();
					}
					if (next_t->kind == TOKEN_EOF)
					{
						return;
					}
					else
					{
						next_t = back_token();
						break;
					}
				}
			}
			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_SEMICOLON };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 1);
			while (t->kind != TOKEN_SEMICOLON && t->kind != TOKEN_EOF)
			{
				t = next_token();
			}
			if (t->kind == TOKEN_EOF)
			{
				return;
			}
			else
			{
				t = back_token();
				break;
			}
		}
	}
}

void parse_definition()
{
	Token* t = next_token();
	create_new_symbol();
	switch (t->kind)
	{
		case TOKEN_ID:
		{
			back_token();
			fprintf(yyout_syntactic, "DEFINITION -> VAR_DEFINITION\n");
			parse_var_definition();
			if((currentSymbol->Type == "integer") || (currentSymbol->Type == "real") 
				|| ((Find(symbolTablesList, currentSymbol->Type) != NULL)))
			{
				insertToSymbolTable(symbolTablesList->Head->symbolTable, currentSymbol);
			}
			else
			{
				fprintf(yyout_semantic, "(Line %d) Type %s not defined\n", currentToken->lineNumber, currentToken->lexeme);
			}
			break;
		}
		case TOKEN_TYPE:
		{
			back_token();
			fprintf(yyout_syntactic, "DEFINITION -> TYPE_DEFINITION\n");
			parse_type_definition();
			if ((currentSymbol->SubType == "integer") || (currentSymbol->SubType == "real")
				|| ((Find(symbolTablesList, currentSymbol->SubType) != NULL)))
			{
				insertToSymbolTable(symbolTablesList->Head->symbolTable, currentSymbol);
			}
			else
			{
				fprintf(yyout_semantic, "(Line %d) Type %s not defined\n", currentToken->lineNumber, currentToken->lexeme);
			}

			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_ID, TOKEN_TYPE };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 2);
			while (t->kind != TOKEN_SEMICOLON && t->kind != TOKEN_EOF)
			{
				t = next_token();
			}
			if (t->kind == TOKEN_EOF)
			{
				return;
			}
			else
			{
				t = back_token();
				break;
			}
		}
	}
}

void parse_var_definition()
{
	fprintf(yyout_syntactic, "VAR_DEFINITION -> id : VAR_DEFINITION'\n");
	currentSymbol->Role = variable;
	match(TOKEN_ID);
	back_token();
	currentToken = next_token();
	currentSymbol->Name = currentToken->lexeme;

	match(TOKEN_COLON);
	parse_var_definition_tag();
}

void parse_var_definition_tag() 
{
	Token* t = next_token();
	switch (t->kind)
	{
		case TOKEN_INTEGER:
		case TOKEN_REAL:
		{
			back_token();
			fprintf(yyout_syntactic, "VAR_DEFINITION' -> BASIC_TYPE\n");
			parse_basic_type();
			break;
		}
		case TOKEN_ID:
		{
			fprintf(yyout_syntactic, "VAR_DEFINITION' -> type_name\n");
			back_token();
			currentToken = next_token();
			currentSymbol->Type = currentToken->lexeme;
			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_INTEGER, TOKEN_REAL, TOKEN_ID };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 3);
			while (t->kind != TOKEN_SEMICOLON && t->kind != TOKEN_EOF)
			{
				t = next_token();
			}
			if (t->kind == TOKEN_EOF)
			{
				return;
			}
			else
			{
				t = back_token();
				break;
			}
		}
	}
}

void parse_type_definition() 
{
	fprintf(yyout_syntactic, "TYPE_DEFINITION -> type type_name is TYPE_INDICATOR\n");
	currentSymbol->Role = user_defined_type;
	match(TOKEN_TYPE);
	match(TOKEN_ID);
	back_token();
	currentToken = next_token();
	currentSymbol->Name = currentToken->lexeme;
	match(TOKEN_IS);
	parse_type_indicator();
}

void parse_type_indicator()
{
	Token* t = next_token();

	switch (t->kind)
	{
		case TOKEN_INTEGER:
		case TOKEN_REAL:
		{
			back_token();
			fprintf(yyout_syntactic, "TYPE_INDICATOR -> BASIC_TYPE\n");
			parse_basic_type();
			break;
		}
		case TOKEN_ARRAY:
		{
			back_token();
			fprintf(yyout_syntactic, "TYPE_INDICATOR -> ARRAY_TYPE\n");
			parse_array_type();
			break;
		}
		case TOKEN_POINTER:
		{
			back_token();
			fprintf(yyout_syntactic, "TYPE_INDICATOR -> POINTER_TYPE\n");
			parse_pointer_type();
			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_INTEGER, TOKEN_REAL , TOKEN_ARRAY, TOKEN_POINTER};
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 4);
			while (t->kind != TOKEN_SEMICOLON && t->kind != TOKEN_EOF)
			{
				t = next_token();
			}
			if (t->kind == TOKEN_EOF)
			{
				return;
			}
			else
			{
				t = back_token();
				break;
			}
		}
	}
}

void parse_basic_type()
{
	Token *t = next_token();
	if ((currentSymbol->Role == user_defined_type) && (currentSymbol->Category == null))
	{
		currentSymbol->Category = basic;
	}
	switch (t->kind)
	{
		case TOKEN_INTEGER:
		{
			fprintf(yyout_syntactic, "BASIC_TYPE -> integer\n");
			if (currentSymbol->Role == user_defined_type)
			{
				currentSymbol->SubType = "integer";
			}
			else
			{
				currentSymbol->Type = "integer";
			}

			break;
		}

		case TOKEN_REAL:
		{
			fprintf(yyout_syntactic, "BASIC_TYPE -> real\n");
			if (currentSymbol->Role == user_defined_type)
			{
				currentSymbol->SubType = "real";
			}
			else
			{
				currentSymbol->Type = "real";
			}

			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_INTEGER, TOKEN_REAL };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 2);
			while (t->kind != TOKEN_SEMICOLON && t->kind != TOKEN_EOF)
			{
				t = next_token();
			}
			if (t->kind == TOKEN_EOF)
			{
				return;
			}
			else
			{
				t = back_token();
				break;
			}
		}
	}
}

void parse_array_type()
{
	fprintf(yyout_syntactic, "ARRAY_TYPE -> array [SIZE] of BASIC_TYPE\n");
	if (currentSymbol->Role == user_defined_type)
	{
		currentSymbol->Category = array;
	}
	match(TOKEN_ARRAY);
	match(TOKEN_OPEN_BRACKETS);
	parse_size();
	match(TOKEN_CLOSE_BRACKETS);
	match(TOKEN_OF);
	parse_basic_type();
}

void parse_pointer_type()
{
	fprintf(yyout_syntactic, "POINTER_TYPE -> ^POINTER_TYPE'\n");
	if (currentSymbol->Role == user_defined_type)
	{
		currentSymbol->Category = pointer;
	}
	match(TOKEN_POINTER);
	parse_pointer_type_tag();
}

void parse_pointer_type_tag()
{
	Token* t = next_token();
	switch (t->kind)
	{
		case TOKEN_INTEGER:
		case TOKEN_REAL:
		{
			back_token();
			fprintf(yyout_syntactic, "VAR_DEFINITION' -> BASIC_TYPE\n");
			parse_basic_type();
			break;
		}
		case TOKEN_ID:
		{
			fprintf(yyout_syntactic,"VAR_DEFINITION' -> type_name\n");
			back_token();
			currentToken = next_token();
			if (currentSymbol->Role == user_defined_type)
			{
				currentSymbol->SubType = currentToken->lexeme;
			}
			else
			{
				currentSymbol->Type = currentToken->lexeme;
			}
			
			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_INTEGER, TOKEN_REAL, TOKEN_ID };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 3);
			while (t->kind != TOKEN_SEMICOLON && t->kind != TOKEN_EOF)
			{
				t = next_token();
			}
			if (t->kind == TOKEN_EOF)
			{
				return;
			}
			else
			{
				t = back_token();
				break;
			}
		}
	}
}

void parse_size()
{
	fprintf(yyout_syntactic, "SIZE -> int_num\n");
	match(TOKEN_INT_NUM);
	back_token();
	currentToken = next_token();
	currentSymbol->Size = atoi(currentToken->lexeme);
}

void parse_commands() 
{
	fprintf(yyout_syntactic, "COMMANDS -> COMMAND COMMANDS'\n");
	parse_command();
	parse_commands_tag();
}

void parse_commands_tag()
{
	Token* t = next_token();
	Token* next_t;
	switch (t->kind)
	{
		case TOKEN_SEMICOLON:
		{
			next_t = next_token();
			switch (next_t->kind)
			{
				case TOKEN_END:
				case TOKEN_END_FOR:
				case TOKEN_END_WHEN:
				case TOKEN_DEFAULT:
				{
					fprintf(yyout_syntactic, "COMMANDS' -> e\n");
					back_token();
					back_token();
					break;
				}
				case TOKEN_ID:
				case TOKEN_WHEN:
				case TOKEN_FOR:
				case TOKEN_FREE:
				case TOKEN_BLOCK:
				{
					fprintf(yyout_syntactic, "COMMANDS' -> ;COMMAND COMMANDS'\n");
					back_token();
					parse_command();
					parse_commands_tag();
					break;
				}
				default:
				{
					eTOKENS expected_tokens[] = { TOKEN_END, TOKEN_ID , TOKEN_WHEN, TOKEN_FOR, TOKEN_FREE, TOKEN_BLOCK, TOKEN_END_FOR, TOKEN_END_WHEN, TOKEN_DEFAULT};
					parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 9);
					while (t->kind != TOKEN_END && t->kind != TOKEN_END_FOR && t->kind != TOKEN_END_WHEN
						&& t->kind != TOKEN_DEFAULT && t->kind != TOKEN_EOF)
									{
						t = next_token();
					}
					if (t->kind == TOKEN_EOF)
					{
						return;
					}
					else
					{
						t = back_token();
						break;
					}
				}
			}
			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_SEMICOLON };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 1);
			while (t->kind != TOKEN_SEMICOLON && t->kind != TOKEN_EOF)
			{
				t = next_token();
			}
			if (t->kind == TOKEN_EOF)
			{
				return;
			}
			else
			{
				t = back_token();
				break;
			}
		}
	}
}

void parse_command()
{
	Token* t = next_token();
	Token* next_t;
	switch (t->kind)
	{
		case TOKEN_ID:
		{
			fprintf(yyout_syntactic, "COMMAND -> id  COMMAND'\n");
			parse_command_tag();
			break;
		}
		case TOKEN_WHEN:
		{
			fprintf(yyout_syntactic, "COMMAND -> when (EXPRESSION rel_op EXPRESSION) do COMMANDS; default COMMANDS; end_when\n");
			match(TOKEN_OPEN_PARENTHESES);
			parse_expression();
			next_t = next_token();
			switch (next_t->kind)
			{
				case TOKEN_EQUAL:
				case TOKEN_NOT_EQUAL:
				case TOKEN_LESS:
				case TOKEN_GREAT:
				case TOKEN_LESS_EQUAL:
				case TOKEN_GREATER_EQUAL:
				{
					break;
				}
				default:
				{
					eTOKENS expected_tokens[] = { TOKEN_EQUAL, TOKEN_NOT_EQUAL , TOKEN_LESS, TOKEN_GREAT, TOKEN_LESS_EQUAL, TOKEN_GREATER_EQUAL };
					parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 6);
					while (next_t->kind != TOKEN_SIZE_OF && next_t->kind != TOKEN_ADDRESS
						&& next_t->kind != TOKEN_REAL_NUM && next_t->kind != TOKEN_INT_NUM && next_t->kind != TOKEN_ID
						&& next_t->kind != TOKEN_EOF)
					{
						next_t = next_token();
					}

					if (next_t->kind == TOKEN_EOF)
					{
						return;
					}
					else
					{
						next_t = back_token();
					}
					break;
				}
			}

			parse_expression();
			match(TOKEN_CLOSE_PARENTHESES);
			match(TOKEN_DO);
			parse_commands();
			match(TOKEN_SEMICOLON);
			match(TOKEN_DEFAULT);
			parse_commands();
			match(TOKEN_SEMICOLON);
			match(TOKEN_END_WHEN);
			break;
		}
		case TOKEN_FOR:
		{
			fprintf(yyout_syntactic, "COMMAND -> for (id = EXPRESSION; id rel_op EXPRESSION; id++) COMMANDS; end_for\n");
			match(TOKEN_OPEN_PARENTHESES);
			match(TOKEN_ID);
			match(TOKEN_ASSIGNMENT);
			parse_expression();
			match(TOKEN_SEMICOLON);
			match(TOKEN_ID);
			next_t = next_token();
			switch (next_t->kind)
			{
				case TOKEN_EQUAL:
				case TOKEN_NOT_EQUAL:
				case TOKEN_LESS:
				case TOKEN_GREAT:
				case TOKEN_LESS_EQUAL:
				case TOKEN_GREATER_EQUAL:
				{
					break;
				}
				default:
				{
					eTOKENS expected_tokens[] = { TOKEN_EQUAL, TOKEN_NOT_EQUAL , TOKEN_LESS, TOKEN_GREAT, TOKEN_LESS_EQUAL, TOKEN_GREATER_EQUAL };
					parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 6);
					while (next_t->kind != TOKEN_SIZE_OF && next_t->kind != TOKEN_ADDRESS
						&& next_t->kind != TOKEN_REAL_NUM && next_t->kind != TOKEN_INT_NUM && next_t->kind != TOKEN_ID
						&& next_t->kind != TOKEN_EOF)
					{
						next_t = next_token();
					}

					if (next_t->kind == TOKEN_EOF)
					{
						return;
					}
					else
					{
						next_t = back_token();
					}
					break;
				}
			}
			parse_expression();
			match(TOKEN_SEMICOLON);
			match(TOKEN_ID);
			match(TOKEN_INCREMENT);
			match(TOKEN_CLOSE_PARENTHESES);
			parse_commands();
			match(TOKEN_SEMICOLON);
			match(TOKEN_END_FOR);
			break;
		}
		case TOKEN_FREE:
		{
			fprintf(yyout_syntactic, "COMMAND -> free(id)\n");
			match(TOKEN_OPEN_PARENTHESES);
			match(TOKEN_ID);
			match(TOKEN_CLOSE_PARENTHESES);
			break;
		}
		case TOKEN_BLOCK:
		{
			fprintf(yyout_syntactic, "COMMAND -> BLOCK\n");
			back_token();
			parse_block();
			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_ID, TOKEN_WHEN, TOKEN_FOR, TOKEN_FREE, TOKEN_BLOCK };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 5);

			while(t->kind != TOKEN_SEMICOLON && t->kind != TOKEN_EOF)
			{
				t = next_token();
			}

			if (t->kind == TOKEN_EOF)
			{
				return;
			}
			else
			{
				t = back_token();
			}
			break;
		}
	}
}

void parse_command_tag()
{
	Token* t = next_token();
	switch (t->kind)
	{
		case TOKEN_OPEN_BRACKETS:
		case TOKEN_POINTER:
		{
			fprintf(yyout_syntactic, "COMMAND' -> RECEIVER' = EXPRESSION\n");
			back_token();
			Symbol* symbol_receiver_tag = parse_receiver_tag();
			match(TOKEN_ASSIGNMENT);
			Symbol* symbolExpression = parse_expression();

			if ((symbolExpression->Type != "undefined")&&(symbol_receiver_tag->Type != "undefined")
				&&(symbolExpression->Type != symbol_receiver_tag->Type))
			{
				fprintf(yyout_semantic, "(line %d) no matching types\n", t->lineNumber);
			}
			
			break;
		}
		case TOKEN_ASSIGNMENT:
		{
			Token* next_t = next_token();
			switch (next_t->kind)
			{
				case TOKEN_MALLOC:
				{
					fprintf(yyout_syntactic, "COMMAND' -> = malloc(size_of(type_name))\n");
					match(TOKEN_OPEN_PARENTHESES);
					match(TOKEN_SIZE_OF);
					match(TOKEN_OPEN_PARENTHESES);
					match(TOKEN_ID);
					match(TOKEN_CLOSE_PARENTHESES);
					match(TOKEN_CLOSE_PARENTHESES);
					break;
				}
				case TOKEN_ID:
				case TOKEN_INT_NUM:
				case TOKEN_REAL_NUM:
				case TOKEN_ADDRESS:
				case TOKEN_SIZE_OF:
				{
					fprintf(yyout_syntactic, "COMMAND' -> RECEIVER' = EXPRESSION\n");
					back_token();
					back_token();
					Symbol* symbol_receiver_tag = parse_receiver_tag();
					match(TOKEN_ASSIGNMENT);
					Symbol* symbolExpression = parse_expression();

					if ((symbolExpression->Type != "undefined") && (symbol_receiver_tag->Type != "undefined")
						&& (symbolExpression->Type != symbol_receiver_tag->Type))
					{
						fprintf(yyout_semantic, "(line %d) no matching types\n", t->lineNumber);
					}
					else if ((symbolExpression->Category == pointer) || (symbol_receiver_tag->Category == pointer))
					{
						if ((symbolExpression->Category == pointer) && (symbol_receiver_tag->Category == pointer))
						{

						}
						else
						{
							fprintf(yyout_semantic, "(line %d) no matching category \n", t->lineNumber);
						}
					}

					break;
				}
				default:
				{
					eTOKENS expected_tokens[] = { TOKEN_MALLOC, TOKEN_ID, TOKEN_INT_NUM, TOKEN_REAL_NUM, TOKEN_ADDRESS, TOKEN_SIZE_OF };
					parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 6);

					while (t->kind != TOKEN_MALLOC && t->kind != TOKEN_ID && t->kind != TOKEN_INT_NUM && t->kind != TOKEN_REAL_NUM
						&& t->kind != TOKEN_ADDRESS && t->kind != TOKEN_SIZE_OF && t->kind != TOKEN_EOF)
					{
						t = next_token();
					}

					if (t->kind == TOKEN_EOF) {
						return;
					}
					else
					{
						t = back_token();
					}

					break;
				}
			}
			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_OPEN_BRACKETS, TOKEN_POINTER, TOKEN_ASSIGNMENT };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 3);

			while (t->kind != TOKEN_ASSIGNMENT && t->kind != TOKEN_EOF) 
			{
				t = next_token();
			}

			if (t->kind == TOKEN_EOF)
			{
				return;
			}
			else
			{
				t = back_token();
			}
			break;
		}
	}
}

void parse_receiver()
{
	fprintf(yyout_syntactic, "RECEIVER -> id RECEIVER’\n");
	match(TOKEN_ID);
	parse_receiver_tag();
}

Symbol* parse_receiver_tag()
{
	back_token();
	Token* token_id = next_token();

	Token* t = next_token();
	Symbol* idSymbol = Find(symbolTablesList, token_id->lexeme);
	Symbol* symbolToReturn = (Symbol*)malloc(sizeof(Symbol));
	if (idSymbol == NULL)
	{
		fprintf(yyout_semantic, "(line %d) variable '%s' not defined\n", token_id->lineNumber, token_id->lexeme);
		symbolToReturn->Category = null;
		symbolToReturn->Name = "undefined";
		symbolToReturn->Type = "undefined";
		symbolToReturn->SubType = "undefined";
		return symbolToReturn;
	}

	Symbol* typeSymbol = get_type_of_symbol(idSymbol);

	switch (t->kind)
	{
		case TOKEN_OPEN_BRACKETS:
		{
			if (typeSymbol->Category != array)
			{
				fprintf(yyout_semantic, "(line %d) variable '%s' is not array\n", t->lineNumber, token_id->lexeme);
				symbolToReturn->Category = null;
				symbolToReturn->Name = "undefined";
				symbolToReturn->Type = "undefined";
				symbolToReturn->SubType = "undefined";
				return symbolToReturn;
			}
			fprintf(yyout_syntactic, "RECEIVER' -> [EXPRESSION]\n");
			Symbol* symbolExpression = parse_expression();
			if ((symbolExpression->Type != "undefined") && (typeSymbol->Type != "undefined")
				&& (symbolExpression->Type != "integer"))
			{
				fprintf(yyout_semantic, "(line %d) index must be integer\n", t->lineNumber);
			}
			symbolToReturn->Category = typeSymbol->Category;
			symbolToReturn->Type = typeSymbol->Type;
			match(TOKEN_CLOSE_BRACKETS);
			break;
		}
		case TOKEN_POINTER:
		{
			if (typeSymbol->Category != pointer)
			{
				fprintf(yyout_semantic, "(line %d) variable '%s' is not pointer\n", t->lineNumber, token_id->lexeme);
				symbolToReturn->Category = null;
				symbolToReturn->Name = "undefined";
				symbolToReturn->Type = "undefined";
				symbolToReturn->SubType = "undefined";
				return symbolToReturn;
			}
			fprintf(yyout_syntactic, "RECEIVER' -> ^\n");
			break;
		}
		case TOKEN_ASSIGNMENT:
		{
			fprintf(yyout_syntactic, "RECEIVER' -> e\n");
			symbolToReturn->Category = typeSymbol->Category;
			symbolToReturn->Type = typeSymbol->Type;
			back_token();
			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_OPEN_BRACKETS, TOKEN_POINTER };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 2);

			while (t->kind != TOKEN_ASSIGNMENT && t->kind != TOKEN_EOF) 
			{
				t = next_token();
			}

			if (t == TOKEN_EOF)
			{
				return;
			}
			else
			{
				t = back_token();
			}
			break;
		}
	}
	return symbolToReturn;
}

Symbol* parse_expression()
{
	Token* t = next_token();

	Symbol* symbol = (Symbol*) malloc(sizeof(Symbol));

	switch (t->kind)
	{
		case TOKEN_ID:
		{
			fprintf(yyout_syntactic, "EXPRESSION -> id EXPRESSION'\n");
			Symbol* symbol_expression_tag = parse_expression_tag();
			symbol->Type = symbol_expression_tag->Type;
			break;
		}
		case TOKEN_INT_NUM:
		{
			fprintf(yyout_syntactic, "EXPRESSION -> int_num\n");
			symbol->Type = "integer";
			break;
		}
		case TOKEN_REAL_NUM:
		{
			fprintf(yyout_syntactic, "EXPRESSION -> real_num\n");
			symbol->Type = "real";
			break;
		}
		case TOKEN_ADDRESS:
		{
			fprintf(yyout_syntactic, "EXPRESSION -> &id\n");
			match(TOKEN_ID);
			back_token();
			Token* token_id = next_token();
			Symbol* idSymbol = Find(symbolTablesList, token_id->lexeme);
			if (idSymbol == NULL)
			{
				fprintf(yyout_semantic, "(line %d) variable '%s' is not defined\n", token_id->lineNumber, token_id->lexeme);
				symbol->Category = null;
				symbol->Name = "undefined";
				symbol->Type = "undefined";
				symbol->SubType = "undefined";
				return symbol;
			}
			else 
			{
				symbol->Type = idSymbol->Type;
				symbol->Category = pointer;
			}

			break;
		}
		case TOKEN_SIZE_OF:
		{
			fprintf(yyout_syntactic, "EXPRESSION -> size_of(type_name)\n");
			match(TOKEN_OPEN_PARENTHESES);
			match(TOKEN_ID);
			match(TOKEN_CLOSE_PARENTHESES);
			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_ID, TOKEN_INT_NUM, TOKEN_REAL_NUM, TOKEN_ADDRESS, TOKEN_SIZE_OF };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 5);

			while(t->kind != TOKEN_LESS && t->kind != TOKEN_GREAT && t->kind != TOKEN_LESS_EQUAL && t->kind != TOKEN_GREATER_EQUAL 
				&& t->kind != TOKEN_NOT_EQUAL && t->kind != TOKEN_EQUAL && t->kind != TOKEN_SEMICOLON
				&& t->kind != TOKEN_CLOSE_BRACKETS && t->kind != TOKEN_EOF)
		
			{
				t = next_token();
			}

			if (t->kind == TOKEN_EOF)
			{
				return;
			}
			else
			{
				t = back_token();
			}
			break;
		}
	}

	return symbol;
}

Symbol* parse_expression_tag()
{
	back_token();
	Token* token_id = next_token();
	Symbol* idSymbol = Find(symbolTablesList, token_id->lexeme);
	Symbol* symbolToReturn = (Symbol*)malloc(sizeof(Symbol));
	if (idSymbol == NULL)
	{
		fprintf(yyout_semantic, "(line %d) variable '%s' not defined\n", token_id->lineNumber, token_id->lexeme);
		symbolToReturn->Category = null;
		symbolToReturn->Name = "undefined";
		symbolToReturn->Type = "undefined";
		symbolToReturn->SubType = "undefined";
		return symbolToReturn;
	}

	Symbol* typeSymbol = get_type_of_symbol(idSymbol);

	Token* t = next_token();
	switch (t->kind)
	{
		case TOKEN_ADDITION:
		case TOKEN_SUBTRACTION:
		case TOKEN_MULTIPLICATION:
		case TOKEN_DIVISION:
		case TOKEN_POWER:
		{
			fprintf(yyout_syntactic, "EXPRESSION' -> ar_op EXPRESSION\n");
			Symbol* symbol_expression = parse_expression();
			symbolToReturn->Type = symbol_expression->Type;
			break;
		}
		case TOKEN_OPEN_BRACKETS:
		case TOKEN_POINTER:
		{
			fprintf(yyout_syntactic, "EXPRESSION' -> RECEIVER'\n");
			back_token();
			Symbol* symbol_receiver_tag = parse_receiver_tag();
			symbolToReturn->Type = symbol_receiver_tag->Type;
			break;
		}
		case TOKEN_CLOSE_BRACKETS:
		case TOKEN_SEMICOLON:
		case TOKEN_EQUAL:
		case TOKEN_NOT_EQUAL:
		case TOKEN_LESS:
		case TOKEN_GREAT:
		case TOKEN_LESS_EQUAL:
		case TOKEN_GREATER_EQUAL:
		{
			fprintf(yyout_syntactic, "EXPRESSION' -> RECEIVER'\n");
			back_token();
			
			symbolToReturn->Type = typeSymbol->Type;

			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_ADDITION, TOKEN_SUBTRACTION, TOKEN_MULTIPLICATION, TOKEN_DIVISION, TOKEN_POWER, TOKEN_OPEN_BRACKETS, TOKEN_POINTER };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 7);

			while (t->kind != TOKEN_LESS && t->kind != TOKEN_GREAT && t->kind != TOKEN_LESS_EQUAL && t->kind != TOKEN_GREATER_EQUAL
				&& t->kind != TOKEN_NOT_EQUAL && t->kind != TOKEN_EQUAL && t->kind != TOKEN_SEMICOLON
				&& t->kind != TOKEN_CLOSE_BRACKETS && t->kind != TOKEN_EOF)
			{
				t = next_token();
			}
			if (t->kind == TOKEN_EOF)
			{
				return;
			}
			else
			{
				t = back_token();
			}
			break;
		}
	}

	return symbolToReturn;
}

void parse_print_error(eTOKENS expected_tokens_kinds[], eTOKENS actual_token_kind, int line_number, char* lexeme, int expected_size)
{
	int i;
	fprintf(yyout_syntactic, "Expected: one of tokens ");
	for (i = 0; i < expected_size; i++)
	{
		fprintf(yyout_syntactic, "%s", get_token_name(expected_tokens_kinds[i]));
		if (i != expected_size - 1)
		{
			fprintf(yyout_syntactic, ", ");
		}
	}
	fprintf(yyout_syntactic, " at line %d,\nActual token: %s, lexeme %s.\n", line_number, get_token_name(actual_token_kind), lexeme);
}

Symbol* get_type_of_symbol(Symbol* idSymbol)
{
	Symbol* typeSymbol = (Symbol*)malloc(sizeof(Symbol));

	if (idSymbol->Role == user_defined_type)
	{
		typeSymbol->Category = idSymbol->Category;
		typeSymbol->Type = idSymbol->SubType;
	}
	else
	{
		if ((idSymbol->Type == "integer") || (idSymbol->Type == "real"))
		{
			typeSymbol->Type = idSymbol->Type;
		}
		else
		{
			Symbol* resultSearch = Find(symbolTablesList, idSymbol->Type);
			if (resultSearch != NULL)
			{
				typeSymbol->Category = resultSearch->Category;
				typeSymbol->Type = resultSearch->SubType;
			}
			else
			{
				typeSymbol->Type = "undefined";
			}
		}
	}

	return typeSymbol;
}