#include "ParathonFunction.hh"

ParathonFunction::ParathonFunction(NamePhrase* name, ParameterList* params, Suite* s, ParathonContext& c)
{
    this->name = name;
    this->params = params;
    this->suite = s;
    this->context = &c;
}

void ParathonFunction::toStream(std::ostream &strm)
{
    strm << "def " << this->name << "(" << this->params << ")";
}
ParathonValue *ParathonFunction::call(std::vector<ParathonValue*>* v)
{
    ParathonContext c(this->context);

    if (!this->params->assign(c, v))
    {
        std::cout << "Wrong number of arguments" << std::endl;
        return NULL;
    }
    try {
        this->suite->evaluate(c);
        return NULL;
    } catch(ParathonReturn* r) {
        return r->value;
    }
}
