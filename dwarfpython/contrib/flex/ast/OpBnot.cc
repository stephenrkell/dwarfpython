#include "ast.h"
/**
 * inherits: UnaryOperator
 */
OpBnot *OpBnot::parse(T_BNOT _t)
{
    return new OpBnot();
}
void OpBnot::toStream(std::ostream& strm)
{
    strm << "~";
}
const char *OpBnot::opname()
{
    return "__invert__";
}
