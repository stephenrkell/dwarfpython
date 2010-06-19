#include "ast.h"
/**
 * inherits: BasePhrase
 * private: TestList *test_list;
 */
ReprPhrase *ReprPhrase::parse(T_BACKTICK _t, TestListNonTrailing *tl, T_BACKTICK _tt)
{
    ReprPhrase *rp = new ReprPhrase();
    rp->test_list = tl;
    return rp;
}
void ReprPhrase::toStream(std::ostream& strm)
{
    strm << "`" << this->test_list << "`";
}
