#include "Token.h"

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
void parse_receiver_tag();
void parse_expression();
void parse_expression_tag();
void parse_print_error(eTOKENS expected_tokens[], eTOKENS actual_token, int line_number, char lexeme, int expected_size);