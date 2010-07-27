#include <stdio.h>
#include "buffer.h"
#include "string.h"

#ifndef _LEXER_H
#define _LEXER_H

#define YY_EXTRA_TYPE yy_extra_type*
#define INDENT_STACK_LENGTH 16

#define YY_EXTRA_COMMON_SETTINGS(yyextra) \
    yyextra.cur_str = NULL; \
    yyextra.offset_read = 0; \
    yyextra.current_indent = 0; \
    yyextra.indent_stack[0] = 0;

#define YY_EXTRA_FOR_STRING(yyextra, str) { \
    YY_EXTRA_COMMON_SETTINGS(yyextra); \
    yyextra.file = NULL; \
    yyextra.finished = 1; \
    yyextra.line_read = str; \
    yyextra.length_read = strlen(str); }

#define YY_EXTRA_FOR_FILE(yyextra, fle) {\
    YY_EXTRA_COMMON_SETTINGS(yyextra); \
    yyextra.line_read = NULL; \
    yyextra.length_read = yyextra.offset_read = 0; \
    yyextra.file = fle; \
    yyextra.finished = 0; }

typedef struct yy_extra_type {
    FILE *file;
    Buffer *cur_str;
    char *line_read;
    unsigned int offset_read;
    int length_read;
    char finished;
    unsigned char indent_stack[INDENT_STACK_LENGTH];
    unsigned int current_indent;
} yy_extra_type;
enum IND_STATUS {IND_ERROR=0, IND_IN, IND_SAME, IND_OUT};
int handle_indentation(char *);
#endif
