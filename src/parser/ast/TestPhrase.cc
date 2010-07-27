#include "ast.h"

/**
 * inherits: TestStatement
 * A "test" as per python's grammar file.
 * TODO fill me up!
 */
TestPhrase *TestPhrase::parse(OrPhrase *op)
{
    return op;
}
TestPhrase *TestPhrase::parse(OrPhrase *op, InlineIfPhrase *iip)
{
    return iip->setTrue(op);
}
