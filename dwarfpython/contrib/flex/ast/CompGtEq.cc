#include "ast.h"
/**
 * inherits: ComparisonOperator
 */
CompGtEq *CompGtEq::parse(T_GTEQ _t)
{
    return new CompGtEq();
}

void CompGtEq::toStream(std::ostream& strm)
{
    strm << ">=";
}
const char * CompGtEq::opname()
{
    return "__gte__";
}
bool CompGtEq::compare(int x)
{
    return !((new CompLt())->compare(x));
}
