#include "ast.h"
/**
 * inherits: SingleInput
 */
Suite *Suite::parse(SimpleStatement *ss, T_NEWLINE _t)
{
    return ss;
}
Suite *Suite::parse(T_NEWLINE _t, T_INDENT _tt, SuiteBody *sb, T_OUTDENT _ttt)
{
    return sb;
}
