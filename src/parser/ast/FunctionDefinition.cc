#include "ast.h"
/*#include "ParathonFunction.hh"*/
/**
 * inherits: SingleInput
 * private: NamePhrase *name;
 * private: ParameterList *parameter_list;
 * private: Suite *suite;
 * virtual: val evaluate();
 */
FunctionDefinition *FunctionDefinition::parse(T_DEF _t, NamePhrase *np, T_OPEN_CURVED _tt, ParameterList *pl, T_CLOSE_CURVED _ttt, T_COLON _tttt, Suite *s)
{
    FunctionDefinition *fd = new FunctionDefinition();
    fd->name = np;
    fd->parameter_list = pl;
    fd->suite = s;
    return fd;
}
void FunctionDefinition::toStream(std::ostream& strm)
{
    strm << "def " << this->name << "(" << this->parameter_list << ")" << ":" << this->suite; 
}
