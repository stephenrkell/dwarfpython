#include "ast.h"
/**
 * inherits: ComparisonOperator
 */
CompNotIs *CompNotIs::parse(T_IS _t, T_NOT _tt)
{
    return new CompNotIs();
}
void CompNotIs::toStream(std::ostream& strm)
{
    strm << "not in";
}

