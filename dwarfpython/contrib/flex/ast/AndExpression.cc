#include "ast.h"
/**
 * inherits: XorExpression
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
ParathonValue *AndExpression::evaluate(ParathonContext& c)
{
    ParathonValue *x = this->lhs->evaluate(c);
    if (x)
    {
        return x->call("__and__", this->rhs->evaluate(c));
    }
    std::cerr  << "PHAIL!";
    return NULL;
}
