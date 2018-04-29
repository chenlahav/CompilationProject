#include "Token.h"
#include "Parser.h"
#include "string.h"

void parse_program()
{
	//TODO: print to output file
	printf("PROGRAM -> BLOCK\n");
	parse_block();
}

void parse_block()
{
	//TODO: print to output file
	printf("BLOCK -> block DEFINITIONS; begin COMMANDS; end\n");
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
	printf("DEFINITIONS -> DEFINITION DEFINITIONS'\n");
	parse_definition();
	parse_definitions_tag();
}

void parse_definitions_tag()
{
	Token* t = next_token();
	Token* next_t = next_token();
	switch (t->kind)
	{
		case TOKEN_SEMICOLON:
		{
			switch (next_t->kind)
			{
				case TOKEN_BEGIN:
				{
					//TODO: print to output file
					printf("DEFINITIONS' -> e\n");
					back_token();
					back_token();
					break;
				}
				case TOKEN_ID:
				case TOKEN_TYPE:
				{
					//TODO: print to output file
					printf("DEFINITIONS' -> ;DEFINITION DEFINITIONS'\n");
					back_token();
					parse_definition();
					parse_definitions_tag();
					break;
				}
				default:
				{
					eTOKENS expected_tokens[] = { TOKEN_ID, TOKEN_TYPE };
					parse_print_error(expected_tokens, next_t->kind, next_t->lineNumber, next_t->lexeme, 2);
					while(next_t->kind != TOKEN_ID && next_t->kind != TOKEN_TYPE && next_t->kind != TOKEN_BEGIN && next_t->kind != TOKEN_EOF)
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
	switch (t->kind)
	{
		case TOKEN_ID:
		{
			back_token();
			//TODO: print to output file
			printf("DEFINITION -> VAR_DEFINITION\n");
			parse_var_definition();
			break;
		}
		case TOKEN_TYPE:
		{
			back_token();
			//TODO: print to output file
			printf("DEFINITION -> TYPE_DEFINITION\n");
			parse_type_definition();
			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_ID, TOKEN_TYPE };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 2);
			while (t->kind != TOKEN_ID && t->kind != TOKEN_TYPE && t->kind != TOKEN_EOF)
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
	//TODO: print to output file
	printf("VAR_DEFINITION -> id : VAR_DEFINITION'\n");
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
			printf("VAR_DEFINITION' -> BASIC_TYPE\n");
			parse_basic_type();
			break;
		}
		case TOKEN_ID:
		{
			//TODO: print to output file
			printf("VAR_DEFINITION' -> type_name\n");
			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_INTEGER, TOKEN_REAL, TOKEN_ID };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 3);
			while (t->kind != TOKEN_INTEGER && t->kind != TOKEN_REAL && t->kind != TOKEN_ID && t->kind != TOKEN_EOF)
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
	//TODO: print to output file
	printf("TYPE_DEFINITION -> type type_name is TYPE_INDICATOR\n");
	
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
			printf("TYPE_INDICATOR -> BASIC_TYPE\n");
			parse_basic_type();
			break;
		}
		case TOKEN_ARRAY:
		{
			back_token();
			//TODO: print to output file
			printf("TYPE_INDICATOR -> ARRAY_TYPE\n");
			parse_array_type();
			break;
		}
		case TOKEN_POINTER:
		{
			back_token();
			//TODO: print to output file
			printf("TYPE_INDICATOR -> POINTER_TYPE\n");
			parse_pointer_type();
			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_INTEGER, TOKEN_REAL , TOKEN_ARRAY, TOKEN_POINTER};
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 4);
			while (t->kind != TOKEN_INTEGER && t->kind != TOKEN_REAL && t->kind != TOKEN_ARRAY && t->kind != TOKEN_POINTER && t->kind != TOKEN_EOF)
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
	switch (t->kind)
	{
		case TOKEN_INTEGER:
		{
			//TODO: print to output file
			printf("BASIC_TYPE -> integer\n");
			break;
		}
		case TOKEN_REAL:
		{
			//TODO: print to output file
			printf("BASIC_TYPE -> real\n");
			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_INTEGER, TOKEN_REAL };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 2);
			while (t->kind != TOKEN_INTEGER && t->kind != TOKEN_REAL && t->kind != TOKEN_EOF)
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
	//TODO: print to output file
	printf("ARRAY_TYPE -> array [SIZE] of BASIC_TYPE\n");
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
	printf("POINTER_TYPE -> ^POINTER_TYPE'\n");
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
			printf("VAR_DEFINITION' -> BASIC_TYPE\n");
			parse_basic_type();
			break;
		}
		case TOKEN_ID:
		{
			//TODO: print to output file
			printf("VAR_DEFINITION' -> type_name\n");
			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_INTEGER, TOKEN_REAL, TOKEN_ID };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 3);
			while (t->kind != TOKEN_INTEGER && t->kind != TOKEN_REAL && t->kind != TOKEN_ID && t->kind != TOKEN_POINTER 
				&& t->kind != TOKEN_EOF)
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
	//TODO: print to output file
	printf("SIZE -> int_num\n");
	match(TOKEN_INT_NUM);
}

void parse_commands() 
{
	//TODO: print to output file
	printf("COMMANDS -> COMMAND COMMANDS'\n");
	parse_command();
	parse_commands_tag();
}

void parse_commands_tag()
{
	Token* t = next_token();
	Token* next_t = next_token();
	switch (t->kind)
	{
		case TOKEN_SEMICOLON:
		{
			switch (next_t->kind)
			{
				case TOKEN_END:
				case TOKEN_END_FOR:
				case TOKEN_END_WHEN:
				case TOKEN_DEFAULT:
				{
					//TODO: print to output file
					printf("COMMANDS' -> e\n");
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
					//TODO: print to output file
					printf("COMMANDS' -> ;COMMAND COMMANDS'\n");
					back_token();
					parse_command();
					parse_commands_tag();
					break;
				}
				default:
				{
					eTOKENS expected_tokens[] = { TOKEN_END, TOKEN_ID , TOKEN_WHEN, TOKEN_FOR, TOKEN_FREE, TOKEN_BLOCK, TOKEN_END_FOR, TOKEN_END_WHEN, TOKEN_DEFAULT};
					parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 9);
					while (t->kind != TOKEN_END && t->kind != TOKEN_ID && t->kind != TOKEN_WHEN && t->kind != TOKEN_FOR &&
						t->kind != TOKEN_FREE && t->kind != TOKEN_BLOCK && t->kind != TOKEN_END_FOR
						&& t->kind != TOKEN_END_WHEN && t->kind != TOKEN_DEFAULT && t->kind != TOKEN_EOF)
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
			//TODO: print to output file
			printf("COMMAND -> id  COMMAND'\n");
			parse_command_tag();
			break;
		}
		case TOKEN_WHEN:
		{
			//TODO: print to output file
			printf("COMMAND -> when (EXPRESSION rel_op EXPRESSION) do COMMANDS; default COMMANDS; end_when\n");
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
					//TODO: print match_print_error

					while (next_t->kind != TOKEN_EQUAL && next_t->kind != TOKEN_NOT_EQUAL && next_t->kind != TOKEN_LESS
						&& next_t->kind != TOKEN_GREAT && next_t->kind != TOKEN_LESS_EQUAL && next_t->kind != TOKEN_GREATER_EQUAL
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
			//TODO: print to output file
			printf("COMMAND -> for (id = EXPRESSION; id rel_op EXPRESSION; id++) COMMANDS; end_for\n");
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
					//TODO: print match_print_error

					while (next_t->kind != TOKEN_EQUAL && next_t->kind != TOKEN_NOT_EQUAL && next_t->kind != TOKEN_LESS
						&& next_t->kind != TOKEN_GREAT && next_t->kind != TOKEN_LESS_EQUAL && next_t->kind != TOKEN_GREATER_EQUAL
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
			//TODO: print to output file
			printf("COMMAND -> free(id)\n");
			match(TOKEN_OPEN_PARENTHESES);
			match(TOKEN_ID);
			match(TOKEN_CLOSE_PARENTHESES);
			break;
		}
		case TOKEN_BLOCK:
		{
			//TODO: print to output file
			printf("COMMAND -> BLOCK\n");
			back_token();
			parse_block();
			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_ID, TOKEN_WHEN, TOKEN_FOR, TOKEN_FREE, TOKEN_BLOCK };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 5);

			while(t->kind != TOKEN_ID && t->kind != TOKEN_WHEN && t->kind != TOKEN_FOR && t->kind != TOKEN_FREE
				&& t->kind != TOKEN_BLOCK && t->kind != TOKEN_EOF)
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
			//TODO: print to output file
			printf("COMMAND' -> RECEIVER' = EXPRESSION\n");
			back_token();
			parse_receiver_tag();
			match(TOKEN_ASSIGNMENT);
			parse_expression();
			break;
		}
		case TOKEN_ASSIGNMENT:
		{
			Token* next_t = next_token();
			switch (next_t->kind)
			{
				case TOKEN_MALLOC:
				{
					//TODO: print to output file
					printf("COMMAND' -> = malloc(size_of(type_name))\n");
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
					//TODO: print to output file
					printf("COMMAND' -> RECEIVER' = EXPRESSION\n");
					back_token();
					back_token();
					parse_receiver_tag();
					match(TOKEN_ASSIGNMENT);
					parse_expression();
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

			while (t->kind != TOKEN_OPEN_BRACKETS && t->kind != TOKEN_POINTER && t->kind != TOKEN_ASSIGNMENT
				&& t->kind != TOKEN_EOF) 
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
	//TODO: print to output file
	printf("RECEIVER -> id RECEIVER’\n");
	match(TOKEN_ID);
	parse_receiver_tag();
}

void parse_receiver_tag()
{
	Token* t = next_token();
	switch (t->kind)
	{
		case TOKEN_OPEN_BRACKETS:
		{
			//TODO: print to output file
			printf("RECEIVER' -> [EXPRESSION]\n");
			parse_expression();
			match(TOKEN_CLOSE_BRACKETS);
			break;
		}
		case TOKEN_POINTER:
		{
			//TODO: print to output file
			printf("RECEIVER' -> ^\n");
			break;
		}
		case TOKEN_ASSIGNMENT:
		{
			//TODO: print to output file
			printf("RECEIVER' -> e\n");
			back_token();
			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_OPEN_BRACKETS, TOKEN_POINTER };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 2);

			while (t->kind != TOKEN_OPEN_BRACKETS && t->kind != TOKEN_POINTER && t->kind != TOKEN_EOF) 
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
}

void parse_expression()
{
	Token* t = next_token();
	switch (t->kind)
	{
		case TOKEN_ID:
		{
			//TODO: print to output file
			printf("EXPRESSION -> id EXPRESSION'\n");
			parse_expression_tag();
			break;
		}
		case TOKEN_INT_NUM:
		{
			//TODO: print to output file
			printf("EXPRESSION -> int_num\n");
			break;
		}
		case TOKEN_REAL_NUM:
		{
			//TODO: print to output file
			printf("EXPRESSION -> real_num\n");
			break;
		}
		case TOKEN_ADDRESS:
		{
			//TODO: print to output file
			printf("EXPRESSION -> &id\n");
			match(TOKEN_ID);
			break;
		}
		case TOKEN_SIZE_OF:
		{
			//TODO: print to output file
			printf("EXPRESSION -> size_of(type_name)\n");
			match(TOKEN_OPEN_PARENTHESES);
			match(TOKEN_ID);
			match(TOKEN_OPEN_PARENTHESES);
			break;
		}

		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_ID, TOKEN_INT_NUM, TOKEN_REAL_NUM, TOKEN_ADDRESS, TOKEN_SIZE_OF };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 5);

			while(t->kind != TOKEN_ID && t->kind != TOKEN_INT_NUM && t->kind != TOKEN_REAL_NUM && t->kind != TOKEN_ADDRESS
				&& t->kind != TOKEN_SIZE_OF && t->kind != TOKEN_EOF)
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

void parse_expression_tag()
{
	Token* t = next_token();
	switch (t->kind)
	{
		case TOKEN_ADDITION:
		case TOKEN_SUBTRACTION:
		case TOKEN_MULTIPLICATION:
		case TOKEN_DIVISION:
		case TOKEN_POWER:
		{
			//TODO: print to output file
			printf("EXPRESSION' -> ar_op EXPRESSION\n");
			parse_expression();
			break;
		}
		case TOKEN_OPEN_BRACKETS:
		case TOKEN_POINTER:
		{
			//TODO: print to output file
			printf("EXPRESSION' -> RECEIVER'\n");
			back_token();
			parse_receiver_tag();
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
			//TODO: print to output file
			printf("EXPRESSION' -> RECEIVER'\n");
			back_token();
			break;
		}
		default:
		{
			eTOKENS expected_tokens[] = { TOKEN_ADDITION, TOKEN_SUBTRACTION, TOKEN_MULTIPLICATION, TOKEN_DIVISION, TOKEN_POWER, TOKEN_OPEN_BRACKETS, TOKEN_POINTER };
			parse_print_error(expected_tokens, t->kind, t->lineNumber, t->lexeme, 7);

			while (t->kind != TOKEN_ADDITION && t->kind != TOKEN_SUBTRACTION && t->kind != TOKEN_MULTIPLICATION && t->kind != TOKEN_DIVISION && t->kind != TOKEN_POWER
				&& t->kind != TOKEN_OPEN_BRACKETS && t->kind != TOKEN_POINTER && t->kind != TOKEN_EOF)
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

void error_handle(eTOKENS follow, Token* current_token)
{
	while (current_token->kind != follow && current_token->kind != TOKEN_EOF)
	{
		current_token = next_token();
	}

	if (current_token->kind == TOKEN_EOF)
	{
		return;
	}
	else
	{
		current_token = back_token();
	}
}

void parse_print_error(eTOKENS expected_tokens_kinds[], eTOKENS actual_token_kind, int line_number, char* lexeme, int expected_size)
{
	int i;
	//TODO: print to output file
	printf("Expected: one of tokens ");
	for (i = 0; i < expected_size; i++)
	{
		printf("%d", (int)expected_tokens_kinds[i]);
		if (i != expected_size - 1)
		{
			printf(", ");
		}
	}
	printf(" at line %d,\nActual token: %d, lexeme %s.\n", line_number, (int)actual_token_kind, lexeme);
}