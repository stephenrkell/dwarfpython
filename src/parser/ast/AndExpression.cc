#include "ast.h"
/**
 * inherits: XorExpression
 * virtual: val evaluate()
 */
AndExpression *AndExpression::parse(ShiftExpression *se)
{
    return se;
}
AndExpression *AndExpression::parse(ShiftExpression *lhs, OpBand *op, AndExpression *rhs)
{
    AndExpression *e = new AndExpression();
    e->lhs = lhs;
    e->op = op;
    e->rhs = rhs;
    return e;
}
