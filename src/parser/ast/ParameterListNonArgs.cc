#include "ast.h"
/**
 * inherits: ParameterList
 */
ParameterListNonArgs *ParameterListNonArgs::parse(ParameterPhrase *pp)
{
    return (new ParameterListNonArgs())->append(pp);
}
ParameterListNonArgs *ParameterListNonArgs::parse(ParameterListNonArgs *pl, T_COMMA _t, ParameterPhrase *pp)
{
    return (pl)->append(pp);
}
ParameterListNonArgs *ParameterListNonArgs::append(ParameterPhrase *pp)
{
    this->params.push_back(pp);
    return this;
}
