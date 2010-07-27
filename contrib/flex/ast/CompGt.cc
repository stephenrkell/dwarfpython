#include "ast.h"
/**
 * inherits: ComparisonOperator
 */
CompGt *CompGt::parse(T_GT _t)
{
    return new CompGt();
}

void CompGt::toStream(std::ostream& strm)
{
    strm << ">";
}
const char * CompGt::opname()
{
    return "__gt__";
}
bool CompGt::compare(int result)
{
    return result > 0;
}
