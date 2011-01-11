#include "ast.h"
/**
 * inherits: BasePhrase
 * private: int i;
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
val ValueInt::evaluate()
{
    return (val) { true, { i_int: i }, val::INT };
}
