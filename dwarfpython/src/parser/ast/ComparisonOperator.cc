#include "ast.h"
/*#include "builtins.hh"*/
/**
 * virtual: bool compare(int)
 */
ComparisonOperator *ComparisonOperator::parse(CompLt *co)
{
    return co;
}
ComparisonOperator *ComparisonOperator::parse(CompGt *co)
{
    return co;
}
ComparisonOperator *ComparisonOperator::parse(CompLtEq *co)
{
    return co;
}
ComparisonOperator *ComparisonOperator::parse(CompGtEq *co)
{
    return co;
}
ComparisonOperator *ComparisonOperator::parse(CompEq *co)
{
    return co;
}
ComparisonOperator *ComparisonOperator::parse(CompNotEq *co)
{
    return co;
}
ComparisonOperator *ComparisonOperator::parse(CompIn *co)
{
    return co;
}
ComparisonOperator *ComparisonOperator::parse(CompNotIn *co)
{
    return co;
}
ComparisonOperator *ComparisonOperator::parse(CompIs *co)
{
    return co;
}
ComparisonOperator *ComparisonOperator::parse(CompNotIs *co)
{
    return co;
}
val ComparisonOperator::evaluate(ParathonContext& c)
{
    return None;
}
void ComparisonOperator::evaluate_print(ParathonContext& c, std::ostream& strm)
{
    strm << this->evaluate(c) << std::endl;
}
bool ComparisonOperator::compare(val lhs, val rhs)
{
    //ParathonValue* cmp = BUILTIN__getattr__(&ParathonValue::builtins)(lhs, "__cmp__");
    //if (cmp)
    //    return this->compare(*(parathon_int*)cmp->call(rhs)->value);
    std::cerr << "FIXME: compare not implemented" << std::endl;
    return false;
}
bool ComparisonOperator::compare(int x)
{
    std::cerr << "Tried to compare a virtual operator..." << std::endl;
    return false;
}
