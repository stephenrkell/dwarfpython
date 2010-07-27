#include "ast.h"
/**
 * inherits: TestPhrase
 * protected: TestPhrase *when_true;
 * protected: TestPhrase *when_false;
 * protected: TestPhrase *condition;
 */
InlineIfPhrase *InlineIfPhrase::parse(T_IF _t, OrPhrase *op, T_ELSE _tt, TestPhrase *tp)
{
    InlineIfPhrase *iip = new InlineIfPhrase();
    iip->when_false = tp;
    iip->condition = op;
    //when_true gets set by TestPhrase
    return iip;
}
void InlineIfPhrase::toStream(std::ostream& strm)
{
    strm << "(" << this->when_true << " if " << this->condition << " else " << this->when_false << ")"; 
}
InlineIfPhrase *InlineIfPhrase::setTrue(TestPhrase *tp)
{
    this->when_true = tp;
    return this;
}
