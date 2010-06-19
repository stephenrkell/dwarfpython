#include "ast.h"
/**
 * inherits: ComparisonOperator
 */
CompNotEq *CompNotEq::parse(T_NOTEQ _t)
{
    return new CompNotEq();
}

void CompNotEq::toStream(std::ostream& strm)
{
    strm << "!=";
}

bool CompNotEq::compare(int result)
{
    return result != 0;
}
const char* CompNotEq::opname()
{
    return "__ne__";
}
