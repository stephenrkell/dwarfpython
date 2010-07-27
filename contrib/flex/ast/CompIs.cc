#include "ast.h"
/**
 * inherits: ComparisonOperator
 */
CompIs *CompIs::parse(T_IS _t)
{
    return new CompIs();
}
void CompIs::toStream(std::ostream& strm)
{
    strm << "is";
}

