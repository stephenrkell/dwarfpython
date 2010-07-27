#include "ffi.h"
typedef struct closure_binding {
    void* bound_arg;
    ffi_type* bound_ffi_type;
    void (*bound_function)();
} closure_binding;

void call_closure(ffi_cif* ocif, void *ret, void* oargs[], void* user_data);
