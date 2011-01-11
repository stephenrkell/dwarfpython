#include "ast.h"
/**
 * inherits: FactExpression
 * virtual: val evaluate();
 */
UnaryPhrase *UnaryPhrase::parse(BasePhrase *bp)
{
    return bp;
}
UnaryPhrase *UnaryPhrase::parse(UnaryOperator *op, UnaryPhrase *up)
{
    UnaryPhrase *e = new UnaryPhrase();
    e->op = op;
    e->rhs = up;
    return e;
}
void UnaryPhrase::toStream(std::ostream& strm)
{
    strm << this->op << this->rhs;
}
