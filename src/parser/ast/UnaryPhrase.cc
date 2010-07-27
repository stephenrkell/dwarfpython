#include "ast.h"
/**
 * inherits: FactExpression
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
val UnaryPhrase::evaluate(ParathonContext& c)
{
    return parathon_call(this->op->opname(), this->rhs->evaluate(c));
}
