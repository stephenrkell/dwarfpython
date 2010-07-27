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
val AndExpression::evaluate(ParathonContext& c)
{
    val x = this->lhs->evaluate(c);
    if (is_true(x))
    {
        //return lookup_and_call(x, "__and__", this->rhs->evaluate(c));
        std::cerr << "FIXME: AND expression not implemented."  << std::endl;
        //return lookup_and_call(x, "__and__", this->rhs->evaluate(c));
    }
    std::cerr  << "PHAIL!";
    return None;
}
