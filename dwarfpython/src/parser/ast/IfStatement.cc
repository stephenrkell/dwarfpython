#include "ast.h"
/**
 * inherits: SingleInput
 * private: TestPhrase *test;
 * private: Suite *true_suite;
 * private: Suite *false_suite;
 */
IfStatement *IfStatement::parse(T_IF _t, TestPhrase *tp, T_COLON _tt, Suite *s)
{
    IfStatement *is = new IfStatement();
    is->test = tp;
    is->true_suite = s;
    return is;
}
IfStatement *IfStatement::parse(IfStatement* is, T_ELSE _t, T_COLON _tt, Suite *s)
{
    is->false_suite = s;
    return is;
}
void IfStatement::toStream(std::ostream& strm)
{
    strm << "if " << this->test << ":" << this->true_suite; 
}

val IfStatement::evaluate(ParathonContext& c)
{
    if (is_true(this->test->evaluate(c)))
    {
        return this->true_suite->evaluate(c);
    }
    else if(this->false_suite)
    {
        return this->false_suite->evaluate(c);
    }
    else
    {
        return None;
    }
}
