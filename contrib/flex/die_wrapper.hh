#ifndef DIE_WRAPPER_H
#define DIE_WRAPPER_H
#include "dwarfpp/encap.hpp"
#include "closures.hh"
#include "parathon.h"

class die_wrapper
{
    public:
        die_wrapper(dwarf::encap::dieset* ds, unsigned long start, unsigned long offset);
        die_wrapper(die_wrapper* die, const char* sym);
        die_wrapper(dwarf::encap::dieset* ds, const char* sym);
        die_wrapper(dwarf::encap::dieset* ds, unsigned long start, dwarf::encap::die* sym);

        dwarf::encap::dieset* dieset;
        unsigned long start;
        unsigned long offset;
        unsigned long filled_children;

        bool isFunction();
        bool isParathonValue();
        bool isSameType(die_wrapper* other);
        bool isPointerTo(die_wrapper* other);

        bool castTo(void ** value, die_wrapper*,void **);
        bool realCastTo(void ** value, die_wrapper*,void **, bool);
        ParathonValue* lookupField(void **, const char *);
        bool assignField(void **, const char *, ParathonValue*);

        die_wrapper* for_closure();
        dwarf::encap::die *die();
        die_wrapper* type_die();
        char* tostr();
        void toStream(void*, std::ostream&);


        unsigned int child_length();
        die_wrapper* child(int);
        die_wrapper* bound_type();
        die_wrapper* return_type();
        ffi_type ** ffi_args();
        ffi_type * ffi_return();
        ffi_type * as_ffi();
        ffi_type * get_ffi_type(dwarf::encap::die*);

        static die_wrapper* builtin(std::string name);
        void print();

};
#endif
