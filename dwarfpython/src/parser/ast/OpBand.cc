#include "ast.h"
/**
 * inherits: UnaryOperator
 */
OpBand *OpBand::parse(T_BAND _t)
{
    return new OpBand();
}
void OpBand::toStream(std::ostream& strm)
{
    strm << "&";
}
