#include "ast.h"
/**
 * inherits: Suite
 * protected: std::vector<Statement*> statements;
 * virtual: val evaluate()
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
