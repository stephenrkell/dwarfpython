#include "ast.h"
/**
 * inherits: AndExpression
 */
ShiftExpression *ShiftExpression::parse(ArithExpression *ae)
{
    return ae;
}
ShiftExpression *ShiftExpression::parse(ShiftExpression *lhs, ShiftOperator *op, ArithExpression *rhs)
{
    ShiftExpression *e = new ShiftExpression();
    e->op = op;
    e->lhs = lhs;
    e->rhs = rhs;
    return e;
}
