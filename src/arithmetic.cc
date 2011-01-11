#include "ast.h"
#include "parathon.h"
#include "ops.h"
#include <cmath>
#include <cfenv>

val ArithExpression::evaluate()
{
	/** Somehow we need to dispatch to the correct operator implementation */
    return None; //parathon_call(this->op->opname(), this->lhs->evaluate(), this->rhs->evaluate());
}
val XorExpression::evaluate()
{
    return None; //parathon_call("__xor__", this->lhs->evaluate(), this->rhs->evaluate());
}
val UnaryPhrase::evaluate()
{
    return None; //parathon_call(this->op->opname(), this->rhs->evaluate());
}
val AndExpression::evaluate()
{
    val x = this->lhs->evaluate();
    if (is_true(x))
    {
        //return lookup_and_call(x, "__and__", this->rhs->evaluate());
        std::cerr << "FIXME: AND expression not implemented."  << std::endl;
        //return lookup_and_call(x, "__and__", this->rhs->evaluate());
    }
    return None;
}
static int naive_builtin_cmp(val lhs, val rhs);
static int naive_builtin_cmp(val lhs, val rhs)
{
	val lhs_norm = normalize_val(lhs);
	val rhs_norm = normalize_val(rhs);
#define KINDS(lk, rk) (((uint64_t) (lk) << 32) + ((uint64_t)(rk)))
	switch (KINDS(lhs_norm.kind, rhs_norm.kind))
	{
		case KINDS(val::INT, val::INT):
			return lhs_norm.i_int - rhs_norm.i_int;
		case KINDS(val::DOUBLE, val::INT): {
			/* We have to return an integer, and it should only be zero
			 * if we have equality. So set the rounding direction to
			 * "away from zero". */
			int tmp = fegetround();
			int ret;
			double difference = lhs_norm.i_double - rhs_norm.i_int;
			if (difference < 0) fesetround(3); // "towards negative infinity"
			else fesetround(2); // "towards positive infinity"
			ret = nearbyint(difference);
			fesetround(tmp);
			return ret;
			}
		case KINDS(val::INT, val::DOUBLE): {
			/* Same again. */
			int tmp = fegetround();
			int ret;
			double difference = lhs_norm.i_int - rhs_norm.i_double;
			if (difference < 0) fesetround(3); // "towards negative infinity"
			else fesetround(2); // "towards positive infinity"
			ret = nearbyint(difference);
			fesetround(tmp);
			return ret;
			}
		case KINDS(val::DOUBLE, val::DOUBLE): {
			/* Same again */
			int tmp = fegetround();
			int ret;
			double difference = lhs_norm.i_double - rhs_norm.i_double;
			if (difference < 0) fesetround(3); // "towards negative infinity"
			else fesetround(2); // "towards positive infinity"
			ret = nearbyint(difference);
			fesetround(tmp);
			return ret;
			}
		default: // we hope this means that at least one is a pointer
			// -- this means we use address comparison.
			// HACK: to behave like CPython, we *should* define addresses for 
			// singleton "integer objects" (like "the 2 object")
			// BUT we cheat and just use i_ptr, &i_int, &i_double
			return ((lhs.is_immediate ? (void*)&lhs.i_int : lhs.i_ptr)
				<  (rhs.is_immediate ? (void*)&rhs.i_int : rhs.i_ptr))
			? -1
			: (((lhs.is_immediate ? (void*)&lhs.i_int : lhs.i_ptr)
				>  (rhs.is_immediate ? (void*)&rhs.i_int : rhs.i_ptr)) 
			? 1
			: 0);
	}
#undef KINDS

}

bool ComparisonOperator::compare(val lhs, val rhs)
{
	// FIXME: support rich comparison

	/* Here's how it worked in Parathon: 
	//ParathonValue* cmp = BUILTIN__getattr__(&ParathonValue::builtins)(lhs, "__cmp__");
	//if (cmp)
	//    return this->compare(*(parathon_int*)cmp->call(rhs)->value);
	 * #define BUILTIN__getattr__(c) 
	 *      (*(ParathonValue *(**)(ParathonValue *, char *))((c)->lookup("__getattr__")->value))
	 * i.e. lookup "__getattr__" in c, get its "value" field
	 * and cast it to a pointer to a pointer to a function: (ParathonValue*, char*) => ParathonValue*
	 * then dereference that (i.e. get the function pointer itself).
	 *
	 * So we are recovering a getattr function from ParathonValue::builtins
	 * Then applying it to (lhs, "__cmp__")
	 * i.e. looking for a __cmp__ function in the object.
	 * If we get one, we call it on rhs, yielding a value
	 *   from Python spec again:
	 *     Should return a negative integer if self < other, 
	                     zero if self == other, 
	                     a positive integer if self > other. 
	 *     If no __cmp__(), __eq__() or __ne__() operation is defined, 
	 *     class instances are compared by object identity (``address''). 
	 * then call this->compare on the *output*
	 * - this distils the result down to a boolean reflecting the
	 *   specific comparison being done
	 */
	
	// FIXME: don't check for __cmp__ for now, just partition into
	// number or object and do two simple comparison implementations
	return this->compare(naive_builtin_cmp(lhs, rhs));
}
