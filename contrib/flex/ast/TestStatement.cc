#include "ast.h"
/**
 * inherits: SmallStatement
 * virtual: ParathonAssigner* getAssigner(ParathonContext&)
 */
TestStatement *TestStatement::parse(TestPhrase *tp)
{
    return tp;
}
TestStatement *TestStatement::parse(TestListNonTrailing *tp, T_COMMA _t)
{
    return tp;
}
TestStatement *TestStatement::parse(TestListNonTrailing *tl, T_COMMA _t, TestPhrase *tp)
{
    return tl->append(tp);
}
ParathonAssigner *TestStatement::getAssigner(ParathonContext& c)
{
    return NULL;
}
