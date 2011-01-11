#include "ast.h"
/**
 * This never gets included in the syntax tree.
 * protected: TestPhrase *args;
 * protected: TestPhrase *kwargs;
 */
ParameterListArgs *ParameterListArgs::parse(ParameterListKwargs *plk)
{
    plk->args = NULL;
    return plk;
}
ParameterListArgs *ParameterListArgs::parse(T_MULTIPLY _t, TestPhrase *tp)
{
    ParameterListArgs *pla = new ParameterListArgs();
    pla->args = tp;
    pla->kwargs = NULL;
    return pla;
}
ParameterListArgs *ParameterListArgs::parse(T_MULTIPLY _t, TestPhrase *tp, T_COMMA, ParameterListKwargs *kw)
{
    kw->args = tp;
    return kw;
}
void ParameterListArgs::toStream(std::ostream& strm)
{
    strm << "FAIL!";
}
val ParameterListArgs::evaluate()
{
    return None;
}
void ParameterListArgs::evaluate_print(std::ostream& strm)
{
    return;
}
TestPhrase *ParameterListArgs::getArgs()
{
    return this->args;
}
TestPhrase *ParameterListArgs::getKwargs()
{
    return this->kwargs;
}
