#include "ast.h"
/** 
 * inherits: BasePhrase
 * private: T_NAME name;
 * virtual: val evaluate();
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
ParathonAssigner *NamePhrase::getAssigner()
{
    //return new ParathonContextAssigner(c, this->name);
    return 0;
}
char * NamePhrase::getName()
{
    return this->name;
}
