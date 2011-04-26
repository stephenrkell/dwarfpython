#include "parathon.h"
#include "util.h"
#include <cassert>

ffi_type *ffi_type_for_concrete_dwarf_type(shared_ptr<type_die> p_t)
{
    if (!p_t)
    {
        /* make it an int */
        return &ffi_type_sint;
    }
    else if (p_t->get_tag() == DW_TAG_base_type)
    {
        auto p_base_type = dynamic_pointer_cast<base_type_die>(p_t);
        /* Don't support bit-offset or bit-size for now */
        assert(
            (!p_base_type->get_bit_offset() || *p_base_type->get_bit_offset() == 0)
        &&  (!p_base_type->get_bit_size() 
                || *p_base_type->get_bit_size() == 8 * *p_base_type->get_byte_size()));
#define ENC_AND_SZ(enc, sz) ((((unsigned short) (enc))<<16)|(unsigned short) (sz))
		switch (ENC_AND_SZ(p_base_type->get_encoding(),
                           *p_base_type->get_byte_size()))
        {
            case (ENC_AND_SZ(DW_ATE_signed_char, 1)): return &ffi_type_sint8;
            case (ENC_AND_SZ(DW_ATE_unsigned_char, 1)): return &ffi_type_uint8;
            case (ENC_AND_SZ(DW_ATE_signed, 1)): return &ffi_type_sint8;
            case (ENC_AND_SZ(DW_ATE_unsigned, 1)): return &ffi_type_uint8;
            case (ENC_AND_SZ(DW_ATE_signed, 2)): return &ffi_type_sint16;
            case (ENC_AND_SZ(DW_ATE_unsigned, 2)): return &ffi_type_uint16;
            case (ENC_AND_SZ(DW_ATE_signed, 4)): return &ffi_type_sint32; 
            case (ENC_AND_SZ(DW_ATE_unsigned, 4)): return &ffi_type_uint32;
            case (ENC_AND_SZ(DW_ATE_signed, 8)): return &ffi_type_sint64;
            case (ENC_AND_SZ(DW_ATE_unsigned, 8)): return &ffi_type_uint64;
            case (ENC_AND_SZ(DW_ATE_float, sizeof (float))): return &ffi_type_float;
            case (ENC_AND_SZ(DW_ATE_float, sizeof (double))): return &ffi_type_double; 
            default:  /* libffi does not support this base type! */ assert(false);
        }
#undef ENC_AND_SZ
    }
    else if (p_t->get_tag() == DW_TAG_pointer_type
			|| p_t->get_tag() == DW_TAG_reference_type)
    { 
        return &ffi_type_pointer;
    }
    else /* probably a structured type */
    {
        assert(false); // come back for this
    }
}        
