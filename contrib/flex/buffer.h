#include <stdio.h>
#ifndef _BUFFER_H
#define _BUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct buffer_s {
    char* string;
    unsigned int length;
    unsigned int used;
} Buffer;

/* Functions for managing buffers */

// Create an empty buffer with no space allocated to the string.
Buffer* new_buffer();
// Reset the buffer, the caller is responsible for freeing the returned contents.
char* read_and_reset(Buffer* b);
// Destroy the buffer and free all memory.
void old_buffer(Buffer*);

/* Functions for appending to buffers */

// These all return 0 on success, or ENOMEM or EOVERFLOW

// Append a '\0'-terminated string to the buffer.
int bputs(Buffer*, char*);
// Append a char to the buffer.
int bputc(Buffer*, char);
// sprintf() into the buffer according to the format
int bprintf(Buffer*, char*, ...);

/* Functions for printing the buffer */

// To STDOUT
Buffer* putb(Buffer*);
// To any file
Buffer* fputb(Buffer*, FILE*);

#ifdef __cplusplus
} // extern "C"
#endif
#endif // _BUFFER_H
