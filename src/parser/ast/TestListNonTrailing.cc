#include "ast.h"
/**
 * inherits: TestListNonEmpty
 */
TestListNonTrailing *TestListNonTrailing::parse(TestPhrase *tp)
{
    return (new TestListNonTrailing())->append(tp);
}
TestListNonTrailing *TestListNonTrailing::parse(TestListNonTrailing *tl, T_COMMA _t, TestPhrase *tp)
{
    return tl->append(tp);
}

TestListNonTrailing *TestListNonTrailing::append(TestPhrase *tp)
{
    this->tests.push_back(tp);
    return this;
}
