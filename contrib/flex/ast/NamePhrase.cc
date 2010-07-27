#include "ast.h"
/** 
 * inherits: BasePhrase
 * A wrapper around a T_NAME;
 * private: T_NAME name;
 */
NamePhrase *NamePhrase::parse(T_NAME name)
{
    NamePhrase * np = new NamePhrase();
    np->name = name;
    return np;
}

void NamePhrase::toStream(std::ostream& strm)
{
    strm << this->name;
}
ParathonAssigner *NamePhrase::getAssigner(ParathonContext& c)
{
    return new ParathonContextAssigner(c, this->name);
}
ParathonValue *NamePhrase::evaluate(ParathonContext &c)
{
    if (c.lookup(this->name))
        return c.lookup(this->name);
    else
    {
        throw ParathonException("NameError: name '" + string(this->name) + "' is not defined", linenum);
    }
}

char * NamePhrase::getName()
{
    return this->name;
}
