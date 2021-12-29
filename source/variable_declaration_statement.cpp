
#include "variable_declaration_statement.h"
#include "variable_node.h"

void Variable_declaration_statement::parse_internal(Parser& parser)
{
    parser.require(Token_type::Keyword_var);
    parser.require(Token_type::Identifier);

    CHECK_END_OF_STATEMENT

    parser.require(Token_type::Assign_operator);

    parser.parse_expression();
}