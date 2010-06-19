#include "ast.h"
/**
 * inherits: ShiftOperator
 */
OpLeftShift *OpLeftShift::parse(T_LEFTSHIFT _t)
{
    return new OpLeftShift();
}
void OpLeftShift::toStream(std::ostream& strm)
{
    strm << "<<";
}
