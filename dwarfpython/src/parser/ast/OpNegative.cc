#include "ast.h"
/**
 * inherits: UnaryOperator
 */
OpNegative *OpNegative::parse(T_MINUS _t)
{
    return new OpNegative();
}
void OpNegative::toStream(std::ostream& strm)
{
    strm << "-";
}
const char *OpNegative::opname()
{
    return "__neg__";

}
