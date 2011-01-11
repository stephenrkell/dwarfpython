#include "ast.h"

/**
 * inherits: BasePhrase
 * private: BasePhrase *base_phrase;
 * private: ParameterList *parameter_list;
 * virtual: val evaluate();
 */
FunctionCall *FunctionCall::parse(BasePhrase *bp, T_OPEN_CURVED _t, ParameterList *pl, T_CLOSE_CURVED _tt)
{
    FunctionCall *asp = new FunctionCall();
    asp->base_phrase = bp;
    asp->parameter_list = pl;
    return asp;
}

void FunctionCall::toStream(std::ostream& strm)
{
    strm << this->base_phrase << "(" << this->parameter_list << ")";
}

