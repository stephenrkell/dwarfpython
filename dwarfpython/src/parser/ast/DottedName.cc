#include "ast.h"
/**
 * private: std::vector<T_NAME> names;
 */
DottedName *DottedName::parse(T_NAME name)
{
    return (new DottedName())->append(name);
}

DottedName *DottedName::parse(DottedName *dn, T_DOT _t, T_NAME name)
{
    return dn->append(name);
}

DottedName *DottedName::append(T_NAME name)
{
    this->names.push_back(name);
    return this;
}

T_NAME DottedName::lastName()
{
    return this->names.back();
}
void DottedName::toStream(std::ostream& strm)
{
    for (unsigned i=0; i < this->names.size(); i++)
    {
        strm << this->names[i] << (i + 1 == this->names.size() ? "": ".");
    }
}
val DottedName::evaluate(ParathonContext&c)
{
    return None;
}
void DottedName::evaluate_print(ParathonContext&c, std::ostream& strm)
{
}
