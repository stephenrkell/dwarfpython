#include "ast.h"

/**
 * Abstract class for individual statements.
 *
 * Each subclass (parsed below) inherits from this.
 */
SmallStatement *SmallStatement::parse(PrintStatement *s)
{
    return s;
}
SmallStatement *SmallStatement::parse(ImportStatement *s)
{
    return s;
}
SmallStatement *SmallStatement::parse(DeleteStatement *s)
{
    return s;
}
SmallStatement *SmallStatement::parse(BreakStatement *s)
{
    return s;
}
SmallStatement *SmallStatement::parse(ContinueStatement *s)
{
    return s;
}
SmallStatement *SmallStatement::parse(PassStatement *s)
{
    return s;
}
SmallStatement *SmallStatement::parse(GlobalStatement *s)
{
    return s;
}
SmallStatement *SmallStatement::parse(AssignStatement *s)
{
    return s;
}
SmallStatement *SmallStatement::parse(TestStatement *s)
{
    return s;
}
SmallStatement *SmallStatement::parse(ReturnStatement *s)
{
    return s;
}
val SmallStatement::evaluate()
{
    return None;
}
void SmallStatement::evaluate_print( std::ostream& strm)
{
    strm << this->evaluate() << std::endl;
}
