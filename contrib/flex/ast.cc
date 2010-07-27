#include "ast.h"

using std::string;
using std::ostream;

/** Statement **/
ostream &operator<<(ostream &strm, Statement &stmt)
{
    stmt.toStream(strm);
    return strm;
}
ostream &operator<<(ostream &strm, Statement *stmt)
{
    stmt->toStream(strm);
    return strm;
}
