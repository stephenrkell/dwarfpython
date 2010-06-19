#include "ast.h"

/**
 * protected: TestPhrase *kwargs;
 * protected: TestPhrase *args;
 * protected: std::vector<ParameterPhrase *> params;
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
val ParameterList::evaluate(ParathonContext& c)
{
    return None;
}
void ParameterList::evaluate_print(ParathonContext& c,std::ostream& strm)
{
    return;
}
std::vector<val>* ParameterList::asArgs(ParathonContext& c)
{
    std::vector<val> *a = new std::vector<val>;
    for (unsigned i=0; i < this->params.size(); i++)
    {
        a->push_back(this->params[i]->evaluate(c));
    }
    return a;
}
bool ParameterList::assign(ParathonContext &c, std::vector<val> *values)
{
    if (this->params.size() != values->size())
        return false;
    for (unsigned i=0; i < this->params.size(); i++)
    {
        if (!this->params[i]->assign(c, (*values)[i]))
            return false;
    }
    return true;
}
