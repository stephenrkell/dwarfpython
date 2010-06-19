#include "closures.hh"
#include <malloc.h>
#include <cstring>
#include "iostream"
void call_closure(ffi_cif* ocif, void *ret, void* oargs[], void* user_data)
{
    // args have all been type checked already :D

    // create new arguments list
    closure_binding * data = (closure_binding*)user_data;
    ffi_type ** arg_types = (ffi_type**)malloc(sizeof(ffi_type*) * (ocif->nargs + 1));
    void ** newargs = (void **)malloc(sizeof(void*) * (ocif->nargs + 1));
    ffi_cif newcif;

    arg_types[0] = data->bound_ffi_type;
    newargs[0] = data->bound_arg;
    memcpy(&(arg_types[1]), ocif->arg_types, sizeof(ffi_type*) * ocif->nargs);
    memcpy(&(newargs[1]), oargs, sizeof(void *) * ocif->nargs);

    if (ffi_prep_cif(&newcif, ocif->abi, ocif->nargs+1, ocif->rtype, arg_types) == FFI_OK)
    {
        // call old function with new arguments
        ffi_call(&newcif, data->bound_function, ret, newargs);
    }
    else
    {
        std::cout << "Could not prepare closure CIF" << std::endl;
    }
}
