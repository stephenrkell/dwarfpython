#ifndef DWARFPYTHON_UTIL_H_
#define DWARFPYTHON_UTIL_H_

#include <ffi.h>
#include "parathon.h"

ffi_type *ffi_type_for_concrete_dwarf_type(shared_ptr<type_die> p_t);


#endif
