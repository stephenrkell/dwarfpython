#include "ast.h"
/**
 * inherits: SmallStatement
 */
BreakStatement *BreakStatement::parse(T_BREAK _t)
{
    return new BreakStatement();
}
void BreakStatement::toStream(std::ostream& strm)
{
    strm << "break";
}
