#include "Token.h"
#include "Symbol.h"


void create_new_symbol();
void parse_program();
void parse_block();
void parse_definitions();
void parse_definitions_tag();
void parse_definition();
void parse_var_definition();
void parse_var_definition_tag();
void parse_type_definition();
void parse_type_indicator();
void parse_basic_type();
void parse_array_type();
void parse_pointer_type();
void parse_pointer_type_tag();
void parse_size();
void parse_commands();
void parse_commands_tag();
void parse_command();
void parse_command_tag();
void parse_receiver();
Symbol* parse_receiver_tag();
Symbol* parse_expression();
Symbol* parse_expression_tag();
void parse_print_error(eTOKENS expected_tokens_kinds[], eTOKENS actual_token_kind, int line_number, char* lexeme, int expected_size);
char* get_token_name(int token_number);
Symbol* get_type_of_symbol(Symbol* idSymbol);
