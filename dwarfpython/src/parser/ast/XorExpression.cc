#include "ast.h"
/**
 * inherits: Expression
 */
XorExpression *XorExpression::parse(AndExpression *ae)
{
    return ae;
}
XorExpression *XorExpression::parse(AndExpression *ae, OpBxor *op, XorExpression *xe)
{
    XorExpression *e = new XorExpression();
    e->lhs = ae;
    e->op = op;
    e->rhs = xe;
    return e;
}
val XorExpression::evaluate(ParathonContext& c)
{
    return parathon_call("__xor__", this->lhs->evaluate(c), this->rhs->evaluate(c));
}
