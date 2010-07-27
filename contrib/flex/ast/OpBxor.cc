#include "ast.h"
/**
 * inherits: UnaryOperator
 */
OpBxor *OpBxor::parse(T_BXOR _t)
{
    return new OpBxor();
}
void OpBxor::toStream(std::ostream& strm)
{
    strm << "^";
}
const char *OpBxor::opname()
{
    return "__xor__";
}
