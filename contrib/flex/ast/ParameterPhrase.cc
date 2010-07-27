#include "ast.h"
/**
 * private: TestPhrase *value;
 * private: NamePhrase *name;
 */
ParameterPhrase *ParameterPhrase::parse(TestPhrase *tp)
{
    ParameterPhrase *pp = new ParameterPhrase();
    pp->name = NULL;
    pp->value = tp;
    return pp;
}
ParameterPhrase *ParameterPhrase::parse(NamePhrase *np, T_ASSIGN _t, TestPhrase *tp)
{
    ParameterPhrase *pp = new ParameterPhrase();
    pp->name = np;
    pp->value = tp;
    return pp;
}
void ParameterPhrase::toStream(std::ostream& strm)
{
    if (this->name)
        strm << this->name << "=";
    strm << this->value;
}
ParathonValue *ParameterPhrase::evaluate(ParathonContext& c)
{
    return this->value->evaluate(c);
}
void ParameterPhrase::evaluate_print(ParathonContext& c,std::ostream& strm)
{
    this->value->evaluate_print(c, strm);
}
bool ParameterPhrase::assign(ParathonContext& c, ParathonValue *v)
{
    ParathonAssigner *a = (this->name == NULL ? this->value : this->name)->getAssigner(c);

    if (a == NULL)
        return false;

    if (v)
        a->assign(v);
    else
        a->assign(this->value->evaluate(*(ParathonContext*)c.parent));

    return true;

}
