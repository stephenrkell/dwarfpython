#include "ast.h"
/**
 * inherits: MultOperator
 */
OpMod *OpMod::parse(T_MODULUS _t)
{
    return new OpMod();
}
void OpMod::toStream(std::ostream& strm)
{
    strm << "%";
}
const char *OpMod::opname()
{
    return "__mod__";
}
