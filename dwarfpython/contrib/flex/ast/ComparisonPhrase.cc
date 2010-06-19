#include "ast.h"
/**
 * inherits: NotPhrase
 */
ComparisonPhrase *ComparisonPhrase::parse(Expression *ex)
{
    return ex; 
}
ComparisonPhrase *ComparisonPhrase::parse(ComparisonList *cl)
{
    return cl;
}
