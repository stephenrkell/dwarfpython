#include "ast.h"
/**
 * inherits: ArithOperator
 */
OpPlus *OpPlus::parse(T_PLUS _t)
{
    return new OpPlus();
}
void OpPlus::toStream(std::ostream& strm)
{
    strm << "+";
}
const char *OpPlus::opname()
{
    return "__add__";
}
