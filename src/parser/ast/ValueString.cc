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
val ValueString::evaluate()
{
    return (val) { false, { i_ptr: s }, val::CHAR_PTR };
}
