#include <string.h>
#include <malloc.h>
#include "types.h"
char *__add__(char * lhs, char * rhs)
{
    char * ret = malloc(strlen(lhs) + strlen(rhs));
    strcpy(ret, lhs);
    strcat(ret, rhs);
    return ret;
}
char *__str__(char * str)
{
    return str;
}
char *__repr__(char * str)
{
    if (str == NULL)
        str = "";
    char * ret = malloc(strlen(str) + 2);
    sprintf(ret, "\"%s\"", str);
    return ret;
}
char __nonzero__(char * str)
{
    return strlen(str) == 0;
}
char *__mul__(char * str, int times)
{
    int len = strlen(str);
    int i=0;
    char * ret = malloc(len * times + 1);
    ret[0] = '\0';

    for (i=0; i<times; i++)
    {
        strcat(ret, str);
    }
    return ret;
}
int __cmp__(char *a, char* b)
{
    return strcmp(a, b);
}
