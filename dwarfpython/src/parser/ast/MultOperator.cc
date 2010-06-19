#include "ast.h"
/**
 * inherits: Operator
 */
MultOperator *MultOperator::parse(OpMult *o)
{
    return o;
}
MultOperator *MultOperator::parse(OpDivide *o)
{
    return o;
}
MultOperator *MultOperator::parse(OpTrunc *o)
{
    return o;
}
MultOperator *MultOperator::parse(OpMod *o)
{
    return o;
}
val MultOperator::evaluate(ParathonContext& c)
{
    return None;
}
void MultOperator::evaluate_print(ParathonContext& c, std::ostream& strm)
{
    return;
}
