#ifndef DWARFPYTHON_VAL_H_
#define DWARFPYTHON_VAL_H_

/** val exists to make passing around "values" (i.e. the contents of temporary
 *  objects) easy, within the interpreter. The moment something is stored under
 *  a name, it is no longer a val but instead in some storage structure (typically
 *  raw memory, but potentially a hash table in the case of locals).  ACTUALLY we
 *  can't use a hash table unless it guarantees that bucket entries don't get moved
 *  or reallocated, because  we might want to take the address of a local and expect
 *  this to be stable. */
struct val
{
	bool is_immediate;
	/* Question: what is the difference between an immediate value
     * that is a pointer, and a non-immediate value? 
     * 
     * Answer: an immediate pointer carries the description of the
     * pointer. A non-immediate value carries the description of
     * the pointed-to object. Both may be imprecise?
     *
     * Question: do we ever need to use immediate pointers? 
     * This is not clear. ValueString used to generate them but now fixed. */
    union 
    {
        int i_int;
        double i_double;
        void *i_ptr;
    };
    //boost::shared_ptr<dwarf::spec::basic_die> descr;
    enum { NONE, INVALID, INT, DOUBLE, CHAR_PTR, OTHER_PTR, TBD } kind;
    bool operator==(const val& v) 
    { return this->is_immediate == v.is_immediate &&
         //(this->is_immediate && this->descr == p_builtin_int_type) ? 
       		(this->is_immediate && this->kind == INT) ? 
    		(this->i_int == v.i_int)
       : //(this->is_immediate && this->descr == p_builtin_double_type) ?
            (this->is_immediate && this->kind == DOUBLE) ?
    		(this->i_double == v.i_double)
       : (!this->is_immediate && this->i_ptr == v.i_ptr);
	}
    bool operator!=(const val& v) { return !(*this == v); }
};
/*extern val valInvalid;*/
extern const val& Invalid;
/*extern val valNone;*/
extern const val& None;
/*extern val valNotImplemented;*/
extern const val& NotImplemented;
/* Note: we record None as a null pointer, so its descr will be set.
 * FIXME: add a constant for this. It will need static initialization
 * in order to grab the builtin DWARF type die for a pointer-to-unspecified. */
std::ostream& operator<<(std::ostream& s, const val& v);

#endif
