#ifndef PARATHON_H
#define PARATHON_H

#include <dwarfpp/adt.hpp>
#include <dwarfpp/encap.hpp>
#include <pmirror/process.hpp>

//class ParathonValue;
/*typedef void ParathonValue;*/ /* val replaces ParathonValue */
//typedef dwarf::encap::die ParathonContext;
struct ParathonContext; /* FIXME: remove this */
//typedef int parathon_int;
//typedef double parathon_float;

class SingleInput;

using boost::shared_ptr;
using boost::dynamic_pointer_cast;
using namespace dwarf;
using boost::shared_ptr;

extern shared_ptr<encap::base_type_die> p_builtin_int_type; // overwritten in init
extern shared_ptr<encap::base_type_die> p_builtin_double_type; // overwritten in init
extern shared_ptr<encap::base_type_die> p_builtin_char_type;
extern shared_ptr<encap::const_type_die> p_builtin_const_char_type;
//extern shared_ptr<encap::pointer_type_die> p_builtin_const_char_pointer_type;
extern shared_ptr<encap::pointer_type_die> p_builtin_pointer_type;
extern shared_ptr<encap::reference_type_die> p_builtin_reference_type;
extern shared_ptr<encap::array_type_die> p_builtin_const_char_array_type;

/* defined in main.cc */
extern const char *executable_path;

#include "val.h"

extern shared_ptr<encap::dieset> p_builtins;

/* we don't need this yet -- try to avoid it */
/* extern process_image image; */

#include "lexer.h"
#include <ffi.h>

#include <sstream>
using std::string;

/* FIXME: stuff below is still in transition from Parathon -> DwarfPython .*/

class ParathonException
{
    public: string message;
    ParathonException(string message) { this->message = message; }
    ParathonException(string m1, string m2, string m3) { 
        std::stringstream s;
	    s << m1 << m2 << m3;
	    this->message = s.str();
    }
    ParathonException(string message, int linenum) {     
        std::stringstream s;
	    s << "  Line " << linenum << ":" << std::endl;
	    s << message;
	    this->message = s.str();
    }
};

class ParathonReturn
{
public: 
    val value;
    ParathonReturn(val value) { this->value = value; }
}
;
/*class ReadOnlyProperty : public ParathonValue
{
    public: ReadOnlyProperty(void *value);
}
;

class ParathonContext : public ParathonValue
{
    public:
        ParathonContext(ParathonValue *);
}
;*/
        
/* This is the interpreter state. */
extern bool interpreterMode; /* whether we're acting as a REPL or not */
extern shared_ptr<encap::compile_unit_die> toplevel; /* compile_unit DIE for this interpreter instance */
extern std::map<std::string, std::string > import_list; /* imported visible namespaces:
 maps Python name e.g. "c" to mapped file name e.g. "/lib/i686/nosegneg/libc-2.7.so" */

int parse_loop(yy_extra_type extra);
std::ostream& operator<<(std::ostream &strm, const val& stmt);
int yyparse();
void evaluate(SingleInput *si);
void evaluate_end();
#endif
