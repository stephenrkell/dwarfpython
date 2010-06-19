#include <string>
#include <iostream>
#include "parathon.h"
#include "ops.h"

#include <libcake/process.hpp>

bool is_true(val value) { return false; }

process_image image(-1); // -1 means "this process"

bool lookup_name_pred(spec::basic_die& d)
{
	/* We want a DIE that has a runtime location and,
     * if it is a program_element,
     * is not just a declaration. */
    std::cerr << "Testing die with name " << (d.get_name() ? *d.get_name() : "(no name)")
    	<< std::endl;
    auto p_rtl_d = dynamic_cast<spec::with_runtime_location_die *>(&d);
    if (p_rtl_d)
    {
    	spec::program_element_die *p_prog_el = dynamic_cast<spec::program_element_die *>(&d);
    	if (!p_prog_el)
        {
        	return true;
        }
        else 
        {
        	return (!p_prog_el->declaration() || !*p_prog_el->declaration());
		}
    }
    else return false;
    	
}

val lookup_name(ParathonContext& context, const std::string& name) 
{
	/* The context records which portions of the process map namespace
     * are visible. */
     
    // HACK to test: import libcake
    if (context.import_list.size() == 0)
    {
    	context.import_list.insert(
        	std::make_pair(
            	std::string("cake"), 
                std::string("/auto/homes/srk31/work/devel/cake/libcake/libcake.so")
            )
        );
    }
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
    for (auto i = context.import_list.begin(); i != context.import_list.end(); i++)
    {
    	try
        {
	        auto cur = image.files[i->second].p_ds->toplevel()->get_first_child();
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
    auto result = resolve_first(split_path, starting_points, lookup_name_pred);
    if (!result) return Invalid; 
    else
    {
		//std::cerr << "Found a die... breakpoint here please." << std::endl;
    	//return 0;
        void *obj = get_object_from_die(/* FIXME: get vaddr from ParathonContext */
        	boost::dynamic_pointer_cast<spec::with_runtime_location_die>(result), 0);
        val r = { false, { i_ptr: obj }, result.get() };
        return r;
    }
}

void print_value_to_stream(void *value, std::ostream& s) 
{
	val v = (val) { false, { .i_ptr = value }, image.discover_object_descr(value) };
	print_value_to_stream(v, s);
}

void print_value_to_stream(val v, std::ostream& s) 
{ 
	if (v.is_immediate)
    {
    	switch (v.descr)
        {
        	case p_builtin_int_type:
            	s << val.i_int;
            	break;
            case p_builtin_double_type:
            	s << val.i_double;
            	break;
        	default:
            	s << "(some value)";
        }
    }
    else s << "(some value)"; 
}

std::ostream& operator<<(std::ostream& s, const val& v)
{
	print_value_to_stream(v, s);
    return s;
}
