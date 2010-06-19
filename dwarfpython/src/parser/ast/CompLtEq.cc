#include "ast.h"
/**
 * inherits: ComparisonOperator
 */
CompLtEq *CompLtEq::parse(T_LTEQ _t)
{
    return new CompLtEq();
}

void CompLtEq::toStream(std::ostream& strm)
{
    strm << "<=";
}

bool CompLtEq::compare(int result)
{
    return result <= 0;
}
const char * CompLtEq::opname()
{
    return "__le__";
}
