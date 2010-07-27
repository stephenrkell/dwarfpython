#include <string.h>
#include <malloc.h>
#include "types.h"
#define binary(fun,op) parathon_float fun(parathon_float lhs, parathon_float rhs) { return lhs op rhs; }
#define unary(fun,op) parathon_float fun(parathon_float num) { return op num;}
binary(__mul__, *);
binary(__truediv__, /);
binary(__add__, +);
binary(__sub__, -);
unary(__neg__, -);
unary(__pos__, +);
char *__str__(parathon_float num)
{
    char * ret = malloc(sizeof(char) * 22);
    sprintf(ret, "%g", num);
    return ret;
}
char __nonzero__(parathon_float num)
{
    return num != 0.0;
}
parathon_int __cmp__(parathon_float lhs, parathon_float rhs)
{
    return lhs < rhs ? -1 : ( lhs > rhs ? 1 : 0 );
}
parathon_float __floordiv__(parathon_float lhs, parathon_float rhs)
{
    return (parathon_float)(long)(lhs / rhs);
}
parathon_int __int__(parathon_float lhs)
{
    return lhs;
}
char *__repr__(parathon_float num){ return __str__(num); }
