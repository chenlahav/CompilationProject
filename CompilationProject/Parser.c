#include "Token.h"
#include "Parser.h"

void parse_program()
{
	//TODO: print to output file
	printf("PROGRAM -> BLOCK");
	parse_block();
}

void parse_block()
{
	//TODO: print to output file
	printf("BLOCK -> block DEFINITIONS; begin COMMANDS; end");
	match(TOKEN_BLOCK);
	parse_definitions();
	match(TOKEN_SEMICOLON);
	match(TOKEN_BEGIN);
	parse_commands();
	match(TOKEN_SEMICOLON);
	match(TOKEN_END);
}

void parse_definitions()
{
	//TODO: print to output file
	printf("DEFINITIONS -> DEFINITION DEFINITIONS’");
	parse_definition();
	parse_definitions_tag();
}

void parse_definitions_tag()
{
	Token* t = next_token();
	switch (t->kind)
	{
	case TOKEN_SEMICOLON:
		//TODO: print to output file
		printf("DEFINITIONS’ -> ;DEFINITION DEFINITIONS’");
		parse_definition();
		parse_definitions_tag();
		break;
	default:
		break;
	}
}

void parse_definition()
{
	//TODO: print to output file
	Token* t = next_token();
	switch (t->kind)
	{
		case TOKEN_ID:
		{
			back_token();
			//TODO: print to output file
			printf("DEFINITION -> VAR_DEFINITION");
			parse_var_definition();
			break;
		}
		case TOKEN_TYPE:
		{
			back_token();
			//TODO: print to output file
			printf("DEFINITION -> TYPE_DEFINITION");
			parse_type_definition();
			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_ID, TOKEN_TYPE };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 2);
			break;
		}
		
	}
}

void parse_var_definition()
{
	//TODO: print to output file
	printf("VAR_DEFINITION -> id : VAR_DEFINITION’");
	match(TOKEN_ID);
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
			//TODO: print to output file
			printf("VAR_DEFINITION’ -> BASIC_TYPE");
			parse_basic_type();
			break;
		}
		case TOKEN_ID:
		{
			//TODO: print to output file
			printf("VAR_DEFINITION’ -> type_name");
			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_INTEGER, TOKEN_REAL, TOKEN_ID };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 3);
			break;
		}
	}
}

void parse_type_definition() 
{
	//TODO: print to output file
	printf("TYPE_DEFINITION -> type type_name is TYPE_INDICATOR");
	
	match(TOKEN_TYPE);
	match(TOKEN_ID);
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
			//TODO: print to output file
			printf("TYPE_INDICATOR -> BASIC_TYPE");
			parse_basic_type();
			break;
		}
		case TOKEN_ARRAY:
		{
			back_token();
			//TODO: print to output file
			printf("TYPE_INDICATOR -> ARRAY_TYPE");
			parse_array_type();
			break;
		}
		case TOKEN_POINTER:
		{
			back_token();
			//TODO: print to output file
			printf("TYPE_INDICATOR -> POINTER_TYPE");
			parse_pointer_type();
			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_INTEGER, TOKEN_REAL , TOKEN_ARRAY, TOKEN_POINTER};
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 4);
			break;
		}
	}
}

void parse_basic_type()
{
	Token *t = next_token();
	switch (t->kind)
	{
		case TOKEN_INTEGER:
		{
			//TODO: print to output file
			printf("BASIC_TYPE -> integer");
			break;
		}
		case TOKEN_REAL:
		{
			//TODO: print to output file
			printf("BASIC_TYPE -> real");
			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_INTEGER, TOKEN_REAL };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 2);
			break;
		}
	}
}

void parse_array_type()
{
	//TODO: print to output file
	printf("ARRAY_TYPE -> array [SIZE] of BASIC_TYPE ");
	match(TOKEN_ARRAY);
	match(TOKEN_OPEN_BRACKETS);
	parse_size();
	match(TOKEN_CLOSE_BRACKETS);
	match(TOKEN_OF);
	parse_basic_type();
}

void parse_pointer_type()
{
	//TODO: print to output file
	printf("POINTER_TYPE -> ^POINTER_TYPE'");
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
			//TODO: print to output file
			printf("VAR_DEFINITION’ -> BASIC_TYPE");
			parse_basic_type();
			break;
		}
		case TOKEN_ID:
		{
			//TODO: print to output file
			printf("VAR_DEFINITION’ -> type_name");
			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_INTEGER, TOKEN_REAL, TOKEN_ID };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 3);
			break;
		}
	}
}

void parse_size()
{
	//TODO: print to output file
	printf("SIZE -> int_num");
	match(TOKEN_INT_NUM);
}

void parse_commands() {

}

void parse_print_error(eTOKENS expected_tokens[], eTOKENS actual_token, int line_number, char lexeme, int expected_size)
{
	int i;
	//TODO: print to output file
	printf("Expected: one of tokens ");
	for (i = 0; i < expected_size; i++)
	{
		printf("%s", expected_tokens[i]);
		if (i != expected_size - 1)
		{
			printf(", ");
		}
	}
	printf("at line %d,\nActual token: %s, lexeme %c.", line_number, actual_token, lexeme);
}