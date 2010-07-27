#include "ast.h"
/**
 * inherits: Operator
 */
ArithOperator *ArithOperator::parse(OpPlus *op)
{
    return op;
}
ArithOperator *ArithOperator::parse(OpMinus *op)
{
    return op;
}
val ArithOperator::evaluate(ParathonContext& c)
{
    return None;
}
void ArithOperator::evaluate_print(ParathonContext& c,std::ostream& strm)
{
    return;
}
