#include "ast.h"
#include "parathon.h"

/**
 * inherits: SmallStatement
 * private: TestList *tests;
 *
 */
ReturnStatement *ReturnStatement::parse(T_RETURN _t, TestList *tl)
{
    ReturnStatement* r = new ReturnStatement();
    r->tests = tl;
    return r;
}
void ReturnStatement::toStream(std::ostream& strm)
{
    strm << "return " << this->tests;
}
val ReturnStatement::evaluate(ParathonContext& c)
{
    throw new ParathonReturn(tests->evaluate(c));
}
