#include "ast.h"
/**
 * inherits: ShiftExpression
 * virtual: val evaluate()
 */
ArithExpression *ArithExpression::parse(MultExpression *me)
{
    return me;
}
ArithExpression *ArithExpression::parse(ArithExpression *lhs, ArithOperator *op, MultExpression *rhs)
{
    ArithExpression *e = new ArithExpression();
    e->lhs = lhs;
    e->rhs = rhs;
    e->op = op;
    return e;
}
