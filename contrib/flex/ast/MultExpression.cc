#include "ast.h"
/**
 * inherits: ArithExpression
 */
MultExpression *MultExpression::parse(FactExpression *fe)
{
    return fe;
}
MultExpression *MultExpression::parse(MultExpression *lhs, MultOperator *op, FactExpression *rhs)
{
    MultExpression *e = new MultExpression();
    e->lhs = lhs;
    e->rhs = rhs;
    e->op = op;
    return e;
}
