#include <malloc.h>
#include <string.h>
#include "types.h"

parathon_list *list___new__()
{
    return (parathon_list *)calloc(1,sizeof(parathon_list));
}
void *list___getitem__(parathon_list *l, parathon_int index)
{
    if (index > 0 && index < l->length)
        return l->data[index];

    return NULL;
}
// Add an item to the list
void list_append(parathon_list *l, void *datum)
{
    l->data = (void **)realloc(l->data, l->length+1);
    l->data[l->length++] = datum;
}
// Add two lists together
void list_extend(parathon_list *l, parathon_list *k)
{
    l->data = (void **)realloc(l->data, l->length + k->length);
    memcpy(&l->data[l->length], k->data, k->length * sizeof(void *));
    l->length += k->length;
}
static void (*list___add__)(parathon_list *, parathon_list *) = &list_extend;
