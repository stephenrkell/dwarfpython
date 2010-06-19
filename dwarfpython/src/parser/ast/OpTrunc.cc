#include "ast.h"
/**
 * inherits: MultOperator
 */
OpTrunc *OpTrunc::parse(T_TRUNC_DIVIDE _t)
{
    return new OpTrunc();
}
void OpTrunc::toStream(std::ostream& strm)
{
    strm << "//";
}
const char *OpTrunc::opname()
{
    return "__floordiv__";
}
