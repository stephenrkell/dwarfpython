#include "ast.h"
/**
 * inherits: SingleInput
 * private: TestPhrase *test;
 * private: Suite *suite;
 */
WhileStatement *WhileStatement::parse(T_WHILE _t, TestPhrase *tp, T_COLON _tt, Suite *s)
{
    WhileStatement *ws = new WhileStatement();
    ws->test = tp;
    ws->suite = s;
    return ws;
}
void WhileStatement::toStream(std::ostream& strm)
{
    strm << "while " << this->test << ":" << this->suite; 
}

val WhileStatement::evaluate(ParathonContext& c)
{
    val r = None;
    while (is_true(this->test->evaluate(c)))
    {
        r = this->suite->evaluate(c);
    }
    return r;
}
