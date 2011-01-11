#include "ast.h"

/**
 * This thing is only temporary - it is not actually incorporated into the syntax tree.
 * (should reflect that in some way - we certainly don't need to implement toStream)
 *
 * private: TestPhrase *tp;
 */
TestPhraseOptional *TestPhraseOptional::parse()
{
    return new TestPhraseOptional(NULL);
}
TestPhraseOptional *TestPhraseOptional::parse(TestPhrase *tp)
{
    return new TestPhraseOptional(tp);
}

TestPhraseOptional::TestPhraseOptional(TestPhrase *tp)
{
    this->tp = tp;
}
TestPhrase *TestPhraseOptional::testPhrase()
{
    return this->tp;
}

void TestPhraseOptional::toStream(std::ostream& strm)
{
    throw "TestPhraseOptional should never be printed.";
    strm << this->tp;
}
val TestPhraseOptional::evaluate()
{
    return None;
}
void TestPhraseOptional::evaluate_print(std::ostream& strm)
{
    return;
}
