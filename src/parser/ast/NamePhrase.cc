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
ParathonAssigner *NamePhrase::getAssigner(ParathonContext *c)
{
    //return new ParathonContextAssigner(c, this->name);
    return 0;
}
val NamePhrase::evaluate(ParathonContext &c)
{
	val found;
    if ((found = lookup_name(c, this->name)) != None)
        return found;
    else
    {
        throw ParathonException("NameError: name '" + string(this->name) + "' is not defined", linenum);
    }
}

char * NamePhrase::getName()
{
    return this->name;
}
