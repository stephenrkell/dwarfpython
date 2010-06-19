#include "ast.h"
/**
 * inherits: ArithOperator
 */
OpPower *OpPower::parse(T_POWER _t)
{
    return new OpPower();
}
void OpPower::toStream(std::ostream& strm)
{
    strm << "**";
}
const char *OpPower::opname()
{
    return "__pow__";
}
