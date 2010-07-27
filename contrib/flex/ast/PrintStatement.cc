#include "ast.h"

/**
 * print >>sys.stdout, blo, bla, blue,
 *
 * inherits: SmallStatement
 * private: TestPhrase *file;
 * private: TestList *testlist;
 */
PrintStatement *PrintStatement::parse(T_PRINT _t, TestList* tl)
{
    return (new PrintStatement())->addTestList(tl);
}
PrintStatement *PrintStatement::parse(T_PRINT _t, T_RIGHTSHIFT _tt, TestPhrase *file)
{
    PrintStatement *p = new PrintStatement();
    p->file = file;
    return p;
}
PrintStatement *PrintStatement::parse(T_PRINT _t, T_RIGHTSHIFT _tt, TestPhrase *file, T_COMMA _ttt, TestListNonEmpty* tl)
{
    return PrintStatement::parse(_t, _tt, file)->addTestList(tl);
}

PrintStatement::PrintStatement()
{
    this->testlist = NULL;
    this->file = NULL;
}

PrintStatement *PrintStatement::addTestList(TestList* tl)
{
    this->testlist = tl;
    return this;
}
void PrintStatement::toStream(std::ostream& s)
{
    s << "print";
    if (this->file)
        s << " >>" << this->file << (this->testlist ? "," : "");

    if (this->testlist)
        s << " " << this->testlist;
}
ParathonValue *PrintStatement::evaluate(ParathonContext& c)
{
    std::string separator = "";
    for (unsigned i = 0; i < this->testlist->size(); i++)
    {
        std::cout << separator;
        this->testlist->item(i)->evaluate(c)->toStream(std::cout);
        separator = " ";
    }
    if (!this->testlist->hasTrailingComma())
        std::cout << std::endl;

    return NULL;
}
