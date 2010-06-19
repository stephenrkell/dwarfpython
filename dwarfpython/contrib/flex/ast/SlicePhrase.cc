#include "ast.h"
/**
 * The step inside [ ]s
 * private: TestPhrase *from;
 * private: TestPhrase *to;
 * private: TestPhrase *step;
 * private: bool ellipsis;
 */
SlicePhrase *SlicePhrase::parse(TestPhrase *from)
{
    SlicePhrase *sl = new SlicePhrase(false);
    sl->from = from;
    return sl;
}
SlicePhrase *SlicePhrase::parse(T_DOT _t, T_DOT _tt, T_DOT _ttt)
{
    return new SlicePhrase(true);
}
SlicePhrase *SlicePhrase::parse(TestPhraseOptional *from, T_COLON _t, TestPhraseOptional *to)
{
    return SlicePhrase::parse(from, _t, to, _t, new TestPhraseOptional(NULL));
}
SlicePhrase *SlicePhrase::parse(TestPhraseOptional *from, T_COLON _t, TestPhraseOptional *to, T_COLON _tt, TestPhraseOptional *step)
{
    SlicePhrase *sl = new SlicePhrase(false);
    sl->from = from->testPhrase();
    sl->to = to->testPhrase();
    sl->step = step->testPhrase();
    delete from;
    delete to;
    delete step;
    return sl;
}

SlicePhrase::SlicePhrase(bool ellipsis)
{
    this->ellipsis = ellipsis;
    this->from = this->to = this->step = NULL;
}

void SlicePhrase::toStream(std::ostream& strm)
{
    if (this->ellipsis)
    {
        strm << "...";
    }
    else
    {
        if(this->from)
            strm << this->from;

        if(this->to || this->step)
        {
            strm << ":";
            if (this->to)
                strm << this->to;

            if (this->step)
                strm << ":" << this->step;
        }
    }
}
ParathonValue *SlicePhrase::evaluate(ParathonContext& c)
{
    return NULL;
}
void SlicePhrase::evaluate_print(ParathonContext& c,std::ostream& strm)
{
    return;
}
