#ifndef DWARFPY_ARCHDEP_H
#define DWARFPY_ARCHDEP_H

#include <vector>
#include "parathon.h"

#ifdef __x86__
void *const MARKER_ADDRESS = reinterpret_cast<void*>(0x12345678U);
#else
#ifdef __x86_64__
void *const MARKER_ADDRESS = reinterpret_cast<void*>(0x123456789abcdef0UL);
#else
#error "Did not recognise architecture."
#endif
#endif

class FunctionDefinition; // forward decl

void
write_entry_point_and_fp_locations(
	FunctionDefinition *ast,
	shared_ptr<dwarf::encap::subprogram_die> subp, /* determines ABI */
	void *dest, /* dest */
	unsigned long sz, /* size of buffer */
	unsigned long *out_sz /* #bytes written */
);

void 
write_basic_entry_point(
	shared_ptr<dwarf::spec::subprogram_die> subp,
	unsigned registers_used, 
	void *dest, 
	size_t sz, 
	size_t *out_sz);

void 
update_fake_ast_pointer(void *dest, size_t sz, FunctionDefinition *ast);

void
write_frame_base(
	shared_ptr<dwarf::encap::subprogram_die> subp, 
	dwarf::lib::Dwarf_Addr hipc, 
	dwarf::lib::Dwarf_Addr lopc);

void 
write_fp_location_descriptions(
	shared_ptr<dwarf::encap::subprogram_die> subp, 
unsigned *registers_used);

#endif
