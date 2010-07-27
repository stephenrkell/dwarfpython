#include "ast.h"
/**
 * inherits: BasePhrase
 * private: TestList *test_list;
 */
TupleMaker *TupleMaker::parse(T_OPEN_CURVED _t, TestListNonTrailing *tl, T_COMMA _tt, TestPhrase *tp, T_CLOSE_CURVED _ttt)
{
    TupleMaker *tm = new TupleMaker();
    tm->test_list = tl->append(tp);
    return tm;
}
TupleMaker *TupleMaker::parse(T_OPEN_CURVED _t, TestListNonTrailing *tl, T_COMMA _tt, T_CLOSE_CURVED _ttt)
{
    TupleMaker *tm = new TupleMaker();
    tm->test_list = tl;
    return tm;
}
void TupleMaker::toStream(std::ostream& strm)
{
    strm << "(" << this->test_list << (this->test_list->size() < 2 ? ",)" : ")");
}
