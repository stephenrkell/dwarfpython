#include "ast.h"
/**
 * inherits: SmallStatement
 * private: TestStatement *lhs;
 * private: TestStatement *rhs;
 * private: Operator *op;
 */
AssignStatement *AssignStatement::parse(TestStatement *lhs, T_ASSIGN _t, TestStatement *rhs)
{
    return new AssignStatement(lhs, rhs, NULL);
}
AssignStatement::AssignStatement(TestStatement *lhs, TestStatement *rhs, Operator *op)
{
    this->lhs = lhs;
    this->rhs = rhs;
    this->op = op;
}
void AssignStatement::toStream(std::ostream& strm)
{
    strm << this->lhs << " ";
    if (this->op != NULL)
        strm << this->op;
    strm << "= " << this->rhs;
}
val AssignStatement::evaluate(ParathonContext& c)
{
    val x = rhs->evaluate(c);
    ParathonAssigner *a = this->lhs->getAssigner(c);
    if (a)
    {
        a->assign(x);
    }
    else
    {
        std::cerr << "Tried to assign to something strange" << std::endl;
    }
    return None;
}
