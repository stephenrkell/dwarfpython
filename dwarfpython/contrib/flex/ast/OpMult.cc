#include "ast.h"
/**
 * inherits: MultOperator
 */
OpMult *OpMult::parse(T_MULTIPLY _t)
{
    return new OpMult();
}
void OpMult::toStream(std::ostream& strm)
{
    strm << "*";
}
const char *OpMult::opname()
{
    return "__mul__";
}
