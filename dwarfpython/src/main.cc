#include "ast.h"
#include "parathon.h"
#include "parathon.yy.hh"
#include "lexer.h"
#include "parathon.l.h"
//#include "builtins.hh"
#include <string.h>
#include "signal.h"
#include "setjmp.h"
#include <dwarfpp/encap_adt.hpp>

dwarf::encap::dieset builtins(dwarf::spec::DEFAULT_DWARF_SPEC);
val valNone = { false, { i_ptr: 0 }, boost::shared_ptr<dwarf::spec::type_die>() };
const val& None = valNone;
val valNotImplemented = { false, { i_ptr: (void*)1 }, boost::shared_ptr<dwarf::spec::type_die>() };
const val& NotImplemented = valNotImplemented;
val valInvalid = { false, { i_ptr: 0 }, boost::shared_ptr<dwarf::spec::type_die>() };
const val& Invalid = valInvalid;
const char *executable_path;
dwarf::encap::base_type_die *p_builtin_int_type = 0; // overwritten in init
dwarf::encap::base_type_die *p_builtin_double_type = 0; // overwritten in init
dwarf::encap::base_type_die *p_builtin_char_type = 0;
dwarf::encap::const_type_die *p_builtin_const_char_type = 0;
dwarf::encap::pointer_type_die *p_builtin_const_char_pointer_type = 0;
std::string s_builtins("builtins");
std::string s_int("int");
std::string s_double("double");
std::string s_char("char");
void init() __attribute__((constructor));
void init()
{
	/* We don't need to call delete on these, nor to explicitly add them
     * to the dieset, because the Die_encap_base constructor will make 
     * shared_ptrs out of them, and will also add them to the dieset. */
    auto p_compile_unit_die = new dwarf::encap::compile_unit_die(
    	dynamic_cast<dwarf::encap::Die_encap_base&>(*builtins[0UL]), s_builtins);

    auto p_pointer_type_die = new dwarf::encap::pointer_type_die(
    	dynamic_cast<dwarf::encap::Die_encap_base&>(*builtins[1UL]), 
        boost::optional<const std::string&>());

    auto p_int_die = new dwarf::encap::base_type_die(
    	dynamic_cast<dwarf::encap::Die_encap_base&>(*builtins[1UL]), s_int);
    p_int_die->set_byte_size(sizeof(int)).set_encoding(DW_ATE_signed);

    auto p_double_die = new dwarf::encap::base_type_die(
    	dynamic_cast<dwarf::encap::Die_encap_base&>(*builtins[1UL]), s_double);
    p_double_die->set_byte_size(sizeof(double)).set_encoding(DW_ATE_float);
    
    // fix up the DIE ptrs in None and NotImplemented to point at the void* DIE
    valNone.descr = builtins[2];
    valNotImplemented.descr = builtins[2];
    // note: descr ptr in Invalid stays 0, as that's what distinguishes it!
    
    // store pointers to the builtin int and double types, for pointer-comparison
    p_builtin_int_type = boost::dynamic_pointer_cast<dwarf::encap::base_type_die>(builtins[3]).get();
    p_builtin_double_type = boost::dynamic_pointer_cast<dwarf::encap::base_type_die>(builtins[4]).get();

    auto p_char_die = new dwarf::encap::base_type_die(
    	dynamic_cast<dwarf::encap::Die_encap_base&>(*builtins[1UL]), s_char);
    p_double_die->set_byte_size(1).set_encoding(DW_ATE_signed_char);

    auto p_const_char_die = new dwarf::encap::const_type_die(
    	dynamic_cast<dwarf::encap::Die_encap_base&>(*builtins[1UL]), boost::optional<const std::string&>());
    p_const_char_die->set_type(
    	boost::dynamic_pointer_cast<dwarf::spec::type_die>(
        	p_char_die->get_this()));
    
    auto p_const_char_pointer_type_die = new dwarf::encap::pointer_type_die(
    	dynamic_cast<dwarf::encap::Die_encap_base&>(*builtins[1UL]), boost::optional<const std::string&>());
    p_const_char_pointer_type_die->set_type(
    	boost::dynamic_pointer_cast<dwarf::spec::type_die>(
        	p_const_char_die->get_this()));
}

jmp_buf JumpBuffer;
void interrupt_handler(int signal)
{
    switch(signal)
    {
        case SIGSEGV:
            std::cout << "Caught segmentation fault!" << std::endl;
            break;
        case SIGFPE:
            std::cout << "Floating point exception. Division by zero?" << std::endl;
            break;
        case SIGILL:
            std::cout << "Illegal instruction executed!" << std::endl;
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
//     if(setjmp(JumpBuffer))
//     {
//         std::cout << "Caught signal during initialisation. Will now die." << std::endl;
//         exit(0);
//     }
//     //signal(SIGSEGV, interrupt_handler);
//     //signal(SIGFPE, interrupt_handler);
//     //signal(SIGILL, interrupt_handler);
// 
//     initialize_builtins(&ParathonValue::builtins);
	executable_path = argv[0];
    std::cout << "This is DwarfPython.\nCtrl-D exits." << std::endl;
    ParathonContext globals/*(ParathonValue::builtins)*/;
    globals.interpreterMode = true;
//    globals.assign("__name__", new ParathonValue("__main__"));

    int result;
    yy_extra_type a;
    YY_EXTRA_FOR_FILE(a, stdin);
    result = parse_loop(a, &globals);

    std::cout << std::endl;
    return result;
}

const char *Operator::opname()
{
    return "__undefined__";
}

void evaluate(SingleInput *si, ParathonContext* c)
{
    try
    {
        if (c->interpreterMode)
            si->evaluate_print(*c, std::cout);
        else
            si->evaluate(*c);
    }
    catch (ParathonException e) 
   // (...)
    {
        std::cerr << e.message /*"Error!"*/ << std::endl;
    }
}

val parathon_call(const char * name, val lhs)
{
    std::cerr << "Trying to ucall '" << name << "' on " << lhs << std::endl;
    //return lhs->call(name);
    return None;
}
val parathon_call(const char * name, val lhs, val rhs)
{
    if (lhs == None)
    {
        std::cerr << "Tried to call '" << name << "' on None" << std::endl;
        return None;
    }
    else
    {
       std::cerr << "Trying to call '" << name << "' on " << lhs << std::endl;
        //return lhs->call(name, rhs);
        return None;
    }
}
