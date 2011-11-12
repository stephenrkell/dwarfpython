#include <sys/mman.h>
#include <string.h>
#include <libreflect.hpp>

#include "parathon.h"
#include "ast.h"
#include "ops.h"
#include "archdep.h"

using dwarf::lib::Dwarf_Unsigned;
using dwarf::lib::Dwarf_Ranges;
using dwarf::lib::Dwarf_Addr;
using pmirror::process_image;
using pmirror::self;

/* This helper keeps vtable initialization complexity out
 * of the generated entry points. */
val evaluate(Statement *arg)
{
	std::cerr << "Received a call from a generated entry point!" << std::endl;
	return arg->evaluate();
}

val FunctionDefinition::evaluate()
{
    //ParathonAssigner *a = this->name->getAssigner(c);
    //a->assign(new ParathonFunction(this->name, this->parameter_list, this->suite, c));
    //std::cout << "rar" << std::endl;
    //std::cerr << "Function definition not implemented!" << std::endl;
    
    /* Defining a function means: 
     * - adding an abstract description of it to the DwarfPython CU
     * - setting up a binding -- this is automatic
     * - defining a "generic" (arguments-indirected) entry point for it
     *   (we leave other, layout-specialised entry points until call time) */
     
	dwarf::encap::factory& f = dwarf::encap::factory::for_spec(dwarf::spec::DEFAULT_DWARF_SPEC);

	auto cu = dynamic_pointer_cast<encap::basic_die>((*p_builtins).toplevel()->resolve("cu.dwarfpython"));
	auto subprogram_die = 	dynamic_pointer_cast<encap::subprogram_die>(
		f.create_die(DW_TAG_subprogram, cu, 
		std::string(name->getName())));

    // -- just allocate a heap block big enough for 
    //     the main trampoline + n (say 8 or 16) different specialised entry points
    //     --- maybe make it page-sized so we can give it PROT_EXEC
    void *ret = mmap(NULL, sysconf(_SC_PAGE_SIZE), PROT_READ|PROT_WRITE|PROT_EXEC, 
    	MAP_PRIVATE|MAP_ANONYMOUS, -1 /* no fd */, 0);
    assert(ret && ret != MAP_FAILED);
    subprogram_die->set_low_pc(
    	(encap::attribute_value::address) { (Dwarf_Addr) ret });
    subprogram_die->set_high_pc(
    	(encap::attribute_value::address) { (Dwarf_Addr) ret + sysconf(_SC_PAGE_SIZE) });
    
    // now adjust the containing CU's rangelist to include this range
    assert(subprogram_die->enclosing_compile_unit());
	auto opt_ranges = subprogram_die->enclosing_compile_unit()->get_ranges();
	assert(opt_ranges);
	auto ranges = *opt_ranges;
	ranges.push_back(
    	(lib::Dwarf_Ranges) { 
        	(unsigned long) ret, 
            (unsigned long) ret + sysconf(_SC_PAGE_SIZE), 
            lib::DW_RANGES_ENTRY });
	assert(ranges.size() > 0);
	assert(dynamic_pointer_cast<encap::compile_unit_die>(subprogram_die->enclosing_compile_unit()));
	dynamic_pointer_cast<encap::compile_unit_die>(subprogram_die->enclosing_compile_unit())
		->set_ranges(ranges);
	auto p_encap_cu = dynamic_pointer_cast<encap::compile_unit_die>(subprogram_die->enclosing_compile_unit()).get();	
	assert(subprogram_die->enclosing_compile_unit()->get_ranges()->size() > 0);

	// children: formal parameters
	// -- one untyped parameter per formal
	// first generate the list of arguments
	for (int i = 0; i < parameter_list->size(); i++)
	{
		auto fp = dynamic_pointer_cast<encap::formal_parameter_die>(
			f.create_die(
				DW_TAG_formal_parameter,
				subprogram_die,
				std::string(
					dynamic_cast<NamePhrase&>(*parameter_list->get(i)->getValue()).getName()
				)
			));
		// add the type
		fp->set_type(dynamic_pointer_cast<spec::type_die>(p_builtin_reference_type));
	}
	
	// let the archdep code do the rest
	size_t out_sz;
	write_entry_point_and_fp_locations(
		this,
		subprogram_die, /* determines ABI */
		ret, /* dest */
		sysconf(_SC_PAGE_SIZE), /* max size of buffer */
		&out_sz /* #bytes written */
	);
	
        
    // children: local variables?
    // -- we simply enumerate all non-argument non-prefixed identifiers appearing in the AST
    // -- can we have computed-identifier locals in functions in Python?
    // -- computed variable names, where they are used, result in CoW of the subprogram?
    // HMM, actually on assigning to a computed name, I think we just add it and don't CoW
    // BUT *references* to computed names are the problem, because they might map to any block
    // NEED to understand Python's scoping semantics better -- how much dynamic scoping is there?
    // FIXME
    
    // children: lexical blocks?
    // -- for now, don't expand lexical blocks: just work at whole-function scope
    // -- what about name collisions? for now, just finesse this.
    // HMM. Actually we might really want lexical blocks. Oh well, doesn't matter for now.
    
    // problem 1: dynamic generation of entry points makes breakpoints difficult
    // solution 1: because we eagerly generate the generic version,
    //             any function is available for breakpointing the moment it is defined,
    //             and that breakpoint will always "work"
    // problem 2: CoW has unexpected effects on debugging state e.g. breakpoints
    // -- one DWARF function identity may become two, at any random moment.
    // solution 2a: when we CoW an entry point, we have to signal the debugger, much as if
    // a dynamic software update has occurred.
    // solution 2b: adding a new local variable doesn't require CoW, because for any local
    // stored in a hash table (say),  the lookup procedure is the same---
    // we simply need to ensure that the variable name is an input into the 
    // location expression that computes the variable's address.
    // We could implement this simply by making each Python-implemented function
    // have a single local variable, i.e. a C++ hash_map,
    // augmented by location descriptions for each named variable used
    
    // Debugging
    std::cerr << "After defining a new function, builtins is as follows." << std::endl;
    std::cerr << (*p_builtins);
    
    // now we can register the entry -- NOTE we couldn't do this earlier
    // because before writing to the mmap()'d region, it need not show up
    // in the memory map (precisely, we need it to show up as nonempty and [anon],
    // and it might just be zero-sized and/or unnamed).
    self.register_anon_segment_description((process_image::addr_t)ret, 
        p_builtins, (process_image::addr_t) 0);
    
    return None;
}

