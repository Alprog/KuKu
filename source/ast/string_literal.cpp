
#include "string_literal.h"

ast::string_literal::string_literal(token& token)
	: value{ token.get_source_text() }
{
	value.try_shrink();
}

void ast::string_literal::compile(compiler& compiler)
{

}