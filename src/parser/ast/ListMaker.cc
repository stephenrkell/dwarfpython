#include "ast.h"
/**
 * inherits: BasePhrase
 * private: TestList *test_list;
 */
ListMaker *ListMaker::parse(T_OPEN_SQUARE _t, TestList *tl, T_CLOSE_SQUARE)
{
    ListMaker *lm = new ListMaker();
    lm->test_list = tl;
    return lm;
}
void ListMaker::toStream(std::ostream& strm)
{
    strm << "[" << this->test_list << "]";
}
