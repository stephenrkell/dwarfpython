#include "ast.h"

/**
 * inherits: SmallStatement
 * private: DottedName *name;
 * private: DottedAsNames *dnames;
 * private: ImportAsNames *inames;
 *
 */
ImportStatement *ImportStatement::parse(T_IMPORT _t, DottedAsNames *dan)
{
    return dan;
}
ImportStatement *ImportStatement::parse(T_FROM _t, DottedName *name, T_IMPORT _tt, ImportAsNames *ian)
{
    return ian->setFrom(name);
}
//Why is this syntax even allowed?
ImportStatement *ImportStatement::parse(T_FROM _t, DottedName *name, T_IMPORT _tt, T_OPEN_CURVED _ttt, ImportAsNames *ian, T_CLOSE_CURVED _tttt)
{
    return ImportStatement::parse(_t, name, _tt, ian);
}
ImportStatement *ImportStatement::parse(T_FROM _t, DottedName *name, T_IMPORT _tt, T_OPEN_CURVED _ttt, ImportAsNames *ian, T_COMMA _tttt, T_CLOSE_CURVED _ttttt)
{
    return ImportStatement::parse(_t, name, _tt, ian);
}
void ImportStatement::evaluate_print( std::ostream& strm)
{
    this->evaluate();
}
