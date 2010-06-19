#include "ast.h"
/**
 * inherits: Operator
 */
UnaryOperator *UnaryOperator::parse(OpNegative *o)
{
    return o;
}
UnaryOperator *UnaryOperator::parse(OpPositive *o)
{
    return o;
}
UnaryOperator *UnaryOperator::parse(OpBnot *o)
{
    return o;
}
ParathonValue *UnaryOperator::evaluate(ParathonContext& c)
{
    return NULL;
}
void UnaryOperator::evaluate_print(ParathonContext& c, std::ostream& strm)
{
    return;
}
