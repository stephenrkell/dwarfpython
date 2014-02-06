#ifndef DWARFPYTHON_INIT_HH_
#define DWARFPYTHIN_INIT_HH_

#include <map>
#include <dwarfpp/encap.hpp>

//builtins(dwarf::spec::DEFAULT_DWARF_SPEC);
extern std::shared_ptr<dwarf::encap::dieset> p_builtins;

/* This is the interpreter state. */
extern bool interpreterMode; /* whether we're acting as a REPL or not */
extern shared_ptr<encap::compile_unit_die> toplevel; /* compile_unit DIE for this interpreter instance */
extern std::map<std::string, std::string > import_list; /* imported visible namespaces:
 maps Python name e.g. "c" to mapped file name e.g. "/lib/i686/nosegneg/libc-2.7.so" */

extern const val& None;
extern const val& NotImplemented;
extern const val& Invalid;

extern const char *executable_path;

extern shared_ptr<encap::base_type_die> p_builtin_int_type; // overwritten in init
extern shared_ptr<encap::base_type_die> p_builtin_double_type; // overwritten in init
extern shared_ptr<encap::base_type_die> p_builtin_char_type;
extern shared_ptr<encap::const_type_die> p_builtin_const_char_type;
extern shared_ptr<encap::pointer_type_die> p_builtin_pointer_type;
extern shared_ptr<encap::reference_type_die> p_builtin_reference_type;
extern shared_ptr<encap::pointer_type_die> p_builtin_const_char_pointer_type;
extern shared_ptr<encap::array_type_die> p_builtin_const_char_array_type;

#endif
