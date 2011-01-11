#include "ast.h"
/**
 * inherits: ComparisonPhrase
 * private: std::vector<Expression *> exprs;
 * private: std::vector<ComparisonOperator *> comps;
 */
ComparisonList *ComparisonList::parse(Expression *exa, ComparisonOperator *co, Expression *exb)
{
    ComparisonList *cl = new ComparisonList();
    cl->exprs.push_back(exa);
    cl->exprs.push_back(exb);
    cl->comps.push_back(co);
    return cl;
}
ComparisonList *ComparisonList::parse(ComparisonList *cl, ComparisonOperator *co, Expression *exb)
{
    cl->exprs.push_back(exb);
    cl->comps.push_back(co);
    return cl;
}
void ComparisonList::toStream(std::ostream& strm)
{
    unsigned i;
    for (i = 0; i < this->comps.size(); i++)
    {
        strm << this->exprs[i];
        strm << " " << this->comps[i] << " ";
    }
    strm << this->exprs[i];
}
val ComparisonList::evaluate()
{
	// evaluate the first element in the list of chained comparisons
	val previous = exprs[0]->evaluate();
	val next;
	for (unsigned i=0; i< comps.size(); i++)
	{
		// evaluate 
		// FIXME: is i+1 safe here? use "at" to allow range checking
		next = exprs.at(i+1)->evaluate();

		// continue the short-circuit conjunction of each comparison
		if (!comps[i]->compare(previous, next))
		{
			// return a value that's False
			return (val) { true, { i_int: 0 }, val::INT };
		}

		previous = next;
	}
	// we got to the end, so return a value that's True
	return (val) { true, { i_int: 1 }, val::INT };
}
