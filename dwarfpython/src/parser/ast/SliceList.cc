#include "ast.h"

/**
 * private: std::vector<SlicePhrase *> slices;
 */
SliceList *SliceList::parse(SlicePhrase *sp)
{
    return (new SliceList())->append(sp);
}
SliceList *SliceList::parse(SliceList *sl, T_COMMA _t, SlicePhrase *sp)
{
    return sl->append(sp);
}

SliceList *SliceList::append(SlicePhrase *sp)
{
    this->slices.push_back(sp);
    return this;
}

void SliceList::toStream(std::ostream &strm)
{
    std::string sep = "";
    for (unsigned i = 0; i < this->slices.size(); i++)
    {
        strm << sep << this->slices[i];
        sep = ",";
    }

}
val SliceList::evaluate(ParathonContext& c)
{
    return None;
}
void SliceList::evaluate_print(ParathonContext& c,std::ostream& strm)
{
    return;
}
