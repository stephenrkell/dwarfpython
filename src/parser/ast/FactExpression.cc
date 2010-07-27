#include "ast.h"
/**
 * inherits: MultExpression
 */
FactExpression *FactExpression::parse(UnaryPhrase *up)
{
    return up;
}
FactExpression *FactExpression::parse(UnaryPhrase *lhs, OpPower *op, FactExpression *rhs)
{
    FactExpression *e = new FactExpression();
    e->lhs = lhs;
    e->op = op;
    e->rhs = rhs;
    return e;
}
