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
val MultOperator::evaluate()
{
    return None;
}
void MultOperator::evaluate_print( std::ostream& strm)
{
    return;
}
