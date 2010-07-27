#include "parathon.h"

ParathonContext::ParathonContext(ParathonValue *parent)
{
    this->interpreterMode = false;
    this->parent = parent;
}

ParathonContextAssigner::ParathonContextAssigner(ParathonValue& c, string name)
{
    this->context = &c;
    this->name = name;
}

void ParathonContextAssigner::assign(ParathonValue *value)
{
    if (!( this->context->die && this->context->die->assignField((void**)this->context->value, this->name.c_str(), value)))
    {
        this->context->assign(this->name, value);
    }
}

