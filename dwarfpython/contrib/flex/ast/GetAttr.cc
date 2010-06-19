#include "ast.h"
#include "builtins.hh"
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
ParathonValue *GetAttr::evaluate(ParathonContext& c)
{
    return BUILTIN__getattr__(&c)(base_phrase->evaluate(c), this->name->getName());
}
ParathonAssigner* GetAttr::getAssigner(ParathonContext& c)
{
    return new ParathonContextAssigner(*base_phrase->evaluate(c), std::string(this->name->getName()));

}
