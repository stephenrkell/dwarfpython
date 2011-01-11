#include "ast.h"
#include "parathon.h"
#include "ops.h"

val AssignStatement::evaluate()
{
    val x = rhs->evaluate();
    //ParathonAssigner *a = this->lhs->getAssigner();
    //if (a)
    //{
    //    a->assign(x);
    //}
    assign_to(this->lhs->evaluate(), x);
    //else
    //{
    //    std::cerr << "Tried to assign to something strange" << std::endl;
    //}
    return None;
}
bool ParameterPhrase::assign(val v)
{
//     ParathonAssigner *a = (this->name == NULL ? this->value : this->name)->getAssigner();
// 
//     if (a == NULL)
//         return false;
// 
//     if (is_true(v))
//         a->assign(v);
//     else { std::cerr << "Parameter assignment case not supported!" << std::endl; return false; }
//         //a->assign(this->value->evaluate(*(ParathonContext*)c.parent));

    return true;

}
ParathonAssigner *TestStatement::getAssigner()
{
    return NULL;
}
