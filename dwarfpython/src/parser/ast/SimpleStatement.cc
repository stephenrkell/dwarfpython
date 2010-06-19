#include "ast.h"
/**
 * A simple statement is essentially one line - i.e. multiple ; separated expressions
 * inherits: SuiteBody
 */
SimpleStatement *SimpleStatement::parse(SmallStatement *ss)
{
    SimpleStatement *s = new SimpleStatement();
    s->statements.push_back(ss);
    return s;
}
SimpleStatement *SimpleStatement::parse(SimpleStatement *s, T_SEMICOLON _t)
{
    return s;
}
SimpleStatement *SimpleStatement::parse(SimpleStatement *s, T_SEMICOLON _t, SmallStatement *ss)
{
    s->statements.push_back(ss);
    return s;
}

void SimpleStatement::toStream(std::ostream& strm)
{
    for (unsigned i=0; i<this->statements.size(); i++)
    {
        strm << this->statements[i] << (i+1 >= this->statements.size() ? "" : ";");
    }
}

void SimpleStatement::evaluate_print(ParathonContext& c, std::ostream& strm)
{
    for (unsigned i=0; i<this->statements.size(); i++)
    {
        this->statements[i]->evaluate_print(c, strm);
    }
}

val SimpleStatement::evaluate(ParathonContext& c)
{
    for (unsigned i=0; i<this->statements.size(); i++)
    {
        this->statements[i]->evaluate(c);
    }
    return None;
}
