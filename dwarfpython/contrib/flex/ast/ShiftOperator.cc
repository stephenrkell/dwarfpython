#include "ast.h"
/**
 * inherits: Operator
 */
ShiftOperator *ShiftOperator::parse(OpLeftShift *o)
{
    return o;
}
ShiftOperator *ShiftOperator::parse(OpRightShift *o)
{
    return o;
}
ParathonValue *ShiftOperator::evaluate(ParathonContext& c)
{
    return NULL;
}
void ShiftOperator::evaluate_print(ParathonContext& c, std::ostream& strm)
{
    return;
}
