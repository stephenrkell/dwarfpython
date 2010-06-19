#include "ast.h"
/**
 * inherits: ComparisonOperator
 */
CompNotIn *CompNotIn::parse(T_NOT _t, T_IN _tt)
{
    return new CompNotIn();
}
void CompNotIn::toStream(std::ostream& strm)
{
    strm << "not in";
}

