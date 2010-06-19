#include "ast.h"
/**
 * inherits: ShiftExpression
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
ParathonValue *ArithExpression::evaluate(ParathonContext& c)
{
    return parathon_call(this->op->opname(), this->lhs->evaluate(c), this->rhs->evaluate(c));
}
