#include "ast.h"
/**
 * inherits: ComparisonOperator
 */
CompIn *CompIn::parse(T_IN _t)
{
    return new CompIn();
}

void CompIn::toStream(std::ostream& strm)
{
    strm << "in";
}

