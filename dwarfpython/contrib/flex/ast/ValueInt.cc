#include "ast.h"
/**
 * inherits: BasePhrase
 * private: parathon_int i;
 */

ValueInt *ValueInt::parse(T_INTEGER i)
{
    ValueInt *vi = new ValueInt();
    vi->i = i;
    return vi;
}
void ValueInt::toStream(std::ostream& strm)
{
    strm << i;
}
ParathonValue *ValueInt::evaluate(ParathonContext& c)
{
    return new ParathonValue(i);
}
