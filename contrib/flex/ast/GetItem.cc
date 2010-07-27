#include "ast.h"

/**
 * inherits: BasePhrase
 * private: BasePhrase *base_phrase;
 * private: SliceList *slice_list;
 */
GetItem *GetItem::parse(BasePhrase *bp, T_OPEN_SQUARE _t, SliceList *sl, T_CLOSE_SQUARE _tt)
{
    GetItem *asp = new GetItem();
    asp->base_phrase = bp;
    asp->slice_list = sl;
    return asp;
}
GetItem *GetItem::parse(BasePhrase *ap, T_OPEN_SQUARE _t, SliceList *sl, T_COMMA _tt, T_CLOSE_SQUARE _ttt)
{
    //FIXME - this should ensure that it is returning a tuple
    return GetItem::parse(ap, _t, sl, _ttt);
}

void GetItem::toStream(std::ostream& strm)
{
    strm << this->base_phrase << "[" << this->slice_list << "]";
}
