#include "ast.h"

/**
 * protected: TestPhrase *kwargs;
 * protected: TestPhrase *args;
 * protected: std::vector<ParameterPhrase *> params;
 * virtual: std::vector<val>* asArgs();
 * virtual: bool assign(std::vector<val> *values);
 */
ParameterList *ParameterList::parse(ParameterListArgs *pla)
{
    return (new ParameterList())->updateWithArgs(pla);
}
ParameterList *ParameterList::parse(ParameterListNonArgs *pl)
{
    pl->args = NULL;
    pl->kwargs = NULL;
    return pl;
}
ParameterList *ParameterList::parse(ParameterListNonArgs *pl, T_COMMA _t, ParameterListArgs *pla)
{
    return pl->updateWithArgs(pla);
}
ParameterList *ParameterList::updateWithArgs(ParameterListArgs *pla)
{
    this->kwargs = pla->getKwargs();
    this->args = pla->getArgs();
    delete pla;
    return this;
}
void ParameterList::toStream(std::ostream& strm)
{
    std::string sep = "";
    for (unsigned i = 0; i < this->params.size(); i++)
    {
        strm << sep << this->params[i];
        sep = ", ";
    }

    if (this->args) 
    {
        strm << sep << "*" << this->args;
        sep = ", ";
    }

    if (this->kwargs)
        strm << sep << "**" << this->kwargs;
}
val ParameterList::evaluate()
{
    return None;
}
void ParameterList::evaluate_print(std::ostream& strm)
{
    return;
}
int ParameterList::size()
{
	return this->params.size();
}
ParameterPhrase* ParameterList::get(int i)
{
	return this->params[i];
}
