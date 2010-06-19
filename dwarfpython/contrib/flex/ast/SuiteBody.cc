#include "ast.h"
/**
 * inherits: Suite
 * protected: std::vector<Statement*> statements;
 */
SuiteBody *SuiteBody::parse(SingleInput *t)
{
    SuiteBody *sb = new SuiteBody();
    sb->statements.push_back(t);
    return sb;
}
SuiteBody *SuiteBody::parse(SuiteBody *sb, SingleInput *t)
{
    sb->statements.push_back(t);
    return sb;
}
void SuiteBody::toStream(std::ostream& strm)
{
    for (unsigned i=0; i < this->statements.size(); i++)
    {
        strm << this->statements[i] << std::endl;
    }
}

ParathonValue *SuiteBody::evaluate(ParathonContext& c)
{
    ParathonValue *ret;
    for (unsigned i=0; i < this->statements.size(); i++)
    {
        ret = this->statements[i]->evaluate(c);
    }
    return ret;
}
