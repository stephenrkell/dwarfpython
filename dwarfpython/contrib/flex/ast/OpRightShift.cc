#include "ast.h"
/**
 * inherits: ShiftOperator
 */
OpRightShift *OpRightShift::parse(T_RIGHTSHIFT _t)
{
    return new OpRightShift();
}
void OpRightShift::toStream(std::ostream& strm)
{
    strm << ">>";
}
