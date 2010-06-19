#include <string.h>
#include <malloc.h>
#include "types.h"
#define binary(fun,op) parathon_int fun(parathon_int lhs, parathon_int rhs) { return lhs op rhs; }
#define unary(fun,op) parathon_int fun(parathon_int num) { return op num;}
binary(__and__, &);
binary(__or__, |);
binary(__xor__, ^);
binary(__mul__, *);
binary(__floordiv__, /);
binary(__mod__, %);
binary(__add__, +);
binary(__sub__, -);
binary(__lshift__, <<);
binary(__rshift__, >>);
unary(__invert__, ~);
unary(__neg__, -);
unary(__pos__, +);
char *__str__(parathon_int num)
{
    char * ret = malloc(sizeof(char) * 22);
    sprintf(ret, "%lli", num);
    return ret;
}
char __nonzero__(parathon_int num)
{
    return (char)(num != 0);
}
parathon_int __cmp__(parathon_int lhs, parathon_int rhs)
{
    return lhs < rhs ? -1 : (lhs > rhs ? 1 : 0);
}
parathon_float __truediv__(parathon_int lhs, parathon_int rhs)
{
    return (parathon_float)lhs / (parathon_float)rhs;
}
parathon_float __float__(parathon_int lhs)
{
    return lhs;
}
char *__repr__(parathon_int i) { return __str__(i); };
