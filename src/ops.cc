#include <string>
#include <iostream>
#include "parathon.h"
#include "ops.h"
#include "util.h"

#include <alloca.h>
#include <ffi.h>
#include <sys/types.h>
#include <cstdarg>

#include <dwarfpp/cxx_compiler.hpp>
#include <dwarfpp/regs.hpp>

#include <pmirror/process.hpp>
#include <pmirror/unw_regs.hpp>

#include <libreflect.hpp>

using namespace dwarf;
using dwarf::spec::type_die;
using dwarf::spec::base_type_die;
using dwarf::spec::array_type_die;
using dwarf::spec::pointer_type_die;
using dwarf::spec::with_dynamic_location_die;
using dwarf::spec::subprogram_die;
using pmirror::process_image;
using pmirror::self;

val normalize_val(val value)
{
	if (value.is_immediate) return value;
	else
	{
		auto descr = self.discover_object_descr(
			reinterpret_cast<process_image::addr_t>(value.i_ptr), 
			shared_ptr<type_die>());
		if (descr->get_tag() != DW_TAG_base_type) return value;
		else 
		{
			auto p_base_type = dynamic_pointer_cast<base_type_die>(descr);
			assert(p_base_type->get_encoding());
			// read the value into an immediate val
			/* Don't support bit-offset or bit-size for now */
			assert(
				(!p_base_type->get_bit_offset() || *p_base_type->get_bit_offset() == 0)
				&&  (!p_base_type->get_bit_size() 
				|| *p_base_type->get_bit_size() == 8 * *p_base_type->get_byte_size()));
		#define ENC_AND_SZ(enc, sz) ((((unsigned short) (enc))<<16)|(unsigned short) (sz))
			switch (ENC_AND_SZ(p_base_type->get_encoding(),
					*p_base_type->get_byte_size()))
			{
				case (ENC_AND_SZ(DW_ATE_signed_char, 1)): 
					return (val) { true, { i_int: *(int8_t*)value.i_ptr }, val::INT};
				case (ENC_AND_SZ(DW_ATE_unsigned_char, 1)): 
					return (val) { true, { i_int: *(uint8_t*)value.i_ptr }, val::INT};
				case (ENC_AND_SZ(DW_ATE_signed, 1)): 
					return (val) { true, { i_int: *(int8_t*)value.i_ptr }, val::INT};
				case (ENC_AND_SZ(DW_ATE_unsigned, 1)): 
					return (val) { true, { i_int: *(uint8_t*)value.i_ptr }, val::INT};
				case (ENC_AND_SZ(DW_ATE_signed, 2)): 
					return (val) { true, { i_int: *(int16_t*)value.i_ptr }, val::INT};
				case (ENC_AND_SZ(DW_ATE_unsigned, 2)): 
					return (val) { true, { i_int: *(uint16_t*)value.i_ptr }, val::INT};
				case (ENC_AND_SZ(DW_ATE_signed, 4)): 
					return (val) { true, { i_int: *(int32_t*)value.i_ptr }, val::INT};
				case (ENC_AND_SZ(DW_ATE_unsigned, 4)): 
					return (val) { true, { i_int: *(uint32_t*)value.i_ptr }, val::INT};
				case (ENC_AND_SZ(DW_ATE_signed, 8)): 
					return (val) { true, { i_int: (int) *(int64_t*)value.i_ptr }, val::INT};
				case (ENC_AND_SZ(DW_ATE_unsigned, 8)): 
					return (val) { true, { i_int: (unsigned) *(uint64_t*)value.i_ptr }, val::INT};
				case (ENC_AND_SZ(DW_ATE_float, sizeof (float))): 
					return (val) { true, { i_double: *(float*)value.i_ptr }, val::DOUBLE};
				case (ENC_AND_SZ(DW_ATE_float, sizeof (double))): 
					return (val) { true, { i_double: *(double*)value.i_ptr }, val::DOUBLE};
				default:  /* we do not support this base type! */ assert(false);
			}
		#undef ENC_AND_SZ
		}
	}
}

void *raw_address_of_val(const val& value, val *temporary)
{
	/* "reference" behaviour -- pass the address of the object denoted by val */
	if (value.is_immediate)
	{
		if (temporary)
		{
			/* Caller has hinted that their val does not have appropriate
			 * lifetime. */
			*temporary = value;
			return (void*) &temporary->i_double;
		}
		else
		{
			return (void*) &value.i_double;
		}
	}
	else
	{
		return (void*) value.i_ptr;
	}
}

bool is_true(val value) 
{ 
	/* From Python 2.5 docs:
		Any object can be tested for truth value, for use in an if or while condition or as operand of the Boolean operations below. 
		The following values are considered false:

		None
		False
		zero of any numeric type, for example, 0, 0L, 0.0, 0j.
		any empty sequence, for example, '', (), [].
		any empty mapping, for example, {}.
		instances of user-defined classes, if the class defines a __nonzero__() or __len__() method, when that method returns the integer zero or bool value False.3.1
		All other values are considered true -- so objects of many types are always true.

		Operations and built-in functions that have a Boolean result always return 0 or False for false and 1 or True for true, unless otherwise stated. (Important exception: the Boolean operations "or" and "and" always return one of their operands.)	
	*/
	if (value.is_immediate)
	{
		switch (value.kind)
		{
			case val::NONE:
				return false;
			case val::INVALID:
				return true;
			case val::INT:
				return value.i_int != 0;
			case val::DOUBLE:
				return value.i_double != 0.0;

			case val::CHAR_PTR:
			case val::OTHER_PTR:
			case val::TBD:
			/* These are non-immediate */
				std::cerr << "Warning: processing an immediate pointer value -- this shouldn't happen!"
					<< std::endl;
				goto non_immediate;
			default: assert(false);
		}
	}
	else
	{
	non_immediate:
		//if (value.i_ptr == &None) return false;
		if (value == None) return false;
		
		/* test sequences and mappings (only arrays for now -- FIXME) */
		auto raw_descr = self.discover_object_descr(
			reinterpret_cast<process_image::addr_t>(value.i_ptr),
			shared_ptr<type_die>());
		assert(raw_descr);
		
		if (raw_descr->get_tag() == DW_TAG_subprogram) return true;
		else assert(dynamic_pointer_cast<type_die>(raw_descr));

		shared_ptr<type_die> type_descr = dynamic_pointer_cast<type_die>(raw_descr);
		
		if (type_descr->get_tag() == DW_TAG_array_type)
		{
			// FIXME
			assert(false);
		}
		
		
		/* test user-defined classes with __nonzero__ or __len__ */
		if (dynamic_pointer_cast<spec::with_named_children_die>(type_descr))
		{
			auto named_child_descr = dynamic_pointer_cast<spec::with_named_children_die>(type_descr);
			assert(named_child_descr);
			if (named_child_descr->named_child("__nonzero__") 
			||  named_child_descr->named_child("__len__"))
			{
				// FIXME
				assert(false);
			}
		}
	}
		
	return true; 
		
}

bool lookup_name_pred(spec::basic_die& d)
{
	/* We want a DIE that has a runtime location and,
 	* if it is a program_element,
 	* is not just a declaration. */
	std::cerr << "Testing die with name " << (d.get_name() ? *d.get_name() : "(no name)")
		<< std::endl;
	if (dynamic_cast<spec::with_static_location_die *>(&d) 
	 || dynamic_cast<spec::with_dynamic_location_die *>(&d) 
	 || dynamic_cast<spec::member_die *>(&d))
	{   /* About ^^ this test: locals, formal parameters and fields are not 
		 * with_static_location_dies, but they have location in a particular
		 * execution context. We assume that the caller (of lookup_name) will
		 * have such a context available. */
		spec::program_element_die *p_prog_el = dynamic_cast<spec::program_element_die *>(&d);
		if (!p_prog_el)
		{
			std::cerr << "Success: we like this DIE." << std::endl;
			return true;
		}
		else 
		{
			if (!p_prog_el->declaration() || !*p_prog_el->declaration())
			{
				std::cerr << "Success: we like this DIE." << std::endl;
				return true;			
			}
			else
			{
				std::cerr << "Failure: DIE is only a declaration ." << std::endl;
				return true;			
			
			}
		}
	}
	else 
	{
		std::cerr << "Failure: DIE has no runtime location." << std::endl;
		return false;
	}
		
}
struct stack_walk_output
{
	unw_word_t frame_base;
	unw_word_t ip;
	std::vector<boost::shared_ptr<spec::with_named_children_die> > *starting_points;
};
static int lexical_name_lookup_handler(
		process_image *image,
		unw_word_t frame_sp, unw_word_t frame_ip, 
		const char *frame_proc_name,
		unw_word_t frame_caller_sp,
		unw_word_t frame_callee_ip,
		unw_cursor_t frame_cursor,
		unw_cursor_t frame_callee_cursor,
		void *arg) __attribute__((noinline)); // for builtin_return_address
static int lexical_name_lookup_handler(
		process_image *image,
		unw_word_t frame_sp, unw_word_t frame_ip, 
		const char *frame_proc_name,
		unw_word_t frame_caller_sp,
		unw_word_t frame_callee_ip,
		unw_cursor_t frame_cursor,
		unw_cursor_t frame_callee_cursor,
		void *arg)
{
	stack_walk_output *output = reinterpret_cast<stack_walk_output *>(arg);
	auto p_starting_points = output->starting_points;
	std::cerr << "Currently we have " << p_starting_points->size() << " starting points."
		<< std::endl;

	// if we hit an entry point...
	if (image->discover_object_memory_kind(
		(process_image::addr_t)frame_ip) == process_image::ANON) // HACK: want a better test here
	{
		std::cerr << "Stack walk hit an entry point..." << std::endl;
		
		// ... we should be able to discover a description,
		// which is itself a subprogram ( => has named children)
		auto discovered = image->discover_object(frame_ip, 0);
		assert(discovered);
		assert(dynamic_pointer_cast<spec::subprogram_die>(discovered));
		assert(dynamic_pointer_cast<spec::with_named_children_die>(discovered));
		
		// ... add it to the list of starting points
		p_starting_points->push_back(
			dynamic_pointer_cast<spec::with_named_children_die>(discovered));

		// calculate and output the frame base
		pmirror::libunwind_regs my_regs(&frame_cursor); 
		output->frame_base = dwarf::lib::evaluator(
			/* loclist = */ *dynamic_pointer_cast<spec::subprogram_die>(discovered)->get_frame_base(),
			/* vaddr = */ /* needs to be CU-relative! */
				frame_ip - /*image->get_dieset_base(discovered->get_ds())*/
				(discovered->enclosing_compile_unit()->get_low_pc() ? 
				 discovered->enclosing_compile_unit()->get_low_pc()->addr : 0UL), /* This is our file-relative IP within the function whose frame includes the local allocation */
			/* spec = */ spec::DEFAULT_DWARF_SPEC,
			/* regs = */ &my_regs,
			/* optional<Dwarf_Signed> frame_base = */ boost::optional<lib::Dwarf_Signed>(),
			/* const std::stack<Dwarf_Unsigned>& initial_stack = */ std::stack<lib::Dwarf_Unsigned>()
		).tos();
		
		// output message and frame IP
		std::cerr << "Added starting point DIE " << *discovered
			<< "paired with frame having caller SP " 
			<< std::hex << frame_caller_sp << std::dec
			<< " and frame base "
			<< std::hex << output->frame_base << std::dec 
			<< " and saved IP " << std::hex << frame_ip << std::dec
			<< "; terminating stack walk..." << std::endl;
		output->ip = frame_ip;
		
		// ... and (FOR NOW, only) terminate
		return 1;
	}
	// else if we should terminate
	// HACK: use evaluate() end marker
	else if ((process_image::addr_t) frame_ip >= (process_image::addr_t) evaluate 
  		&& (process_image::addr_t) frame_ip < (process_image::addr_t) evaluate_end)
	{
		std::cerr << "Stack walk hit evaluate() -- terminating." << std::endl;
		return 1;
	}
	
	// return 0 means "carry on"
	std::cerr << "Stack walk continuing." << std::endl;
	return 0;
}

val lookup_name(const std::string& name) 
{
	/* Python name lookup rules: 
 	* First look in the local lexical context. 
 	* THEN... are there enclosing contexts to worry about? Yes, certainly
 	* in the case of nested functions, and possibly others.
 * -- We want to eliminate ParathonContext... use the program context directly!
 * -- Stack-walking is fine for native frames... what about interpreter-internal frames?
 * -- I'm thinking about lexical blocks nested within Python constructs here.
 * -- Maybe we just maintain a list of all Python eval functions that define a new lexical scope? 
 * -- YES. And we can keep walking into a calling function iff it lexically encloses us 
  	(i.e. once we walk past the current function, hop up the *static* Dwarf-hop link and find the
   	corresponding on-stack dynamic entry, if any exists. Otherwise skip to the Python globals,
   	including any imported module namespaces (there are no other "system" globals).)
   	HMM. Need to think about what happens with multiple levels of function nesting.
   	BUT I'm fairly sure this is sufficient. */
	
	// simple HACK to get us going: add the current subprogram to the starting points,
	// FIRST.

	/* The context records which portions of the process map namespace
 	* (i.e. which libraries' DWARF records) are visible. */
	
	// HACK to test: if we haven't executed (implemented) any "import" statements yet,
	// import our own DWARF info so we can test name resolution.
//    if (import_list.size() == 0)
//    {
//    	import_list.insert(
//        	std::make_pair(
//            	std::string("_self"), 
//                std::string(executable_path)
//            )
//        );
//   }
	dwarf::encap::pathname split_path;
	std::string::size_type pos = 0;
	do
	{
		std::string::size_type next_pos = name.find(".", pos);
		if (next_pos == std::string::npos) next_pos = name.length();
			split_path.push_back(std::string(name, pos, next_pos - pos));
		if (next_pos != std::string::npos) pos = next_pos + 1;
	} while (pos < name.length());
	
	std::vector<boost::shared_ptr<spec::with_named_children_die> > starting_points;
	// include the local lexical block in the starting points, if we have one
	// -- to decide this, walk up the stack:
	//    we will either hit an entry point (and can resolve names in its DWARF info)
	//    or hit the REPL a.k.a. evaluate() (meaning we should proceed to the toplevel CU)
	
	/* FIXME: instead of doing this stack-walking thing on each name lookup, just
	 * cache the most recent evaluate() in a thread-local var
	 * and do the walk only when exiting an evaluate() 
	 * (although that might be returning to a non-Python context ... hmm).
	 * So maybe populate the thread-local on each evaluate()?  But then it
	 * would get clobbered by the next call. Keep a thread-local stack of them?
	 * Or just do the back-walk thing -- okay. Remember that we don't have to
	 * walk back very far -- we can stop once we exit the Python world, because
	 * we never resolve names across those boundaries (i.e. it'd be in the import list,
	 * not a stack-based scope).
	 * NOTE: this back-walking is basically recalculating the static link. Can we
	 * optimise it out completely in cases where we know we have no nested functions? */
	
	std::cerr << "Walking stack for lexical context of call site " 
		<< __builtin_return_address(1)
		<< "..." << std::endl;
	
	assert(starting_points.size() == 0);
	stack_walk_output output = { 0, 0, /* will be filled in */ &starting_points };
	self.walk_stack(0 /* unused */, lexical_name_lookup_handler, &output);
	std::cerr << "Now we have " << starting_points.size() << " starting points" << std::endl;
	shared_ptr<subprogram_die> found_lookup_frame;
	if (starting_points.size())
	{
		found_lookup_frame = 
			dynamic_pointer_cast<subprogram_die>(starting_points.at(0));
		assert(found_lookup_frame);
	}
	
	// include the toplevel CU in the starting points
	assert(dynamic_pointer_cast<spec::with_named_children_die>(
			toplevel->get_this()));
	starting_points.push_back(
		dynamic_pointer_cast<spec::with_named_children_die>(
			toplevel->get_this()
			));
	std::cerr << "Then we have " << starting_points.size() << " starting points" << std::endl;
			
	// include any imported namespaces in the starting points
	for (auto i = import_list.begin(); i != import_list.end(); i++)
	{
		try
		{
			auto cur = self.files[i->second].p_ds->toplevel()->get_first_child();
			do
			{
				boost::shared_ptr<spec::with_named_children_die> to_add
					= boost::dynamic_pointer_cast<spec::with_named_children_die>(cur);
				if (to_add) starting_points.push_back(to_add);
				cur = cur->get_next_sibling();
			} while(true); // will fail by No_entry
		}
		catch (dwarf::lib::No_entry) {}
	}
	std::cerr << "Finally we have " << starting_points.size() << " starting points" << std::endl;
	
	// do the lookup
	auto result = pmirror::resolve_first(split_path, starting_points, lookup_name_pred);
	if (!result) return Invalid; 
	else
	{
		std::cerr << "Found a die... breakpoint here please." << std::endl;

		val r; // this will be returned
		if (dynamic_pointer_cast<spec::with_static_location_die>(result))
		{
			process_image::addr_t p_obj = self.get_object_from_die(
				/* FIXME: get vaddr from ParathonContext */
				boost::dynamic_pointer_cast<spec::with_static_location_die>(result), 0);
			r = (val) { false, { i_ptr: reinterpret_cast<void*>(p_obj) }, val::TBD };
		}
		else if (dynamic_pointer_cast<spec::with_dynamic_location_die>(result))
		{
			/* Now where did we put that stack frame? */
			assert(found_lookup_frame);
			/* HACK: use caller_sp directly as the frame base, for now */
			auto found_location = dynamic_pointer_cast<spec::with_dynamic_location_die>(result);
			lib::Dwarf_Unsigned addr = found_location->calculate_addr(
				output.frame_base,
				output.ip - /*image.get_dieset_base(found_lookup_frame->get_ds())*/
					(found_lookup_frame->enclosing_compile_unit()->get_low_pc() ?
					 found_lookup_frame->enclosing_compile_unit()->get_low_pc()->addr : 0UL), /* This is our file-relative IP within the function whose frame includes the local allocation */
				/* regs = */ 0);
			
				
				
			
// 			lib::Dwarf_Unsigned addr = dwarf::lib::evaluator(
// 				/* loclist = */ *dynamic_pointer_cast<spec::with_dynamic_location_die>(result)->get_location(),
// 				/* vaddr = */ /* neds to be CU-relative! */
// 				output.ip - /*image.get_dieset_base(found_lookup_frame->get_ds())*/
// 				(found_lookup_frame->enclosing_compile_unit()->get_low_pc() ?
// 				*found_lookup_frame->enclosing_compile_unit()->get_low_pc() : 0), /* This is our file-relative IP within the function whose frame includes the local allocation */
// 				/* spec = */ spec::DEFAULT_DWARF_SPEC,
// 				/* regs = */ 0,
// 				/* optional<Dwarf_Signed> frame_base = */ output.frame_base,
// 				/* const std::stack<Dwarf_Unsigned>& initial_stack = */ std::stack<lib::Dwarf_Unsigned>()
// 			).tos();
			std::cerr << "We have calculated that variable " << name 
				<< " in frame based at " << std::hex << output.frame_base << std::dec
				<< " lies at address " << std::hex << addr << std::dec << std::endl;
			r = (val) { false, { i_ptr: reinterpret_cast<void*>(addr) }, val::TBD };
		}
		else
		{
			assert(false);
		}
	
		/* Now, if the result is of reference type, dereference it before returning. */
		if (result->get_tag() == DW_TAG_subprogram) return r;
		else
		{
			auto result_wsl = dynamic_pointer_cast<with_dynamic_location_die>(result);
			assert(result_wsl);
			if (result_wsl->get_type() &&
				(*result_wsl->get_type())->get_tag() == DW_TAG_reference_type)
			{
				void *derefed = *reinterpret_cast<void**>(r.i_ptr);
				std::cerr << "Since variable " << name 
					<< " is a reference, dereferencing " << std::hex << r.i_ptr << std::dec 
					<< " to yield resolved variable at location " << std::hex << derefed << std::dec
					<< " (word value currently : 0x" << std::hex << *(unsigned*)derefed << ")" << std::dec
					<< std::endl;
				return (val) { false, { i_ptr: derefed }, val::TBD };
			}
			else return r;
		}
	}
}

/** This version prints raw pointed-to values */
void print_value_to_stream(void *value, std::ostream& s, 
	shared_ptr<type_die> opt_descr /* = shared_ptr<type_die>() */) 
{
	static dwarf::tool::cxx_compiler compiler(std::vector<std::string>(1, "g++"));

/*	val v = { false, 
  			{ i_ptr: value }, 
  			image.discover_object_descr(reinterpret_cast<process_image::addr_t>(value),
  				opt_descr) 
			};*/
	self.update(); // HACK
	auto descr = self.discover_object_descr(
		reinterpret_cast<process_image::addr_t>(value),
		opt_descr);

	if (!descr && opt_descr) descr = opt_descr;

	if (!descr)
	{
		s << "(some value)";
	}
	else
	{
		std::cerr << "Printing value described by " << *descr << std::endl;
		/* Now we need to map DWARF types to C++ operator overloads. 
 		* HACK: use dlsym() to look for an operator<< overload 
 		*       *in the same library* that defines the data type
 		*       -- we assume that this will be well-matched. 
 		*          FIXME: this is technically unsafe. */
		
		// 0. If we are pointing at an array, iterate + recurse. 
		if (descr->get_tag() == DW_TAG_array_type)
		{
			shared_ptr<array_type_die> arr_descr = dynamic_pointer_cast<array_type_die>(descr);
			
			/* NOTE: libprocessimage should always give us
   			back an array type if the pointed-to object is a block of n>1? */
			/* Termination style! HACK: use char-or-not test. */
			if (
			((*arr_descr->get_type())->get_concrete_type())->get_tag() == DW_TAG_base_type
 			&& dynamic_pointer_cast<spec::base_type_die>((*arr_descr->get_type())->get_concrete_type())->get_encoding()
  			== DW_ATE_signed_char)
			{
				/* Assume it's null-terminated. */
				char *p = (char*) value;
				while(*p) s << *(char*)p++; 
				return;
			}
			else
			{
				/* Assume it's explicitly sized */
				assert(arr_descr->element_count()); 
				assert(arr_descr->get_type());
				assert((*arr_descr->get_type())->calculate_byte_size());
				s << "[";
				int index __attribute__((unused)) 
				 = *arr_descr->enclosing_compile_unit()->implicit_array_base();
				for (int i = 0; i < *arr_descr->element_count(); index++, i++)
				{
					print_value_to_stream((char*)value 
						+ i * *(*arr_descr->get_type())->calculate_byte_size(),
						s,
						*arr_descr->get_type());
				}
				s << "]";
				return;
			}
		}
		
		if (descr->get_tag() == DW_TAG_subprogram)
		{
			// 0.5: if we are a function...
			s << "(some function at " << std::hex << value << std::dec << ")";
			return;
		}
		
		assert(dynamic_pointer_cast<type_die>(descr));
		descr = dynamic_pointer_cast<type_die>(descr)->get_concrete_type();
		std::cerr << "Printing value described concretely by " << *descr << std::endl;
		
		/* PROBLEM with our treatment of arguments:
		 * typing them as void* confuses everything, because
		 * (quite rightly) a lot of code will want to treat them as pointers.
		 * Perhaps better: encode them as reference types with no target type.
		 * We will have to traverse such references here, but that's okay.
		 */
		
		// HACK in print functions for builtins, for now
		if (descr == p_builtin_int_type)
		{
			s << *(int*)value;
		}
		else if (descr == p_builtin_double_type)
		{
			s << *(double*)value;
		}
		else if (descr == p_builtin_char_type)
		{
			s << *(char*)value;
		}
		else if (descr == p_builtin_char_type)
		{
			s << *(char*)value;
		}
		else 
		{
			assert(dynamic_pointer_cast<type_die>(descr));
			auto type_descr = dynamic_pointer_cast<type_die>(descr);
			// 1. get a C++ concrete typename from the descr
			auto name_parts = compiler.fq_name_parts_for(type_descr->get_concrete_type());
			std::cerr << "Want a print function for ";
			for (auto i = name_parts.begin(); i != name_parts.end(); i++)
			{
				if (i != name_parts.begin()) std::cerr << " :: ";
				std::cerr << *i;
			}
			std::cerr << std::endl;
			assert(false);
		}
		
	}
}

/** This version prints immediate values, and calls around for others. */
void print_value_to_stream(val v, std::ostream& s) 
{ 
	if (v == None) { s << "None"; return; }
	if (v == Invalid) { s << "Invalid"; return; }
	if (v == NotImplemented) { s << "NotImplemented"; return; }
	if (v.is_immediate)
	{
		//if (v.descr == p_builtin_int_type)
		//{ s << v.i_int; }
		//else if (v.descr == p_builtin_double_type)
		//{ s << v.i_double; }
		//else assert(false);
		///*{ s << "(some value)"; }*/
		if (v.kind == val::INT)
		{ s << v.i_int; }
		else if (v.kind == val::DOUBLE)
		{ s << v.i_double; }
		else assert(false);
		/*{ s << "(some value)"; }*/
	}
	else 
	{
		return print_value_to_stream(v.i_ptr, s, 
			(v.kind == val::CHAR_PTR) ? p_builtin_const_char_array_type
  		: 
		/*dynamic_pointer_cast*/shared_ptr<type_die>(/*v.descr*/));
	}
}

std::ostream& operator<<(std::ostream& s, const val& v)
{
	print_value_to_stream(v, s);
	return s;
}

int interpret(Statement *statement) //, encap::subprogram_die *subp, va_list ap, short *sizes)
{
	std::cerr << "Received a call from a generated entry point!" << std::endl;
	
	/* Let's thread some arguments to this function: 
 	* - the AST being interpreted;
 	* - pointer to the Dwarf information we created for the function; 
 	* - va_list for the arguments;
 	* - ptr to a blob encoding sizes for each argument; */
	
	// PROBLEM: the va_list is supposed to span *all* the caller-passed arguments.
	// Can't use the initial break pointer because that includes the caller's locals.
	// We need to finesse this in the generated assembly code, using knowledge
	// of the entry point's arguments, i.e. its Dwarf info, to get a va_list
	// pointing at the *first* argument. 
	
	/* It might be useful to stuff a custom attribute into the function definition.
 	* DW_AT_DWARFPY_interpreted_data -- an address pointing to interpreted data, and
 	* DW_AT_DWARFPY_interpreter -- udata describing an enumeration? 
 	* BUT this is not necessary: we want just to use generic Dwarf and Dwarf extensions
 	* to implement the interpreter. We will need to do something for the line numbers.  */
	
	// debugger features to demonstrate:
	// backtrace
	// line numbers (source listing)
	// state inspection
	// breakpoints (at a particular line number => conditional)
	//  ^-- hints that we might want a single evaluate() function, to break on
	//      -- can then make the evaluate() function nonvirtual
	//         ... don't use typeid for switch() statement, just use an enum threaded to base?
	
}

val call_function(val function, std::vector<val> *params)
{
	//assert(function.descr->get_tag() == DW_TAG_subprogram);
	shared_ptr<spec::with_static_location_die> discovered 
	 = self.discover_object((process_image::addr_t)function.i_ptr, 0);
	assert(discovered && discovered->get_tag() == DW_TAG_subprogram);
	shared_ptr<subprogram_die> subp = dynamic_pointer_cast<subprogram_die>(discovered);
	
	/* use alloca() to allocate these variable-length structures, for speed */
	int argcount = 0; 
	for (auto i_child = subp->formal_parameter_children_begin(); 
			i_child != subp->formal_parameter_children_end();
			i_child++) argcount++;
	ffi_type **ffi_type_buf = (ffi_type **) alloca(argcount * sizeof (ffi_type *)
											+ argcount * sizeof (void *)
											// FIXME: ^^^ doesn't work for non-wordsize args
											+ argcount * sizeof (val)
											// ^^^ to hold reference temporaries
											);
	void **ffi_arg_buf = (void **) (ffi_type_buf + argcount);
	val *reference_temporaries_buf = (val*) (ffi_arg_buf + argcount);

	int i_arg_type = 0;
	for (auto i_fp = subp->formal_parameter_children_begin(); 
			i_fp != subp->formal_parameter_children_end();
			i_fp++, i_arg_type++)
	{
		std::cerr << "getting ffi type for argument " << *i_fp 
		 << " which " << ((*i_fp)->get_type() ? "does" : "does not" )
		 << " have a type." << std::endl;
		ffi_type_buf[i_arg_type] = ffi_type_for_concrete_dwarf_type(
							(*i_fp)->get_type() ? 
							(*(*i_fp)->get_type())->get_concrete_type() 
							: shared_ptr<type_die>());
	}
	
	auto i_param = params->begin();
	int i_arg_val = 0;
	for (auto i_fp = subp->formal_parameter_children_begin(); 
			i_fp != subp->formal_parameter_children_end();
			i_fp++, i_arg_val++, i_param++)
	{
		assert(i_param != params->end());
		/* FIXME: we have to coerce parameters here because the called function 
		 * might bring type constraints.
		 * BUT is this the right place to do this? e.g. if we are evaluating
		 * fac(2) and fac takes a reference, who is responsible for indirecting
		 * the "2" to a pointer-to-2? It could be us, or it could be the argument
		 * evaluation code, or it could be FunctionCall::evaluate() code. It's not
		 * the argument evaluation code because it has no knowledge of the function.
		 * It doesn't really matter whether it goes in FunctionCall::evaluate() or
		 * here. Let's put it here. */
		 
		/* PROBLEM: val is ambiguous when our actual value (e.g. the argument we're passing)
		 * is a pointer. Do we set immediate? I'd say no. 
		 * NOTE: this means ValueString is broken! It creates a pointer-to-char
		 * as (val) { false, { i_ptr: s }, val::CHAR_PTR }; 
		 * i.e. as a ^^ *NON*-immediate pointer. */
		
		/* PROBLEM: What if it's ambiguous whether we need to pass the val or the
		 * address? 
		 * SOLUTION: Decree that if we're passing a reference , we *will* take the
		 * address of the object denoted by the val
		 * (i.e. i_ptr if the val is non-immediate, or
		 *      &i_int if the val is immediate) 
		 * and pass that. Passing that means pointing ffi_arg_buf[i_arg_val] at this address.
		 * creating a buffer */
		
		/* Here we're really coding an "address of" function. */
		// address_of(val *reference_temporary);
		
		if ((*i_fp)->get_type() && (*(*i_fp)->get_type())->get_concrete_type()
			&& (*(*i_fp)->get_type())->get_concrete_type()->get_tag() == DW_TAG_reference_type)
		{
			/* "reference" behaviour -- pass the address of the object denoted by val,
			 * meaning we need to be able to take the address of that address. */
			reference_temporaries_buf[i_arg_val] 
			= (val) { true, { i_ptr: raw_address_of_val(*i_param, 0) }, val::OTHER_PTR };
			ffi_arg_buf[i_arg_val] = raw_address_of_val(reference_temporaries_buf[i_arg_val], 0);
		}
		else
		{
			/* "normal" behaviour */
			ffi_arg_buf[i_arg_val] = i_param->is_immediate ? (void *) &i_param->i_int : i_param->i_ptr;
			// note that this work for double too because ^ this is a union
			// FIXME: this is broken for doubles or non-32bit ints!
		}
		
	}
	
	// FIXME: assume the return value from foo() is smaller than sizeof(long), it
	// must be passed as ffi_arg or ffi_sarg. FIND OUT what must happen when
	// return value is not so small!
	// v-- here assert that the return value has size < sizeof long
	assert(!subp->get_type() || ( (*subp->get_type())->calculate_byte_size() 
							&&  *(*subp->get_type())->calculate_byte_size() <= sizeof (long))); 
	ffi_arg result;
	ffi_type *result_type = ffi_type_for_concrete_dwarf_type(
								subp->get_type() ? 
									(*subp->get_type())->get_concrete_type()
								: shared_ptr<type_die>());

	ffi_status status;
	ffi_cif cif;
	// Prepare the ffi_cif structure.
	if ((status = ffi_prep_cif(&cif, FFI_DEFAULT_ABI,
			argcount, result_type, ffi_type_buf)) != FFI_OK)
	{
		// Handle the ffi_status error.
		assert(false);
	}

	// Invoke the function.
	std::cerr << "FFI-calling function at " << function.i_ptr
		<< " with arguments (";
	for (int i = 0; i < argcount; i++)
	{
		if (i != 0) std::cerr << ", ";
		std::cerr << (params->at(i).is_immediate ? 
			params->at(i).i_int 
		: 	*(reinterpret_cast<int*>(params->at(i).i_ptr)))
		<< "[in ffi_arg buf at " << &ffi_arg_buf[i] 
		<< ", pointing to " << ffi_arg_buf[i] 
		<< ", word value " << *(int*)ffi_arg_buf[i] 
		<< "]";
	}
	std::cerr << ")" << std::endl;
	
	ffi_call(&cif, FFI_FN(function.i_ptr), &result, ffi_arg_buf);

	// The ffi_arg 'result' now contains the unsigned char returned from foo(),
	// which can be accessed by a typecast.
	//printf("result is %hhu", (unsigned char)result);
	val result_val; 
	if (result_type == &ffi_type_void)
	{
		result_val = None;
	}
	else if (result_type == &ffi_type_sint8)
	{
		result_val = (val) { true, { i_int: (int) (int8_t) result }, val::INT };
	}
	else if (result_type == &ffi_type_uint8)
	{
		result_val = (val) { true, { i_int: (int) (uint8_t) result }, val::INT };
	}
	else if (result_type == &ffi_type_sint16)
	{
		result_val = (val) { true, { i_int: (int) (int16_t) result }, val::INT };
	}
	else if (result_type == &ffi_type_uint16)
	{
		result_val = (val) { true, { i_int: (int) (uint16_t) result }, val::INT };
	}
	else if (result_type == &ffi_type_sint32)
	{
		result_val = (val) { true, { i_int: (int) (int32_t) result }, val::INT };
	}
	else if (result_type == &ffi_type_float)
	{
		result_val = (val) { true, { i_double: (double) (float) result }, val::DOUBLE };
	}
	else if (result_type == &ffi_type_double)
	{
		result_val = (val) { true, { i_double: (double) result }, val::DOUBLE };
	}
	else if (result_type == &ffi_type_pointer)
	{
		auto result_pointer_type = 
			dynamic_pointer_cast<pointer_type_die>(
				(*subp->get_type())->get_concrete_type()); // a pointer type...
		auto opt_result_pointed_to_type = result_pointer_type->get_type();
		result_val = (val) { false, { i_ptr: (void *) result }, val::TBD };
		// opt_result_pointed_to_type ? 
		//   val::TBD
		// : shared_ptr<basic_die>() };
	}
	else
	{
		/* some result type that we don't know how to encode */
		assert(false);
	}

	// the vector was alloc'd for our sole benefit, so destroy it now
	delete params; // FIXME: would be faster to avoid the heap allocation here
	
	return result_val;
}

void assign_to(val loc, val v)
{
	assert(!loc.is_immediate);
	assert(false);
}
