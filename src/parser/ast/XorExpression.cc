#include "ast.h"
/**
 * inherits: Expression
 * virtual: val evaluate();
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
