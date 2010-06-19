#include "ast.h"
/**
 * inherits: AndPhrase
 */
NotPhrase *NotPhrase::parse(ComparisonPhrase *cp)
{
    return cp;
}
NotPhrase *NotPhrase::parse(T_NOT _t, NotPhrase *ap)
{
    NotPhrase *nop = new NotPhrase();
    nop->lhs = NULL;
    nop->rhs = ap;
    return nop;
}

void NotPhrase::toStream(std::ostream& strm)
{
    strm << "(not " << this->rhs << ")";
}
