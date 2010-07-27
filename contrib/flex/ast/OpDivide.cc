#include "ast.h"
/**
 * inherits: MultOperator
 */
OpDivide *OpDivide::parse(T_DIVIDE _t)
{
    return new OpDivide();
}
void OpDivide::toStream(std::ostream& strm)
{
    strm << "/";
}
const char *OpDivide::opname()
{
    return "__truediv__";
}
