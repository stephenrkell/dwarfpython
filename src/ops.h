#ifndef DWARFPYTHON_OPS_H_
#define DWARFPYTHON_OPS_H_

#include "parathon.h"

class Statement;
class process_image;
extern process_image image;

/* Primitive operations defined by the interpreter on AST nodes. */

/* Computer Python truth value of an arbitrary value. */
bool is_true(val value);
/* We might want to make this take a void *, 
 * because val exists only to simplify allocation of temporaries
 * (i.e. to make the compiler do it, using its "value" abstraction). */

/* normalize_val()
   -- pulls any primitive value into an immediate value
   -- leaves any non-primitive value as a non-immediate.
 * i.e. it relieves us from handling non-immediate primitives. */
val normalize_val(val value);

/* Get a pointer pointing to a memory location containing the 
 * raw bytes of the object denoted by val. For immediate vals,
 * this writes val to a temporary variable (if passed), else
 * just passes the address in the caller's val. */
void *raw_address_of_val(const val& value, val *temporary);

/* Resolve a name to an object. Use the program context directly! */
val lookup_name(const std::string& s);

void assign_to(val loc, val v);

/* Print an object to a stream, as a string. */
void print_value_to_stream(void *value, std::ostream& s, 
	shared_ptr<type_die> descr = shared_ptr<type_die>());

void print_value_to_stream(val value, std::ostream& s);

/* Function called into by generated entry points
 * -- this should be a minimal wrapper around evaluate()
 * -- it exists only to recover a neat context from the messy entry point stack frame
 * -- entry point frames are messy why? they should be just like any other....
 * -- Get rid of sizes and ap: Dwarf + stack unwinding is "the way". This function *is* evaluate!
 * -- Stack walking is fairly fast. PC => Dwarf subprogram can be made fast. */
int interpret(Statement *statement); /*, encap::subprogram_die *subp, va_list ap, short *sizes) */

/** Call a function, using libffi. */
val call_function(val function, std::vector<val> *params);

#endif

/* Vaguely interesting design decisions: 
 * Don't pass around a "context" object: the program state *is* the context!
 * Don't make evaluate() a virtual function: want a single entry point?
 * -- Actually, making a single breakpoint break in multiple locations is just fine.
 * -- "evaluate" just needs a single argument, namely the AST
 * -- we can use vtable access + indirect call to call the right evaluate() */
