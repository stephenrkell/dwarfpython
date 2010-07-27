#include "ast.h"
/**
 * inherits: ComparisonOperator
 */
CompLt *CompLt::parse(T_LT _t)
{
    return new CompLt();
}

void CompLt::toStream(std::ostream& strm)
{
    strm << "<";
}
const char * CompLt::opname()
{
    return "__lt__";
}
bool CompLt::compare(int result)
{
    return result < 0;
}
