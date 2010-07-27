#include "ast.h"
/**
 * inherits: UnaryOperator
 */
OpBor *OpBor::parse(T_BOR _t)
{
    return new OpBor();
}
void OpBor::toStream(std::ostream& strm)
{
    strm << "|";
}
const char *OpBor::opname()
{
    return "__or__";
}
