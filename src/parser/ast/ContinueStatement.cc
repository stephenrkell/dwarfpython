#include "ast.h"
/**
 * inherits: SmallStatement
 */
ContinueStatement *ContinueStatement::parse(T_CONTINUE _t)
{
    return new ContinueStatement();
}
void ContinueStatement::toStream(std::ostream& strm)
{
    strm << "continue";
}
