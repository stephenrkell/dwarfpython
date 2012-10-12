#include "ast.h"
#include "parathon.h"
#include "parathon.yy.hh"
#include "lexer.h"
#include "parathon.l.h"
//#include "builtins.hh"
#include <string.h>
#include "signal.h"
#include "setjmp.h"
#include <dwarfpp/encap.hpp>

//builtins(dwarf::spec::DEFAULT_DWARF_SPEC);
std::shared_ptr<dwarf::encap::dieset> p_builtins;

/* This is the interpreter state. */
bool interpreterMode; /* whether we're acting as a REPL or not */
shared_ptr<encap::compile_unit_die> toplevel; /* compile_unit DIE for this interpreter instance */
std::map<std::string, std::string > import_list; /* imported visible namespaces:
 maps Python name e.g. "c" to mapped file name e.g. "/lib/i686/nosegneg/libc-2.7.so" */

val valNone = { false, { i_ptr: 0 }, val::NONE };
const val& None = valNone;
val valNotImplemented = { false, { i_ptr: (void*)1 }, val::NONE };
const val& NotImplemented = valNotImplemented;
val valInvalid = { false, { i_ptr: 0 }, val::INVALID };
const val& Invalid = valInvalid;

const char *executable_path;

shared_ptr<encap::base_type_die> p_builtin_int_type; // overwritten in init
shared_ptr<encap::base_type_die> p_builtin_double_type; // overwritten in init
shared_ptr<encap::base_type_die> p_builtin_char_type;
shared_ptr<encap::const_type_die> p_builtin_const_char_type;
shared_ptr<encap::pointer_type_die> p_builtin_pointer_type;
shared_ptr<encap::reference_type_die> p_builtin_reference_type;
shared_ptr<encap::pointer_type_die> p_builtin_const_char_pointer_type;
shared_ptr<encap::array_type_die> p_builtin_const_char_array_type;
void init() __attribute__((constructor));
void init()
{
	using namespace dwarf::encap;
	using boost::dynamic_pointer_cast;
	
	p_builtins = std::make_shared<dwarf::encap::dieset>(dwarf::spec::DEFAULT_DWARF_SPEC);
	dwarf::encap::dieset& builtins = *p_builtins;

	/* We don't need to call delete on these, nor to explicitly add them
     * to the dieset, because the factory will make 
     * shared_ptrs out of them, and also add them to the dieset. */
	dwarf::encap::factory& f = dwarf::encap::factory::for_spec(dwarf::spec::DEFAULT_DWARF_SPEC);
	
	// alias the toplevel DIE as an encap::basic_die, to satisfy argument matching
	auto toplevel_as_basic = dynamic_pointer_cast<encap::basic_die>(
		builtins[0UL]);
	assert(toplevel_as_basic);
	
	auto p_compile_unit_die = dynamic_pointer_cast<encap::compile_unit_die>(
		f.create_die(DW_TAG_compile_unit, toplevel_as_basic, std::string("cu.dwarfpython")));
		
		
		
	assert(p_compile_unit_die);
    encap::rangelist rs; p_compile_unit_die->set_ranges(rs);

    auto p_pointer_type_die = dynamic_pointer_cast<encap::pointer_type_die>(
    	 f.create_die(DW_TAG_pointer_type, p_compile_unit_die, std::string("void_pointer_type")));
	p_pointer_type_die->set_byte_size(sizeof (void*));

    auto p_reference_type_die = dynamic_pointer_cast<encap::reference_type_die>(
		f.create_die(DW_TAG_reference_type, p_compile_unit_die, std::string("void_reference_type")));
	p_reference_type_die->set_byte_size(sizeof (void*));

    auto p_int_die = dynamic_pointer_cast<encap::base_type_die>(
		f.create_die(DW_TAG_base_type, p_compile_unit_die, std::string("int")));
    p_int_die->set_byte_size(sizeof(int))->set_encoding(DW_ATE_signed);

    auto p_double_die = dynamic_pointer_cast<encap::base_type_die>(
		f.create_die(DW_TAG_base_type, p_compile_unit_die, std::string("double")));
    p_double_die->set_byte_size(sizeof(double))->set_encoding(DW_ATE_float);
    
//    // fix up the DIE ptrs in None and NotImplemented to point at the void* DIE
//    valNone.kind = builtins.toplevel()->resolve("cu.dwarfpython::void_pointer_type");
//    valNotImplemented.descr = valNone.descr; 
//    // note: descr ptr in Invalid stays 0, as that's what distinguishes it!
    
    auto p_char_die = dynamic_pointer_cast<encap::base_type_die>(
     	f.create_die(DW_TAG_base_type, p_compile_unit_die, std::string("char")));
    p_char_die->set_byte_size(1)->set_encoding(DW_ATE_signed_char);

    auto p_const_char_die = dynamic_pointer_cast<encap::const_type_die>(
		f.create_die(DW_TAG_const_type, p_compile_unit_die));
    p_const_char_die->set_type(dynamic_pointer_cast<spec::type_die>(p_char_die));
    
    auto p_const_char_pointer_type_die = dynamic_pointer_cast<encap::pointer_type_die>(
		f.create_die(DW_TAG_pointer_type, p_compile_unit_die, std::string("const_char_pointer_type")));
	p_const_char_pointer_type_die->set_type(dynamic_pointer_cast<spec::type_die>(p_const_char_die));
	p_const_char_pointer_type_die->set_byte_size(sizeof (char*));

    auto p_const_char_array_type_die = dynamic_pointer_cast<encap::array_type_die>(
     	f.create_die(DW_TAG_array_type, p_compile_unit_die, std::string("const_char_array_type")));
    p_const_char_array_type_die->set_type(dynamic_pointer_cast<spec::type_die>(p_const_char_die));

    // store pointers to the builtin int/double/string types, for pointer-comparison
    p_builtin_int_type = dynamic_pointer_cast<encap::base_type_die>(
     p_compile_unit_die->named_child("int")); assert(p_builtin_int_type);
    p_builtin_double_type = dynamic_pointer_cast<encap::base_type_die>(
     p_compile_unit_die->named_child("double")); assert(p_builtin_double_type);
    //p_builtin_const_char_pointer_type = dynamic_pointer_cast<encap::pointer_type_die>(
    // p_compile_unit_die->named_child("const_char_pointer_type")); assert(p_builtin_const_char_pointer_type);
    p_builtin_const_char_array_type = dynamic_pointer_cast<encap::array_type_die>(
     p_compile_unit_die->named_child("const_char_array_type")); assert(p_builtin_const_char_array_type);
	p_builtin_pointer_type = dynamic_pointer_cast<encap::pointer_type_die>(
	 p_compile_unit_die->named_child("void_pointer_type")); assert(p_builtin_pointer_type);
	p_builtin_reference_type = dynamic_pointer_cast<encap::reference_type_die>(
	 p_compile_unit_die->named_child("void_reference_type")); assert(p_builtin_reference_type);
    
    // debugging
    std::cerr << "Started DwarfPython with builtins as follows." << std::endl << builtins;
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

int parse_loop(yy_extra_type extra)
{
    int status;
    yypstate *ps = yypstate_new ();
    yyscan_t scanner;
    YYSTYPE lval;
    yylex_init_extra( &extra, &scanner );

    do {
        setjmp(JumpBuffer); 

        status = yypush_parse(ps, yylex(&lval, scanner), &lval, NULL);
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
    //ParathonContext globals/*(ParathonValue::builtins)*/;
    interpreterMode = true;
    toplevel = dynamic_pointer_cast<encap::compile_unit_die>((*p_builtins)[1UL]);
//    globals.assign("__name__", new ParathonValue("__main__"));

    int result;
    yy_extra_type a;
    YY_EXTRA_FOR_FILE(a, stdin);
    result = parse_loop(a);

    std::cout << std::endl;
    return result;
}

const char *Operator::opname()
{
    return "__undefined__";
}

void evaluate(SingleInput *si)
{
    try
    {
        if (interpreterMode)
            si->evaluate_print(std::cout);
        else
            si->evaluate();
    }
    catch (ParathonException e) 
    //(...)
    {
        std::cerr << e.message /* "Error!" */<< std::endl;
    }
}
void evaluate_end() {}

/*val parathon_call(const char * name, val lhs)
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
*/
