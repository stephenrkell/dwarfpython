#include "ast.h"
/**
 * This never gets included in the syntax tree.
 * inherits: ParameterListArgs
 */
ParameterListKwargs *ParameterListKwargs::parse()
{
    ParameterListKwargs *plk = new ParameterListKwargs();
    plk->kwargs = NULL;
    return plk;
}
ParameterListKwargs *ParameterListKwargs::parse(T_POWER _t, TestPhrase *tp)
{
    ParameterListKwargs *plk = new ParameterListKwargs();
    plk->kwargs = tp;
    return plk;
}
ParameterListKwargs *ParameterListKwargs::parse(T_POWER _t, TestPhrase *tp, T_COMMA)
{
    return ParameterListKwargs::parse(_t, tp);
}
