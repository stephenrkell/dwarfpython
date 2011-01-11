#include <sys/mman.h>
#include <string.h>
#include <processimage/process.hpp>

#include "parathon.h"
#include "ast.h"
#include "ops.h"

using dwarf::lib::Dwarf_Unsigned;
using dwarf::lib::Dwarf_Ranges;
using dwarf::lib::Dwarf_Addr;

/* This helper keeps vtable initialization complexity out
 * of the generated entry points. */
val evaluate(Statement *arg)
{
	std::cerr << "Received a call from a generated entry point!" << std::endl;
	return arg->evaluate();
}

const unsigned MARKER_ADDRESS = 0x12345678U;

void *ideal_entry_point(...) __attribute__((optimize(3)));
void *ideal_entry_point(...)
{
	// call through an immediately-addressed object's vtable.
    return reinterpret_cast<Statement*>(MARKER_ADDRESS)->evaluate().i_ptr;
}

void end_ideal_entry_point(void);
void end_ideal_entry_point(void) {}

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
     
    auto subprogram_die = new encap::subprogram_die(
     dynamic_cast<encap::Die_encap_base&>(*(*p_builtins).toplevel()->resolve("cu.dwarfpython")), 
      std::string(name->getName()));
    // give it a low pc and a high pc
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
    subprogram_die->enclosing_compile_unit()->get_ranges()->push_back(
    	(lib::Dwarf_Ranges) { 
        	(unsigned) ret, 
            (unsigned) ret + sysconf(_SC_PAGE_SIZE), 
            lib::DW_RANGES_ENTRY });
    
    // give it a frame_base? YES, just make it ebp (no lexical blocks to worry about)
    Dwarf_Unsigned opcodes1[] = { DW_OP_breg4, sizeof (int) };     // vaddr 0x0..0x1
    Dwarf_Unsigned opcodes2[] = { DW_OP_breg4, 2 * sizeof (int) }; // vaddr 0x1..0x3
    Dwarf_Unsigned opcodes3[] = { DW_OP_breg5, 2 * sizeof (int) }; // vaddr 0x3..LAST+1
    
    /* These are x86-specific, assuming that an entry point has this prologue:
    
       0:   55                      push   %ebp
       1:   89 e5                   mov    %esp,%ebp
       3:   83 ec 10                sub    $0x10,%esp # <-- here 0x10 is just size of locals, 16-byte rounded

       and this epilogue:

      10:   c9                      leave  
      11:   c3                      ret    
      
      And this needs the following loclist (reg4 is esp, reg5 is ebp):
(loclist) {loc described by { 0x1: DW_OP_breg4((signed) 4); } (for vaddr 0x0..0x1), % i.e. esp + 1 word
           loc described by { 0x1: DW_OP_breg4((signed) 8); } (for vaddr 0x1..0x3), % i.e. esp + 2 words
           loc described by { 0x1: DW_OP_breg5((signed) 8); } (for vaddr 0x3..0x12)}% i.e. ebp + 2 words
    */
//     unsigned char prologue_bytes[] = { 0x55, 0x89, 0xe5, 0x83, 0xec, 0x00 /* SIZE_OF_LOCALS */ };
//     unsigned char call_bytes[]     = { 0xe8, 0x00, 0x00, 0x00, 0x00 }; // to be filled in...
//     /* needs to be PC-relative! */
//     *(signed*)&call_bytes[1] = (unsigned) &interpret
//      - ((unsigned) ret + sizeof prologue_bytes + sizeof call_bytes);
//     unsigned char epilogue_bytes[] = { 0xc9, 0xc3 };
//     
//     // now blat the bytes into the mmap()-returned block
//     unsigned char *pos = (unsigned char *) ret;
//     memcpy(pos, &prologue_bytes[0], sizeof prologue_bytes); pos += sizeof prologue_bytes;
//     memcpy(pos, &call_bytes[0], sizeof call_bytes); pos += sizeof call_bytes;
//     memcpy(pos, &epilogue_bytes[0], sizeof epilogue_bytes); pos += sizeof epilogue_bytes;
//     // FIXME: remember how much we wrote, so we can manage the free space within this block

	// new method: use the ideal entry point 
    size_t entry_point_size = (char*)&end_ideal_entry_point - (char*)&ideal_entry_point;
    // blat the bytes
    memcpy(ret, (void*) ideal_entry_point, entry_point_size);
    // find the AST node pointer in the instruction sequence
    Statement** searchp = reinterpret_cast<Statement**>(ret); 
    while (!((char*) searchp > (char*) ret + entry_point_size - sizeof (Statement*))) 
    {
        // debugging
    	std::cerr << "Bytes: " << std::hex  
        	<< (unsigned) *reinterpret_cast<unsigned char*>(searchp) << " "
            << (unsigned) *(reinterpret_cast<unsigned char*>(searchp)+1) << " "
            << (unsigned) *(reinterpret_cast<unsigned char*>(searchp)+2) << " "
            << (unsigned) *(reinterpret_cast<unsigned char*>(searchp)+3) << std::dec << std::endl;

    	if (*reinterpret_cast<unsigned*>(searchp) == MARKER_ADDRESS)
        {
            // overwrite the AST node pointer with the appropriate one
            *searchp = this->suite;
            std::cerr << "Installed AST node pointer for entry point " << this->name
    	        << ", AST at " << (void*) this->suite << std::endl;
			searchp++; // advance by a pointer's worth
        }
    	// advance by a byte's worth
    	else searchp = (Statement**) (((char*) searchp) + 1); 
	} 

    encap::loc_expr expr1(opcodes1, //expr1.lopc = 0; expr1.hipc = 1;
		(Dwarf_Unsigned)((char*)(ret)) + 0, (Dwarf_Unsigned)((char*)(ret) + 1)); 
    encap::loc_expr expr2(opcodes2,//expr2.lopc = 1; expr2.hipc = 3;
		(Dwarf_Unsigned)((char*)(ret)) + 1, (Dwarf_Unsigned)((char*)(ret) + 3)); 
    encap::loc_expr expr3(opcodes3, /*sizeof prologue_bytes + sizeof call_bytes + sizeof epilogue_bytes + 1*/ // <-- +1 is wrong here 
		(Dwarf_Unsigned)((char*)(ret) + 3), (Dwarf_Unsigned)((char*)(ret) + entry_point_size));
    
    encap::loclist loc(expr1); loc.push_back(expr2); loc.push_back(expr3);
    subprogram_die->set_frame_base(loc);
    
    // children: formal parameters
    // -- one untyped parameter per formal
	unsigned offset = 0;
    for (int i = 0; i < parameter_list->size(); i++)
    {
    	auto fp = new encap::formal_parameter_die(*subprogram_die,
            std::string(
            	dynamic_cast<NamePhrase&>(*parameter_list->get(i)->getValue()).getName()));
		
		// add the location description -- 
		Dwarf_Unsigned opcodes[] = { DW_OP_fbreg, offset };
		fp->set_location(
			encap::loclist(
				encap::loc_expr(opcodes, 0, std::numeric_limits<Dwarf_Addr>::max()))); 
		
		// increment the stack offset of the parameter
		offset += sizeof (void*);
		
		// add the type
		fp->set_type(dynamic_pointer_cast<spec::type_die>(p_builtin_pointer_type));
	}    
    
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
    image.register_anon_segment_description((process_image::addr_t)ret, 
        p_builtins, (process_image::addr_t) 0);
    
    return None;
}

