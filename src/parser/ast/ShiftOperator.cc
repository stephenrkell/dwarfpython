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
val ShiftOperator::evaluate()
{
    return None;
}
void ShiftOperator::evaluate_print( std::ostream& strm)
{
    return;
}
