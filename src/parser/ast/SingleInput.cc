#include "ast.h"
/**
 * An Abstract class for either a "block" of code
 * Could be a single line (with semicolons), an "if" statement, a "def", etc.
 * Or even just empty.
 */
SingleInput *SingleInput::parse(T_NEWLINE _t)
{
    return new SimpleStatement();
}

SingleInput *SingleInput::parse(SimpleStatement *simple_statement, T_NEWLINE _t)
{
    return simple_statement;
}
SingleInput *SingleInput::parse(IfStatement *if_statement)
{
    return if_statement;
}
SingleInput *SingleInput::parse(WhileStatement *while_statement)
{
    return while_statement;
}
SingleInput *SingleInput::parse(FunctionDefinition *function_definition)
{
    return function_definition;
}
void SingleInput::evaluate_print( std::ostream& strm)
{
    strm << this->evaluate();
}
