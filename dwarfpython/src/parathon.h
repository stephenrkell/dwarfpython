#ifndef PARATHON_H
#define PARATHON_H

#include <dwarfpp/adt.hpp>
#include <dwarfpp/encap.hpp>
#include <dwarfpp/encap_adt.hpp>
namespace dwarf { namespace encap { 
typedef dwarf::encap::Die_encap_compile_unit compile_unit_die; 
typedef dwarf::encap::Die_encap_base_type base_type_die; 
typedef dwarf::encap::Die_encap_pointer_type pointer_type_die; 
typedef dwarf::encap::Die_encap_const_type const_type_die; 
}}

//class ParathonValue;
/*typedef void ParathonValue;*/ /* val replaces ParathonValue */
//typedef dwarf::encap::die ParathonContext;
struct ParathonContext;
typedef int parathon_int;
typedef double parathon_float;

extern dwarf::encap::base_type_die *p_builtin_int_type;
extern dwarf::encap::base_type_die *p_builtin_double_type;
extern dwarf::encap::base_type_die *p_builtin_char_type;
extern dwarf::encap::const_type_die *p_builtin_const_char_type;
extern dwarf::encap::pointer_type_die *p_builtin_const_char_pointer_type;

/* defined in main.cc */
extern const char *executable_path;

struct val
{
 	bool is_immediate;
    union 
    {
        int i_int;
        double i_double;
        void *i_ptr;
    };
    boost::shared_ptr<dwarf::spec::basic_die> descr;
    bool operator==(const val& v) 
    { return this->is_immediate == v.is_immediate &&
         (this->is_immediate && this->descr.get() == p_builtin_int_type) ? 
       		(this->i_int == v.i_int)
       : (this->is_immediate && this->descr.get() == p_builtin_double_type) ?
            (this->i_double == v.i_double)
       : (!this->is_immediate && this->i_ptr == v.i_ptr);
	}
    bool operator!=(const val& v) { return !(*this == v); }
};
/*extern val valInvalid;*/
extern const val& Invalid;
/*extern val valNone;*/
extern const val& None;
/*extern val valNotImplemented;*/
extern const val& NotImplemented;
/* Note: we record None as a null pointer, so its descr will be set.
 * FIXME: add a constant for this. It will need static initialization
 * in order to grab the builtin DWARF type die for a pointer-to-unspecified. */
extern dwarf::encap::dieset builtins;

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
struct ParathonContext
{
  	bool interpreterMode; /* whether we're acting as a REPL or not */
    dwarf::encap::die *toplevel; /* compile_unit DIE for this interpreter instance */
    std::map<std::string, std::string > import_list; /* imported visible namespaces:
     maps Python name e.g. "c" to mapped file name e.g. "/lib/i686/nosegneg/libc-2.7.so" */
};

class ParathonAssigner
{
    public:
        virtual void assign(val)=0;
}
;
class ParathonContextAssigner : public ParathonAssigner
{
    private:
        val context;
        string name;

    public:
        ParathonContextAssigner(val c, string name);
        void assign(val);
}
;

int parse_loop(yy_extra_type extra, ParathonContext* c);
val parathon_call(const char *fn, val lhs);
val parathon_call(const char *fn, val lhs, val rhs);
std::ostream& operator<<(std::ostream &strm, const val& stmt);
int yyparse();

#define BASIC_EVALUATE(classname, function) \
    val classname::evaluate(ParathonContext& c) \
    { \
        return parathon_call(function, this->lhs->evaluate(c), this->rhs->evaluate(c)); \
    }
#endif
