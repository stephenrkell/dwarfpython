#include "ast.h"
/**
 * private: TestPhrase *value;
 * private: NamePhrase *name;
 * virtual: bool assign(val v);
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
val ParameterPhrase::evaluate()
{
    return this->value->evaluate();
}
void ParameterPhrase::evaluate_print(std::ostream& strm)
{
    this->value->evaluate_print(strm);
}
NamePhrase *ParameterPhrase::getName()
{
	return name;
}
TestPhrase *ParameterPhrase::getValue()
{
	return value;
}
