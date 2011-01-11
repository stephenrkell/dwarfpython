#include "ast.h"
/*#include "builtins.hh"*/
/**
 * virtual: bool compare(int)
 * virtual: bool compare(val lhs, val rhs)
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
val ComparisonOperator::evaluate()
{
    return None;
}
void ComparisonOperator::evaluate_print(std::ostream& strm)
{
    strm << this->evaluate() << std::endl;
}
bool ComparisonOperator::compare(int x)
{
	std::cerr 	<< "Warning: ComparisonOperator::compare() called -- "
				<< "BUG meaning a comparison operator subclass is missing its compare()." 
				<< std::endl;
	return false;
}
