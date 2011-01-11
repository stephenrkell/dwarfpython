#include "ast.h"
/**
 * inherits: SingleInput
 * private: TestPhrase *test;
 * private: Suite *suite;
 * virtual: val evaluate();
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

