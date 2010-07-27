#include "ast.h"
/*#include "builtins.hh"*/
/**
 * inherits: ImportStatement
 * private: std::map<T_NAME, DottedName *> imports;
 */
DottedAsNames *DottedAsNames::parse(DottedName *dn)
{
    return (new DottedAsNames())->append(dn->lastName(), dn);
}
DottedAsNames *DottedAsNames::parse(DottedName *dn, T_AS _t, T_NAME name)
{
    return (new DottedAsNames())->append(name, dn);
}
DottedAsNames *DottedAsNames::parse(DottedAsNames *dan, T_COMMA _t, DottedName *dn)
{
    return dan->append(dn->lastName(), dn);
}
DottedAsNames *DottedAsNames::parse(DottedAsNames *dan, T_COMMA _t, DottedName *dn, T_AS _tt, T_NAME name)
{
    return dan->append(name, dn);
}

DottedAsNames *DottedAsNames::append(T_NAME name, DottedName *dn)
{
    this->imports[name] = dn;
    return this;
}

void DottedAsNames::toStream(std::ostream& strm)
{
    std::map<T_NAME, DottedName *>::iterator iter;
    std::string sep = "import ";
    for (iter = this->imports.begin(); iter != this->imports.end(); ++iter)
    {
        strm << sep << iter->second;
        if (iter->second->lastName() != iter->first)
            strm << " as " << iter->first;
        sep = ", ";
    }
}
val DottedAsNames::evaluate(ParathonContext& c)
{
/*    std::map<T_NAME, DottedName *>::iterator iter;
    for (iter = this->imports.begin(); iter != this->imports.end(); ++iter)
    {
        c.assign(iter->first, BUILTIN__import__(&c)(iter->first, &c));
    }*/
    std::cerr << "DottedAsNames not supported!" << std::endl;
    return None;
}
