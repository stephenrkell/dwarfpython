//#include "die_wrapper.hh"
#include "parathon.h"
#include "ast.h"
#include "float.h"
#include <sstream>
;
// FIXME - this file is becoming a mess rapidly!
die_wrapper::die_wrapper(dwarf::encap::dieset* ds, unsigned long start, unsigned long offset)
{
    this->dieset = ds;
    this->start = start;
    this->offset = offset;
    this->filled_children = 0;
}

void die_wrapper::print()
{
    std::cout << *this->die() << std::endl;
}

FILE * fil_builtins = NULL;
static dwarf::encap::dieset *ds_builtins = NULL;
die_wrapper *die_wrapper::builtin(string name)
{
    if (! ds_builtins)
    {
        fil_builtins = fopen("./runtime/libbuiltin_types.so", "r");
        if (!fil_builtins)
        {
            std::cerr << "Could not open libbuiltin_types.so :(" << std::endl;
            return NULL;
        }

        ds_builtins = &(new dwarf::encap::file(fileno(fil_builtins)))->ds();
    }

    return new die_wrapper(ds_builtins, name.c_str());
}

die_wrapper* die_wrapper::for_closure()
{
    if (!this) // Some of the inbuilt properties that don't have C types call this with NULL
        return NULL; // should have used vanilla C, then this problem wouldn't exist :D

    if (!this->isFunction())
        return NULL;

    if (!this->child_length())
        return NULL;

    die_wrapper *ret = new die_wrapper(*this);
    ret->filled_children += 1;
    return ret;
}

void die_wrap(die_wrapper* die, dwarf::encap::dieset* dsp, const char* sym)
{
    die->filled_children = 0;
    dwarf::encap::dieset& ds = *dsp;
    std::string asym = "__";
    asym += sym;

    for (dwarf::encap::die_off_list::iterator start = ds[0UL].children().begin();
            start < ds[0UL].children().end(); start++)
    {
        for (dwarf::encap::die_off_list::iterator i = ds[*start].children().begin();
                i < ds[*start].children().end(); i++)
        {
            const dwarf::encap::attribute_value& val = ds[*i][DW_AT_name];
            if (val == dwarf::encap::attribute_value::DOES_NOT_EXIST())
                continue;
            string name = val.get_string();
            if (name == sym)
            {
                die->dieset = &ds;
                die->start = *start;
                die->offset = *i;
                return;
            }
            else if (name == asym)
            {
                die->dieset = &ds;
                die->start = *start;
                die->offset = *i;
                return;
            }
        }
    }
    throw ParathonException("Could not find '", sym, "' in library.");
}
die_wrapper::die_wrapper(dwarf::encap::dieset* ds, const char * sym)
{
    die_wrap(this, ds, sym);
}
die_wrapper::die_wrapper(die_wrapper* die, const char * sym)
{
    die_wrap(this, die->dieset, sym);
}
die_wrapper::die_wrapper(dwarf::encap::dieset* ds, unsigned long start, dwarf::encap::die* die)
{
    this->dieset = ds;
    this->start = start;
    this->offset = die->offset();
    this->filled_children = 0;
}
bool die_wrapper::isFunction()
{
    if (!this)
        return false;

    if (die()->get_tag() == DW_TAG_subprogram)
    {
        return true;
    }
    if (die()->get_tag() == DW_TAG_variable)
    {
        die_wrapper* die = this->type_die();
        while(die && die->die()->get_tag() == DW_TAG_pointer_type)
        {
            die = die->type_die();
        }
        if (die->die()->get_tag() == DW_TAG_subroutine_type)
        {
            return true;
        }
    }
    return false;
}
bool die_wrapper::isParathonValue()
{
    dwarf::encap::die* die = &(*this->dieset)[this->offset];

    // Won't loop infinitely
    // case 1 and 3 return,
    // case 2 follows reference, dwarf is a tree not a graph => no cycles
    //       => eventually reference cannot be followed => case 1 or 3
    while(true)
    {
        if ((*die)[DW_AT_name] == "ParathonValue")
        {
            return true;
        }
        else if ((die->get_tag() == DW_TAG_pointer_type ||
                  die->get_tag() == DW_TAG_formal_parameter ) && 
            (*die)[DW_AT_type] != dwarf::encap::attribute_value::DOES_NOT_EXIST())
        {
            die = &((*this->dieset)[(*die)[DW_AT_type].get_ref().off + this->start - 11]);
        }
        else
        {
            return false;
        }
    }
}
bool die_wrapper::isSameType(die_wrapper* other)
{
    return (this == other) ||
           (this && other &&
            this->offset == other->offset &&
            this->dieset == other->dieset &&
            this->start  == other->start  &&
            this->filled_children == other->filled_children) ||
           (this->as_ffi() == other->as_ffi());
    // FIXME: this fails for pointers to structs
}
bool die_wrapper::isPointerTo(die_wrapper* other)
{
    if (this && this->die()->get_tag() == DW_TAG_pointer_type)
        return other->isSameType(this->type_die());
    return false;

}
bool die_wrapper::realCastTo(void ** value, die_wrapper* type, void ** result, bool create)
{

    if(!this)
        return false;

    unsigned this_size, that_size, this_encoding, that_encoding;
    switch(die()->get_tag())
    {
        case DW_TAG_formal_parameter:
        case DW_TAG_typedef:
            return this->type_die()->castTo(value, type, result);
        case DW_TAG_base_type:
            switch(type->die()->get_tag())
            {
                case DW_TAG_formal_parameter:
                case DW_TAG_typedef:
                    return this->castTo(value, type->type_die(), result);
                case DW_TAG_base_type:

                    this_size = (*this->die())[DW_AT_byte_size].get_unsigned();
                    that_size = (*type->die())[DW_AT_byte_size].get_unsigned();
                    this_encoding = (*this->die())[DW_AT_encoding].get_unsigned();
                    that_encoding = (*type->die())[DW_AT_encoding].get_unsigned();

//                    std::cout << this_size << ":" << that_size << "#" << this_encoding << ":" << that_encoding << std::endl;
                    // Can hope to cram ints into spaces
                    if (    (this_size == that_size && this_encoding == that_encoding) || 
                            (this_size <= that_size && this_encoding == that_encoding && (this_encoding == 7 || this_encoding == 5))
                            || (this_size < that_size && this_encoding == 7 && that_encoding == 5) ) {

                        if (create) {
                            *result = calloc(1, that_size);
                            if (value != NULL)
                                memcpy(*result, value, this_size);
                            return true;
                        } 
                    } else if ( (this_encoding == 7 || this_encoding == 5) && (that_encoding == 7 || that_encoding == 5) ) {
                        unsigned int this_needs = value == NULL ? 0 : this_size;

                        while (this_needs > 1 && (((char*)value)[this_needs] == '\0') && ((((char*)value)[this_needs - 1] & 0x40) == 0) )
                            this_needs -= 1;

                        if (this_needs <= that_size)
                        {
                                *result = calloc(1, this_size);
                                memcpy(*result, value, this_needs);
                                return true;
                        }
                        return false;
                        // Floating point
                    } else if (this_encoding == 4 && that_encoding == 4) {

                        *result = calloc(1, that_size);
                        if (that_size == 12) 
                        {
                            if (this_size == 8) 
                            {
                                *(long double*)result = *(double*) value;
                                return true;
                            }
                            else if (this_size == 4)
                            {
                                *(long double*) result = *(float*) value;
                                return true;
                            }
                        }
                        else if (that_size == 8)
                        {
                            if (this_size == 12 && *(long double*)value <= DBL_MAX)
                            {
                                *(double*)result = *(long double*) value;
                                return true;
                            }
                            else if (this_size == 4)
                            {
                                *(double*) result = *(float*) value;
                                return true;
                            }
                        }
                        else if (that_size == 4)
                        {
                            if (this_size == 12 && *(long double*)value <= FLT_MAX)
                            {
                                *(float*) result = *(long double*) value;
                                return true;
                            }
                            else if (this_size == 8 && *(double*) value <= FLT_MAX)
                            {
                                *(float*)result = *(double*) value;
                                return true;
                            }
                        }
                        return false;
                    }
                default:
                    return false;
            }
        case DW_TAG_pointer_type:
            switch(type->die()->get_tag())
            {
                case DW_TAG_subroutine_type:
                    *result = malloc(sizeof(void*));
                    return this->type_die()->castTo(value, type,  *(void ***)result);

                case DW_TAG_typedef:
                    return this->castTo(value, type->type_die(), result);

                case DW_TAG_pointer_type:
                    if (this->type_die()->castTo(value, type->type_die(), result))
                    {
                        if (create)
                            memcpy(*result, value, sizeof(void*));
                        else
                            memcpy(result, value, sizeof(void*));
                        return true;
                    }

                case DW_TAG_base_type:
                default:
                    return false;
            }
        case DW_TAG_subroutine_type:
        case DW_TAG_subprogram:
            switch(type->die()->get_tag())
            {
                case DW_TAG_subroutine_type:
                    *result = malloc(sizeof(void*));
                    memcpy(*result, value, sizeof(void*));
                case DW_TAG_subprogram:
                    *result = malloc(sizeof(void*));
                    memcpy(*result, value, sizeof(void*));
                default:
                    return false;
            }
        default:
            return false;
    }

}
ParathonValue* die_wrapper::lookupField(void ** value, const char * str)
{
    switch(this->die()->get_tag())
    {
        case DW_TAG_pointer_type:
        case DW_TAG_typedef:
            return this->type_die()->lookupField(value, str);

        case DW_TAG_structure_type:
            for (unsigned i = 0; i < this->child_length(); i++)
            {
                const dwarf::encap::attribute_value& at((*(this->child(i)->die()))[DW_AT_name]);
                if (at == dwarf::encap::attribute_value::DOES_NOT_EXIST() ) {
                    std::cout << "does not exist" << this->child_length() << std::endl;
                    return NULL;

                }
                else if (at.get_string() == str) {
                    return ParathonValue::getValue( (*(void***)value)[i] , this->child(i)->type_die());
                }
            }

        default:
            return NULL;
    }
}

bool die_wrapper::assignField(void **value, const char * str, ParathonValue *assignee)
{
    switch(this->die()->get_tag())
    {
        case DW_TAG_pointer_type:
            return this->type_die()->assignField(value, str, assignee);
        case DW_TAG_typedef:
            return this->type_die()->assignField(value, str, assignee);

        case DW_TAG_structure_type:
            for (unsigned i = 0; i < this->child_length(); i++)
            {
                if ((*(this->child(i)->die()))[DW_AT_name].get_string() == str) {
                    std::cout << "KLASJDKLJA" << std::endl;
                    return assignee->die->realCastTo((void**)&assignee->value, this->child(i)->type_die(), &(*(void***)value)[i], false); 
                }
            }

        default:
            return false;
    }
    return false;
}
std::string typeString(dwarf::encap::dieset& ds, const unsigned long start, const unsigned long offset)
{

    dwarf::encap::attribute_value type = ds[offset][DW_AT_type];
    if (type == dwarf::encap::attribute_value::DOES_NOT_EXIST())
    {
        std::ostringstream out;
        out << ds[offset];
       // return out.str();
        return "void";
    }

    /**
     * start is the beginning of the compilation unit.
     * type.get_ref().off is the nonglobal offset within the compilation unit.
     * 11 is a magic number that I found in the dwarfdump output...
     * Possibly something to do with header size of the compliation unit? dunno
     */

    dwarf::encap::die type_die = ds[start + type.get_ref().off - 11];

    switch(type_die.get_tag())
    {
        case DW_TAG_pointer_type:
            return typeString(ds, start, type_die.get_offset()) + "*";

        case DW_TAG_reference_type:
            return typeString(ds, start, type_die.get_offset()) + "&";

        case DW_TAG_const_type:
            return "const " + typeString(ds, start, type_die.get_offset());

        case DW_TAG_volatile_type:
            return "volatile " + typeString(ds, start, type_die.get_offset());

        case DW_TAG_structure_type:
            return "struct " + type_die[DW_AT_name].get_string();

        case DW_TAG_subroutine_type:
            return "( ) ->" + typeString(ds, start, type_die.get_offset());

        case DW_TAG_class_type:
            if (type_die[DW_AT_name] != dwarf::encap::attribute_value::DOES_NOT_EXIST())
                return type_die[DW_AT_name].get_string();
            else if(type_die[DW_AT_specification] != dwarf::encap::attribute_value::DOES_NOT_EXIST())
            {
                std::ostringstream out;
                out << ds[type_die[DW_AT_specification].get_ref().off + start - 11][DW_AT_name].get_string();
                return out.str();
            }
            else
            {
                std::ostringstream out;
                out << type_die;
                return out.str();
            }
        case DW_TAG_enumeration_type:
        case DW_TAG_typedef:
        case DW_TAG_base_type:
            return type_die[DW_AT_name].get_string();

        default:

            std::ostringstream out;
            out << type_die;
            return out.str();
    }

}
char * die_wrapper::tostr()
{
    if (!this)
        return (char*)"void";
    if (this->isFunction())
    {
        std::stringstream ss;
        ss << typeString(*this->dieset, this->start, this->offset);
        ss << " ";
        ss << string((*this->die())[DW_AT_name].get_string());
        ss << "(";
        string sep = "";
        for (unsigned i=0; i<this->child_length(); i++)
        {
            ss << sep << this->child(i)->tostr();
            sep = ", ";
        }
        ss << ")";
        string * s = new string(ss.str());
        return (char*)s->c_str();
    }
    else
    {
        return (char*)typeString(*this->dieset, this->start, this->offset).c_str();
    }
}
void die_wrapper::toStream(void* value, std::ostream& strm)
{
    if (!this)
    {
        strm << (char*)"void";
        return;
    }

    if (this->isFunction())
    {
        strm << this->tostr();
    }

    dwarf::encap::dieset ds = *this->dieset;

    switch(die()->get_tag())
    {
        case DW_TAG_typedef:
            strm << (*die())[DW_AT_name].get_string();
            this->type_die()->toStream(value, strm);
            break;

        case DW_TAG_pointer_type:
            this->type_die()->toStream(*(void**)value, strm);
            break;

        case DW_TAG_structure_type:
            strm << "{" << std::endl;
            for (unsigned i = 0; i < this->child_length(); i++)
            {
                strm << (*(this->child(i)->die()))[DW_AT_name].get_string() << ": ";
                ParathonValue::getValue( ((void**)value)[i] , this->child(i)->type_die())->toStream(strm);
            }
            strm << "}" << std::endl;
            break;

        default:
            this->print();
    }

}

bool die_wrapper::castTo(void ** value, die_wrapper* type, void ** result)
{
    return this->realCastTo(value, type, result, true);
}
unsigned int die_wrapper::child_length()
{
    unsigned count = 0;
    dwarf::encap::die_off_list children = (*this->dieset)[this->offset].children();

    for( dwarf::encap::die_off_list::iterator i = children.begin();
            i < children.end(); i++)
    {
        if ((*this->dieset)[*i].get_tag() == DW_TAG_formal_parameter || (*this->dieset)[*i].get_tag() == DW_TAG_member)
            count++;
    }
    return count - this->filled_children;
}
die_wrapper *die_wrapper::child(int index)
{
    return new die_wrapper(this->dieset, this->start, (*this->dieset)[this->offset].children()[index + this->filled_children]);
}

die_wrapper *die_wrapper::bound_type()
{
    return this->child(-1);
}

ffi_type ** die_wrapper::ffi_args()
{
    ffi_type ** args = (ffi_type**)malloc(sizeof(ffi_type *) *this->child_length());
    for (unsigned i = 0; i < this->child_length(); i++)
    {
        args[i] = this->child(i)->as_ffi();
    }
    return args;
}

ffi_type *die_wrapper::get_ffi_type(dwarf::encap::die* die)
{
    switch(die->get_tag())
    {
        case DW_TAG_pointer_type:
            return &ffi_type_pointer;
        case DW_TAG_const_type:
        case DW_TAG_volatile_type:
            return this->get_ffi_type(&(*this->dieset)[(*die)[DW_AT_type].get_ref().off + this->start - 11]);
        case DW_TAG_typedef:
            return this->get_ffi_type(&(*this->dieset)[(*die)[DW_AT_type].get_ref().off + this->start - 11]);
        case DW_TAG_base_type:
                switch((*die)[DW_AT_byte_size].get_unsigned() * 10 + (*die)[DW_AT_encoding].get_unsigned())
                {
                    case 124:
                        return &ffi_type_longdouble;
                    case 88:
                    case 87:
                        return &ffi_type_uint64;
                    case 86:
                    case 85:
                        return &ffi_type_sint64;
                    case 84:
                        return &ffi_type_double;

                    case 48:
                    case 47:
                        return &ffi_type_uint32;
                    case 46:
                    case 45:
                        return &ffi_type_sint32;
                    case 44:
                        return &ffi_type_float;

                    case 28:
                    case 27:
                        return &ffi_type_uint16;
                    case 26:
                    case 25:
                        return &ffi_type_sint16;

                    case 18:
                        return &ffi_type_uchar;
                    case 17:
                        return &ffi_type_uint8;
                    case 16:
                        return &ffi_type_schar;
                    case 15:
                        return &ffi_type_sint8;

                    default:
                        std::cout << (*die)[DW_AT_byte_size].get_unsigned() * 10 + (*die)[DW_AT_encoding].get_unsigned() << std::endl;
                        throw ParathonException("Unknown base type");
                }
        default:
            std::cout << "RARRRRRRRRRRRRRRRRRRV" << std::endl;
            return NULL;
    }
}

ffi_type * die_wrapper::ffi_return()
{
    dwarf::encap::die* die = &(*this->dieset)[this->offset];
    if ((*die)[DW_AT_type] == dwarf::encap::attribute_value::DOES_NOT_EXIST())
    {
        return &ffi_type_void;
    }
    else
    {
        return this->get_ffi_type(&(*this->dieset)[(*die)[DW_AT_type].get_ref().off + this->start - 11]);
    }
}

die_wrapper *die_wrapper::return_type()
{
    if (!this->isFunction())
        throw ParathonException("Tried to get return type of non-function");
    return this->type_die();
}
die_wrapper *die_wrapper::type_die()
{
    if ((*this->die())[DW_AT_type] == dwarf::encap::attribute_value::DOES_NOT_EXIST())
        return die_wrapper::builtin("void");
    else
        return new die_wrapper(this->dieset, this->start, &(*this->dieset)[(*this->die())[DW_AT_type].get_ref().off + this->start - 11]);
}

ffi_type * die_wrapper::as_ffi()
{
    if (!this)
    {
        return &ffi_type_pointer;
    }
    dwarf::encap::die* die = &(*this->dieset)[this->offset];

    // Not infinite on the condition that each case either returns or moves die down the tree
    while(true)
    {
        switch(die->get_tag())
        {
            case DW_TAG_pointer_type:
            case DW_TAG_subprogram:
                return &ffi_type_pointer;

            case DW_TAG_formal_parameter:
            case DW_TAG_typedef:
                if ((*die)[DW_AT_type] == dwarf::encap::attribute_value::DOES_NOT_EXIST())
                {
                    return &ffi_type_void;
                }
                die = &(*this->dieset)[(*die)[DW_AT_type].get_ref().off + this->start - 11];
                break;

            case DW_TAG_base_type:

                switch((*die)[DW_AT_byte_size].get_unsigned() * 10 + (*die)[DW_AT_encoding].get_unsigned())
                {
                    case 88:
                    case 87:
                        return &ffi_type_uint64;
                    case 86:
                    case 85:
                        return &ffi_type_sint64;
                    case 84:
                        return &ffi_type_double;

                    case 48:
                    case 47:
                        return &ffi_type_uint32;
                    case 46:
                    case 45:
                        return &ffi_type_sint32;
                    case 44:
                        return &ffi_type_float;

                    case 28:
                    case 27:
                        return &ffi_type_uint16;
                    case 26:
                    case 25:
                        return &ffi_type_sint16;

                    case 18:
                        return &ffi_type_uchar;
                    case 17:
                        return &ffi_type_uint8;
                    case 16:
                        return &ffi_type_schar;
                    case 15:
                        return &ffi_type_sint8;

                    default:
                        std::cout << (*die)[DW_AT_byte_size].get_unsigned() * 10 + (*die)[DW_AT_encoding].get_unsigned() << std::endl;
                        throw ParathonException("Unknown base type");
                }
            case 0:
                throw ParathonException("Unknown type...");

            default:
                throw ParathonException("Could not find ffi_type");
        }
    }
}

dwarf::encap::die * die_wrapper::die()
{
    return &(*this->dieset)[this->offset];
}
