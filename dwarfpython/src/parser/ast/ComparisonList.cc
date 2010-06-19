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
val ComparisonList::evaluate(ParathonContext& c)
{
    val previous = exprs[0]->evaluate(c);
    val next;
    for (unsigned i=0; i< comps.size(); i++)
    {
        next = exprs[i+1]->evaluate(c);
        //if (!comps[i]->compare(previous, next))
        //        return new ParathonValue((parathon_int)0);
        
        previous = next;
    }
    return None;//new ParathonValue((parathon_int)1);
}
