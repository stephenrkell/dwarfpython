#include "ast.h"
/**
 * A possibly empty,. comma-separated list of "test"s
 * (something like a lambda def, or a (spam "and" eggs)
 * May contain a trailing comma
 *
 * inherits: TestStatement
 * protected: std::vector<TestPhrase *> tests;
 * protected: bool trailing; // For the print statement
 */

TestList *TestList::parse( )
{
    TestList *tl = new TestList();
    tl->trailing = false;
    return tl;
}
TestList *TestList::parse(TestListNonEmpty *tl)
{
    return tl;
}

void TestList::toStream(std::ostream& strm)
{
    for (unsigned i=0; i < this->tests.size(); i++)
    {
        strm << this->tests[i] << ((this->trailing == false && this->tests.size() <= i + 1) ? "": ", ");
    }
}
bool TestList::hasTrailingComma()
{
    return this->trailing;
}
unsigned TestList::size()
{
    return this->tests.size();
}
TestPhrase *TestList::item(unsigned i)
{
    return this->tests[i];
}
val TestList::evaluate(ParathonContext& c)
{
    return this->tests[this->tests.size() - 1]->evaluate(c);
}
