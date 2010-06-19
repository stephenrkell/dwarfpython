#include <string.h>
#include <malloc.h>
#include <stdarg.h>
#include <limits.h>
#include <errno.h>
#include "buffer.h"

#define INITIAL_BUFFER_SIZE 4096
#define PROPAGATE_ERROR(exp, ...) int err_state ## __LINE_NO__ = exp; \
                                  if (err_state ## __LINE_NO__) \
                                  { \
                                      __VA_ARGS__; \
                                      return err_state ## __LINE_NO__; \
                                  }

int buffer_size(Buffer*, unsigned int length);

Buffer* new_buffer()
{
    Buffer* b = malloc(sizeof(Buffer));
    read_and_reset(b);
    return b;
}
char* read_and_reset(Buffer* b)
{
    char* ret;
    if (b == NULL)
        return NULL;

    ret = b->string;
    b->used = b->length = 0;
    b->string = NULL;
    return ret;
}
void old_buffer(Buffer* b)
{
    if (b == NULL)
        return;

    if (b->string)
        free(b->string);

    free(b);
}
/**
 * Resize the buffer to fit "length" bytes and a '\0'
 *
 * return 0 on success (b->string can be appended to)
 *        | EOVERFLOW when string is longer than 4 GB
 *        | ENOMEM if the realloc fails
 */
int buffer_size(Buffer* b, unsigned int length)
{
    unsigned int new_length = b->length;
    char *new_string;

    if (new_length == 0)
        new_length = INITIAL_BUFFER_SIZE;

    if (b->used + length >= UINT_MAX)
        return EOVERFLOW;

    while (b->used + length >= new_length) 
    {
        new_length = new_length * 2;
        if (new_length == 0) 
            new_length = UINT_MAX;
    }

    new_string = realloc(b->string, new_length * sizeof(char));
    if (new_string == NULL)
    {
        return ENOMEM;
    }
    else
    {
        b->string = new_string;
        b->length = new_length;
        return 0;
    }
}

Buffer* putb(Buffer* b)
{
    puts(b->string == NULL ? "" : b->string);
    return b;
}
Buffer* fputb(Buffer* b, FILE* f)
{
    fputs(b->string == NULL ? "" : b->string, f);
    return b;
}
int bputs(Buffer* b, char* s)
{
    int len = strlen(s);
    PROPAGATE_ERROR(buffer_size(b, len));
    strncpy(b->string + b->used, s, len + 1);
    b->used += len;
    return 0;
}
int bputc(Buffer* b, char c)
{
    PROPAGATE_ERROR(buffer_size(b, 1));
    b->string[b->used++] = c;
    b->string[b->used] = '\0';
    return 0;
}
int bprintf(Buffer* b, char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int written = vsnprintf(b->string + b->used, b->length - b->used, fmt, args);
    if (b->used + written >= b->length)
    {
        PROPAGATE_ERROR(buffer_size(b, written),
                va_end(args));
        vsnprintf(b->string + b->used, b->length - b->used, fmt, args);
    }
    b->used += written;
    va_end(args);
    return 0;
}
