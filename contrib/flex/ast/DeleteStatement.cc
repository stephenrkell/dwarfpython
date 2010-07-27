#include "ast.h"
/**
 * inherits: SmallStatement
 * private: TestList *test_list;
 */
DeleteStatement *DeleteStatement::parse(T_DEL _t, TestList *t)
{
    DeleteStatement *ds = new DeleteStatement();
    ds->test_list = t;
    return ds;
}

void DeleteStatement::toStream(std::ostream& strm)
{
    strm << "del " << this->test_list;
}
