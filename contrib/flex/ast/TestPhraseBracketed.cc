#include "ast.h"
/**
 * This is perhaps the ickiest artifact of the generated parser stuff -
 *  in a sane world we could just return the TestPhrase, but that wouldn't be type-checkable
 *
 * inherits: BasePhrase
 * private: TestPhrase * tp;
 */
TestPhraseBracketed *TestPhraseBracketed::parse(T_OPEN_CURVED _t, TestPhrase *tp, T_CLOSE_CURVED _tt)
{
    TestPhraseBracketed * tpb = new TestPhraseBracketed();
    tpb->tp = tp;
    return tpb;
}

void TestPhraseBracketed::toStream(std::ostream& strm)
{
    strm << tp ;
}
ParathonValue *TestPhraseBracketed::evaluate(ParathonContext& c)
{
    return this->tp->evaluate(c);
}
