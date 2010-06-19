#include "ast.h"
/**
 * inherits: OrPhrase
 */
AndPhrase *AndPhrase::parse(NotPhrase *np)
{
    return np;
}
AndPhrase *AndPhrase::parse(AndPhrase *ap, T_AND _t, NotPhrase *np)
{
    AndPhrase *nop = new AndPhrase();
    nop->lhs = ap;
    nop->rhs = np;
    return nop;
}

void AndPhrase::toStream(std::ostream& strm)
{
    strm << "(" << this->lhs << " and " << this->rhs << ")";
}
