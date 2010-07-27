#include "ast.h"
#include "parathon.h"
#include "parathon.yy.hh"
#include "lexer.h"
#include "parathon.l.h"
#include "builtins.hh"
#include <string.h>
#include "signal.h"
#include "setjmp.h"

jmp_buf JumpBuffer;
void interrupt_handler(int signal)
{
    switch(signal)
    {
        case SIGSEGV:
            std::cout << "Caught segmentation fault. Be careful!" << std::endl;
            break;
        case SIGFPE:
            std::cout << "Floating point exception. Division by zero?" << std::endl;
            break;
        case SIGILL:
            std::cout << "Illegal instruction executed. Be careful!" << std::endl;
            break;
    }
    longjmp(JumpBuffer,1);
}

int parse_loop(yy_extra_type extra, ParathonContext* c)
{
    int status;
    yypstate *ps = yypstate_new ();
    yyscan_t scanner;
    YYSTYPE lval;
    yylex_init_extra( &extra, &scanner );

    do {
        setjmp(JumpBuffer); 

        status = yypush_parse(ps, yylex(&lval, scanner), &lval, c);
    } while (status == YYPUSH_MORE);

    yypstate_delete(ps);
    yylex_destroy(scanner);
    return 0;
}

int main(int argc, char ** argv)
{
    if(setjmp(JumpBuffer))
    {
        std::cout << "Caught signal during initialisation. Will now die." << std::endl;
        exit(0);
    }
    //signal(SIGSEGV, interrupt_handler);
    //signal(SIGFPE, interrupt_handler);
    //signal(SIGILL, interrupt_handler);

    initialize_builtins(&ParathonValue::builtins);
    std::cout << "This is DwarfPython\nCtrl-D exits." << std::endl;
    ParathonContext globals(ParathonValue::builtins);
    globals.interpreterMode = true;
    globals.assign("__name__", new ParathonValue("__main__"));

    int result;
    yy_extra_type a;
    YY_EXTRA_FOR_FILE(a, stdin);
    result = parse_loop(a, &globals);

    std::cout << std::endl;
    return result;
}

void evaluate(SingleInput *si, ParathonContext* c)
{
//    std::cout << si;
//    std::cerr << "Trying to evaluate";
    try
    {
        if (c->interpreterMode)
            si->evaluate_print(*c, std::cout);
        else
            si->evaluate(*c);
    }
    catch(ParathonException e)
    {
        std::cerr << e.message << std::endl;
    }
}

ParathonValue *parathon_call(const char * name, ParathonValue *lhs)
{
//    std::cerr << "Trying to ucall '" << name << "' on " << lhs << std::endl;
    return lhs->call(name);
}
ParathonValue *parathon_call(const char * name, ParathonValue *lhs, ParathonValue *rhs)
{
    if (!lhs)
    {
        std::cerr << "Tried to call '" << name << "' on None" << std::endl;
        return NULL;
    }
    else
    {
//        std::cerr << "Trying to call '" << name << "' on " << lhs << std::endl;
        return lhs->call(name, rhs);
    }
}

const char *Operator::opname()
{
    return "__YUCK__";
}

void initialise()
{

}
