#include "ast.h"
/**
 * inherits: ComparisonOperator
 */
CompEq *CompEq::parse(T_EQ _t)
{
    return new CompEq();
}

void CompEq::toStream(std::ostream& strm)
{
    strm << "==";
}

bool CompEq::compare(int result)
{
    return result == 0;
}
const char* CompEq::opname()
{
    return "__eq__";
}
