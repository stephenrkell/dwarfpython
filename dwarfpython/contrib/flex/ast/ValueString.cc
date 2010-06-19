#include "ast.h"
/**
 * inherits: BasePhrase
 * private: char *s;
 */
ValueString *ValueString::parse(T_STRING str)
{
    ValueString *vs = new ValueString();
    vs->s = str;
    return vs;
}
void ValueString::toStream(std::ostream& strm)
{
    //FIXME
    strm << "\"" << this->s << "\"";
}
ParathonValue* ValueString::evaluate(ParathonContext& c)
{
    return new ParathonValue((char*) this->s);
}
