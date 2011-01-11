#include "ast.h"
#include "parathon.h"
#include "ops.h"

val NamePhrase::evaluate()
{
	val found;
    if ((found = lookup_name(this->name)) != None)
        return found;
    else
    {
        throw ParathonException("NameError: name '" + string(this->name) + "' is not defined", linenum);
    }
}
