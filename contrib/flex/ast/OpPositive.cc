#include "ast.h"
/**
 * inherits: UnaryOperator
 */
OpPositive *OpPositive::parse(T_PLUS _t)
{
    return new OpPositive();
}
void OpPositive::toStream(std::ostream& strm)
{
    strm << "+";
}
const char *OpPositive::opname()
{
    return "__pos__";
}
