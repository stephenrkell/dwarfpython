#include "ast.h"
/**
 * inherits: TestPhrase
 * protected: TestPhrase *lhs;
 * protected: TestPhrase *rhs;
 */
OrPhrase *OrPhrase::parse(AndPhrase *ap)
{
    return ap;
}
OrPhrase *OrPhrase::parse(OrPhrase *op, T_OR _t, AndPhrase *ap)
{
    OrPhrase *nop = new OrPhrase();
    nop->lhs = op;
    nop->rhs = ap;
    return nop;
}

void OrPhrase::toStream(std::ostream& strm)
{
    strm << "(" << this->lhs << " or " << this->rhs << ")";
}

