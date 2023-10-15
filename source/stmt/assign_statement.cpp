
#include "assign_statement.h"
#include "unexepected_error.h"
#include "compiler.h"

stmt::assign_statement::assign_statement(std::unique_ptr<ast::expression> expression)
	: lvalue{ std::move(expression) }
{
}

void stmt::assign_statement::parse_internal(parser& parser)
{
	parser.require(token_type::Assign_operator);
	rvalue = parser.parse_expression();
	if (!rvalue)
	{
		throw unexpected_error();
	}
}

void stmt::assign_statement::semantic_analyze()
{
	lvalue->semantic_analyze(*this);
	rvalue->semantic_analyze(*this);
}

void stmt::assign_statement::compile(compiler& compiler)
{
	compiler.compile(*this);
}