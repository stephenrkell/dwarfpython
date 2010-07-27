#include "ast.h"
/**
 * inherits: SmallStatement
 */
PassStatement *PassStatement::parse(T_PASS _t)
{
    return new PassStatement();
}
void PassStatement::toStream(std::ostream& strm)
{
    strm << "pass";
}
