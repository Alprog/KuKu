
#include "variable_declaration_statement.h"
#include "ast/expression.h"

void stmt::variable_declaration_statement::parse_internal(parser& parser)
{
    parser.require(token_type::Keyword_var);
    parse_symbol(parser);

    if (parser.match(token_type::Colon))
    {
        parser.require(token_type::Identifier);
        CHECK_END_OF_STATEMENT
    }

    parser.require(token_type::Assign_operator);
    expression = parser.parse_expression();
}

void stmt::variable_declaration_statement::semantic_analyze()
{
    if (expression != nullptr)
    {
        expression->semantic_analyze(*this);
    }
}

void stmt::variable_declaration_statement::define_symbols(statement_scope* scope)
{
    scope->define_symbol(symbol);
}

void stmt::variable_declaration_statement::compile(compiler& compiler)
{
    expression->compile(compiler);
}