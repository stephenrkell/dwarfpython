#include "ast.h"
/**
 * inherits: SmallStatement
 * private: std::vector<NamePhrase *> names;
 */
GlobalStatement *GlobalStatement::parse(T_GLOBAL _t, NamePhrase *np)
{
    return (new GlobalStatement())->append(np);
}
GlobalStatement *GlobalStatement::parse(GlobalStatement *gp, T_COMMA _t, NamePhrase *np)
{
    return gp->append(np);
}
GlobalStatement *GlobalStatement::append(NamePhrase *np)
{
    this->names.push_back(np);
    return this;
}
void GlobalStatement::toStream(std::ostream& strm)
{
    std::string sep = "";

    strm << "global ";

    for(unsigned i = 0; i < this->names.size(); i++)
    {
        strm << sep << this->names[i];
        sep = ", ";
    }
}
