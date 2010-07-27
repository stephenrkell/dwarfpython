#include "ast.h"
/**
 * inherits: BasePhrase
 * private: double f;
 */

ValueFloat *ValueFloat::parse(T_FLOAT f)
{
    ValueFloat *vf = new ValueFloat();
    vf->f = f;
    return vf;
}
void ValueFloat::toStream(std::ostream& strm)
{
    strm << this->f;
}
ParathonValue *ValueFloat::evaluate(ParathonContext& c)
{
    return new ParathonValue(this->f);
}
