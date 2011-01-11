#include <processimage/process.hpp>
#include "ast.h"
#include "parathon.h"
#include "ops.h"

val SuiteBody::evaluate() 
{
	/* HACK: if our caller is a generated entry point, catch returns. */
	std::cerr << "SuiteBody::evaluate() has caller address " << std::hex
		<< reinterpret_cast<process_image::addr_t>(__builtin_return_address(0)) << std::dec
		<< " of memory kind " << image.discover_object_memory_kind(
		reinterpret_cast<process_image::addr_t>(__builtin_return_address(0)))
		<< std::endl;
	if (image.discover_object_memory_kind(
		reinterpret_cast<process_image::addr_t>(__builtin_return_address(0))) 
		== process_image::ANON)
	{
		try
		{
			val ret;
			for (unsigned i=0; i < this->statements.size(); i++)
			{
				ret = this->statements[i]->evaluate();
			}
			return ret;
		}
		catch (ParathonReturn *p_r)
		{
			return p_r->value;
		}
	}
	else
	{
		val ret;
		for (unsigned i=0; i < this->statements.size(); i++)
		{
			ret = this->statements[i]->evaluate();
		}
		return ret;
	}
}
val Expression::evaluate()
{
    return None; // parathon_call("__or__", this->lhs->evaluate(), this->rhs->evaluate());
}
val FunctionCall::evaluate()
{
    return call_function(this->base_phrase->evaluate(), this->parameter_list->asArgs());
}
val IfStatement::evaluate()
{
    if (is_true(this->test->evaluate()))
    {
        return this->true_suite->evaluate();
    }
    else if(this->false_suite)
    {
        return this->false_suite->evaluate();
    }
    else
    {
        return None;
    }
}
val WhileStatement::evaluate()
{
    val r = None;
    while (is_true(this->test->evaluate()))
    {
        r = this->suite->evaluate();
    }
    return r;
}
std::vector<val>* ParameterList::asArgs()
{
    std::vector<val> *a = new std::vector<val>;
    for (unsigned i=0; i < this->params.size(); i++)
    {
        a->push_back(this->params[i]->evaluate());
    }
    return a;
}
bool ParameterList::assign(std::vector<val> *values)
{
    if (this->params.size() != values->size())
        return false;
    for (unsigned i=0; i < this->params.size(); i++)
    {
        if (!this->params[i]->assign((*values)[i]))
            return false;
    }
    return true;
}
val PrintStatement::evaluate()
{
    std::string separator = "";
    for (unsigned i = 0; i < this->testlist->size(); i++)
    {
        std::cout << separator;
        //this->testlist->item(i)->evaluate()->toStream(std::cout);
        print_value_to_stream(this->testlist->item(i)->evaluate(), std::cout);
        separator = " ";
    }
    if (!this->testlist->hasTrailingComma())
        std::cout << std::endl;

    return None;
}
