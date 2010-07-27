#include "parathon.h"
#include <sstream>
ParathonException::ParathonException(string message)
{
    this->message = message;
}
ParathonException::ParathonException(string m1, string m2, string m3)
{
    std::stringstream s;
    s << m1 << m2 << m3;
    this->message = s.str();
}
ParathonException::ParathonException(string message, int linenum)
{
    std::stringstream s;
    s << "  Line " << linenum << ":" << std::endl;
    s << message;
    this->message = s.str();
}

ParathonReturn::ParathonReturn(ParathonValue* value)
{
    this->value = value;
}
