#include "ast.h"
/**
 * inherits: ImportStatement
 * private: std::map<T_NAME, T_NAME> imports;
 * private: DottedName *from;
 */
ImportAsNames *ImportAsNames::parse(T_NAME name)
{
    return (new ImportAsNames())->append(name, name);
}
ImportAsNames *ImportAsNames::parse(T_NAME item, T_AS _t, T_NAME name)
{
    return (new ImportAsNames())->append(name, item);
}
ImportAsNames *ImportAsNames::parse(ImportAsNames *dan, T_COMMA _t, T_NAME name)
{
    return dan->append(name, name);
}
ImportAsNames *ImportAsNames::parse(ImportAsNames *dan, T_COMMA _t, T_NAME item, T_AS _tt, T_NAME name)
{
    return dan->append(name, item);
}

ImportAsNames *ImportAsNames::append(T_NAME name, T_NAME item)
{
    this->imports[name] = item;
    return this;
}

// set by ImportStatement.cc on every possible parse
ImportAsNames *ImportAsNames::setFrom(DottedName *from)
{
    this->from = from;
    return this;
}

void ImportAsNames::toStream(std::ostream& strm)
{
    std::map<T_NAME, T_NAME>::iterator iter;
    std::string sep = "import ";
    for (iter = this->imports.begin(); iter != this->imports.end(); ++iter)
    {
        strm << sep << iter->second;
        if (iter->second != iter->first)
            strm << " as " << iter->first;

        sep = ", ";
    }
}
