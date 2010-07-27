#include "ast.h"
/**
 * inherits: TestList
 */
TestListNonEmpty *TestListNonEmpty::parse(TestListNonTrailing *tl)
{
    tl->trailing = false;
    return tl;
}
TestListNonEmpty *TestListNonEmpty::parse(TestListNonTrailing *tl, T_COMMA _t)
{
    tl->trailing = true;
    return tl;
}
