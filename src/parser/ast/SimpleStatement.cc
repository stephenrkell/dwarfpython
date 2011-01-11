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

void SimpleStatement::evaluate_print( std::ostream& strm)
{
    for (unsigned i=0; i<this->statements.size(); i++)
    {
        this->statements[i]->evaluate_print(strm);
    }
}

val SimpleStatement::evaluate()
{
    for (unsigned i=0; i<this->statements.size(); i++)
    {
        this->statements[i]->evaluate();
    }
    return None;
}
