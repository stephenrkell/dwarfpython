#include "ast.h"
/**
 * inherits: ArithOperator
 */
OpMinus *OpMinus::parse(T_MINUS _t)
{
    return new OpMinus();
}
void OpMinus::toStream(std::ostream& strm)
{
    strm << "-";
}
const char *OpMinus::opname()
{
    return "__sub__";
}
