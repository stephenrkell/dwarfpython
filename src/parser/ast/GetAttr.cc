#include "ast.h"
/*#include "builtins.hh"*/
/**
 * inherits: BasePhrase
 * private: BasePhrase *base_phrase;
 * private: NamePhrase *name;
 */
GetAttr *GetAttr::parse(BasePhrase *bp, T_DOT _t, NamePhrase *name)
{
    GetAttr *ga = new GetAttr();
    ga->base_phrase = bp;
    ga->name = name;
    return ga;
}
void GetAttr::toStream(std::ostream& strm)
{
    strm << this->base_phrase << "." << this->name;
}
val GetAttr::evaluate()
{
    //return BUILTIN__getattr__(&c)(base_phrase->evaluate(), this->name->getName());
    std::cerr << "GetAttr not implemented!" << std::endl;
     return None;
}
ParathonAssigner* GetAttr::getAssigner()
{
    //return new ParathonContextAssigner(base_phrase->evaluate(), std::string(this->name->getName()));
	return 0;
}
