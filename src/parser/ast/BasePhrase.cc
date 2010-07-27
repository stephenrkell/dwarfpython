#include "ast.h"
/** 
 * inherits: UnaryPhrase
 * Anything that can be .attr'd or [gotitem]'d 
 */
BasePhrase *BasePhrase::parse(NamePhrase *np)
{
    return np;
}
BasePhrase *BasePhrase::parse(GetItem *gi)
{
    return gi;
}
BasePhrase *BasePhrase::parse(GetAttr *ga)
{
    return ga;
}
BasePhrase *BasePhrase::parse(FunctionCall *fc)
{
    return fc;
}
BasePhrase *BasePhrase::parse(ListMaker *lm)
{
    return lm;
}
BasePhrase *BasePhrase::parse(TupleMaker *tm)
{
    return tm;
}
BasePhrase *BasePhrase::parse(ReprPhrase *rp)
{
    return rp;
}
BasePhrase *BasePhrase::parse(TestPhraseBracketed *tpb)
{
    return tpb;
}
BasePhrase *BasePhrase::parse(ValueInt *vi)
{
    return vi;
}
BasePhrase *BasePhrase::parse(ValueFloat *vf)
{
    return vf;
}
BasePhrase *BasePhrase::parse(ValueString *vs)
{
    return vs;
}
