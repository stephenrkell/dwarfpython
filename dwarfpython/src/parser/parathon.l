%{
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "buffer.h"
#include "ast.h"
#include "lexer.h"

#include "parathon.yy.hh"

#define LEXER_ERROR(format) printf("Lexer error, line %d:\n\t" format "\n", line_num); return 0;
#define SYNTAX_ERROR_(error) printf("Syntax error, line %d:\n\t%s\n", line_num, error);
#define SYNTAX_ERROR(format, ...) printf("Syntax error, line %d:\n\t" format "\n", line_num, __VA_ARGS__);
//#define LEX_DEBUG(format, ...) printf("lex, %d: " format "\n", line_num, __VA_ARGS__);
#define LEX_DEBUG(...) ;

#define YY_INPUT(buf, result, size) { result = parathon_input(buf, size, yyextra); } 

// This leaks memory like anything, lucky we imported a global GC 
int parathon_input(char * buf, int size, yy_extra_type* extra)
{
    size_t size_t_size = (size_t) size;
    if (!extra->line_read)
    {
        if (extra->finished) 
            return 0;

        if (isatty(fileno(extra->file)))
        {
            rl_instream = extra->file;
            extra->line_read = readline(">>> ");
        }
        else
        {
            extra->line_read = NULL;
            extra->length_read = getline(&(extra->line_read), &size_t_size, extra->file);
            if (extra->length_read == -1)
            {
                extra->line_read = NULL;
                extra->length_read = 0;
            }
        }
        if (! extra->line_read)
        {
            extra->finished = 1;
            extra->line_read = (char *)";";
        }
        else if (*extra->line_read)
        {
            add_history (extra->line_read);
        }

        extra->length_read = strlen(extra->line_read);
    }
    int end_offset = extra->length_read - extra->offset_read + 1;
    if (end_offset < size)
    {
        strncpy(buf, extra->line_read + extra->offset_read, end_offset);
        buf[end_offset - 1] = '\n';
        buf[end_offset] = '\0';
        extra->line_read = NULL;
        return end_offset;
    }
    else
    {
        printf("Line too long, maximum is: %d bytes\n", size);
        exit(1);
    }
    
}

#ifndef YYTOKENTYPE
typedef enum LEX_TOKEN {
    TOK_ERROR=0, 
    /* Indents */
    TOK_NEWLINE, TOK_INDENT, TOK_OUTDENT, 
    /* Numbers */
    TOK_INTEGER, TOK_FLOAT,
    /* Brackets */
    TOK_OPEN_SQUARE, TOK_CLOSE_SQUARE,
    TOK_OPEN_CURLY, TOK_CLOSE_CURLY,
    TOK_OPEN_CURVED, TOK_CLOSE_CURVED,
    /* Strings */
    TOK_NAME, TOK_STRING,
// punctuation
    /* Basic syntax */
    TOK_DOT, TOK_COMMA, TOK_COLON, TOK_SEMICOLON, TOK_ASSIGN, TOK_AT, TOK_BACKTICK
    /* Comparisons */
    TOK_EQ, TOK_GT, TOK_GTEQ, TOK_LT, TOK_LTEQ, TOK_NOTEQ,
    /* Arithmetic */
    TOK_PLUS, TOK_MINUS, TOK_MULTIPLY, TOK_DIVIDE, TOK_TRUNC_DIVIDE,
    TOK_POWER, TOK_MODULUS,
    /* Binary */
    TOK_BAND, TOK_BOR, TOK_BNOT, TOK_BXOR,
    /* Shifting */
    TOK_LEFTSHIFT, TOK_RIGHTSHIFT,
// keywords
    /* Conditions */
    TOK_AND, TOK_NOT, TOK_OR, TOK_IN, TOK_IS, 
    /* If statements */
    TOK_IF, TOK_ELIF, TOK_ELSE, 
    /* Block side-effects */
    TOK_PASS, TOK_RETURN, TOK_YIELD, TOK_PRINT, 
    /* Loops */
    TOK_FOR, TOK_WHILE, TOK_BREAK, TOK_CONTINUE, 
    /* Exceptions */
    TOK_TRY, TOK_ASSERT, TOK_RAISE, TOK_EXCEPT, TOK_FINALLY, 
    /* Definitions */
    TOK_CLASS, TOK_DEF, TOK_LAMBDA, 
    /* Names */
    TOK_FROM, TOK_GLOBAL, TOK_IMPORT, TOK_AS, 
    /* etc. */
    TOK_WITH, TOK_DEL, TOK_EXEC 
} LEX_TOKEN;
#endif

// Keep track of current line number for providing reasonable error messages;
unsigned int line_num = 1;
unsigned int bracket_count = 0;

/**
 * This function keeps track of indentation levels and causes the 
 * emission of INDENT and OUTDENT tokens as necessary.
 return 0;
 *
 * The indent_stack is an array of chars, the first of which is always 0
 * corresponding to the left-hand margin. Every time an INDENT is emitted,
 * a new value is pushed onto the stack (higher than the previous). When the
 * indentation decreases, an OUTDENT is emitted for every item that must be
 * popped from the stack in order to leave the last item equal to the new
 * indent. (If the indentation level of an OUTDENT is not in the stack, an
 * error is raised).
 *
 * As with python a tab is eight spaces wide.
 */
 
int handle_indentation(char * yytxt, yy_extra_type* extra)
{
    unsigned int cpos = 0;
    unsigned char indent_level = 0;

    // Find the indentation of this line.
    while (yytxt[cpos + 1] && indent_level < UCHAR_MAX)
    {
        if (yytxt[cpos] == ' ')
        {
            indent_level += 1;
        }
        else if (yytxt[cpos] == '\t')
        {
            indent_level += 8;
        }
        else
        {
            LEXER_ERROR("Unexpected leading whitespace.");
        }
        cpos++;
    }

    if (indent_level == UCHAR_MAX)
    {
        SYNTAX_ERROR_("Maximum indentation level exceded.");
        return IND_ERROR;
    }
    // An "indent"
    else if (indent_level > extra->indent_stack[extra->current_indent]) 
    {
        if (++extra->current_indent == INDENT_STACK_LENGTH)
        {
            SYNTAX_ERROR_("Maximum nested depth exceded.");
            return IND_ERROR;
        }
        else
        {
            extra->indent_stack[extra->current_indent] = indent_level;
            LEX_DEBUG("%s %d", "indent", indent_level);
            return IND_IN;
        }
    } 
    // An "outdent"
    else if (indent_level < extra->indent_stack[extra->current_indent]) 
    {
        if (extra->current_indent <= 0)
        {
            LEXER_ERROR("Unexpected unindent.");
        }
        else if (indent_level > extra->indent_stack[extra->current_indent - 1])
        {
            SYNTAX_ERROR("Unindent to incorrect column: %d", indent_level);
            return IND_ERROR;
        }
        else
        {
            --extra->current_indent;
            LEX_DEBUG("%s %d", "outdent", extra->indent_stack[extra->current_indent]);
            return IND_OUT;
        }
    }
    // Same indentation
    else
    {
        LEX_DEBUG("%s %d", "nodent", extra->indent_stack[extra->current_indent]);
        return IND_SAME;
    }

};

/** String handling, just some wrappers around buffers **/
// Ideally these would be functions, but we need to return and BEGIN
#define begin_string(type) \
    yyextra->cur_str = new_buffer(); \
    BEGIN(type);

#define append_string() \
    if (bputs(yyextra->cur_str, yytext)) {\
        SYNTAX_ERROR_("String too big");\
        BEGIN(ERROR);\
    }

#define append_char(c) \
    if (bputc(yyextra->cur_str, c)) {\
        SYNTAX_ERROR_("String too big");\
        BEGIN(ERROR);\
    }

#define end_string() \
    LEX_DEBUG("%s '%s'", "string", yyextra->cur_str->string);\
    BEGIN(NORMAL); \
    yylval->string = read_and_reset(yyextra->cur_str);\
    old_buffer(yyextra->cur_str);\
    return TOK_STRING;


/** Bracket handling. Needed to avoid whitespace taking effect within brackets **/
#define open_bracket(type) \
    if (bracket_count == UINT_MAX) \
    { \
        LEXER_ERROR("Exceded bracket count"); \
    } \
    else \
    { \
        bracket_count++; \
        LEX_DEBUG("%s%s", "open", yytext); \
        return TOK_OPEN_ ## type; \
    }

#define close_bracket(type) \
    if (!bracket_count || !--bracket_count) \
    { \
        BEGIN(NORMAL); \
    } \
    LEX_DEBUG("%s%s", "close", yytext); \
    return TOK_CLOSE_ ## type;

%}

%option header-file="parathon.l.h"
%option reentrant
%option bison-bridge
%option nounput

%x NORMAL
%x ERROR
%x STR1
%x STR2
%x STR3
%x STR6
%x RSTR1
%x RSTR2
%x RSTR3
%x RSTR6

RE_FLOAT [0-9]+(\.[0-9]+([eE][+-]?[0-9]+)?|[eE][+-]?[0-9]+)
RE_OCT [0-7]+
RE_DEC [1-9][0-9]*
RE_HEX 0x[0-9A-Fa-f]+
RE_NAME [_a-zA-Z][_a-zA-Z0-9]*

%%

<INITIAL>{ /*

    This context is entered into at the start of any line when indentation is significant,
    i.e. while not in strings or brackets.

    It should be provable that all possible lines match either of these patterns:

    case 1: The first character on the line is [^ \t#\n], 
        will match rule 1.
    case 2: The first character on the line is #, or the line is empty (equivalent to first character is \n), 
        will match rule 2.
    case 3: The first character on the line is [ \t], 
        can treat the second character on a line as if it were the first as [ \t] is subsumed into [ \t]* both times.
    By induction, either rule 1 or rule 2 will match.
*/

[ \t]*[^ \t#\n] { // If there is something on the line, then we care about the indentation.

    switch (handle_indentation(yytext, yyextra)) 
    {
        case IND_ERROR:
            fprintf(stderr, "Hello");
            return TOK_ERROR;

        case IND_IN: // Emit INDENT and pass the lookahead to <NORMAL>
            yyless(yyleng - 1);
            BEGIN(NORMAL);
            return TOK_INDENT;

        case IND_OUT: // Emit OUTDENT and loop in <INITIAL> until we get IND_SAME or IND_ERROR
            yyless(0);
            return TOK_OUTDENT;

        case IND_SAME: // pass the lookahead to <NORMAL>
            yyless(yyleng - 1);
            BEGIN(NORMAL);
            break;
    }
}

[ \t]*(#.*)?\n { // If there is nothing of value on the line, the indentation is not of value either.
    LEX_DEBUG("%s", "blank line");
    line_num++;
}

}

<ERROR>{

\n { 
    line_num++;
    BEGIN(INITIAL); 
}

. { // Skip over everything to the end of the line
}

}

<NORMAL>{ // Newlines are tokens when we are not within brackets or comments

;?\n { // newlines mark the ends of expressions (but only if there are no open brackets)
    if (bracket_count == 0)
    {
        LEX_DEBUG("%s", "newline");
        line_num++;
        BEGIN(INITIAL);
        return TOK_NEWLINE;
    }
    else
    {
        LEX_DEBUG("%s", "ignored line");
        line_num++;
    }
}

[ \t]+ |
#.* { /* spaces and comments are ignored */ }

\\\n {
    LEX_DEBUG("%s", "escaped newline");
    line_num++;
}

{RE_FLOAT} { //Floating point numbers

    double number;
    int status;

    status = sscanf(yytext, "%lf", &number);

    if (status == EOF) 
    {
        if (errno == ERANGE) 
        {
            SYNTAX_ERROR("Number out of range: %s", yytext);
        } 
        else
        {
            SYNTAX_ERROR("Error occured while reading number: %s", yytext);
        }
        BEGIN(ERROR);
    }
    else if (status != 1)
    {
        SYNTAX_ERROR("Invalid number: %s", yytext);
        BEGIN(ERROR);
    }
    else
    {
        LEX_DEBUG("%s %f", "float", number)

        yylval->float_val = number;
        return TOK_FLOAT;
    }
}

{RE_OCT} |
{RE_DEC} |
{RE_HEX} {

    char *failed = NULL;
    long long number;

    errno = 0;
    number = strtoll(yytext, &failed, 0);

    if (errno == ERANGE) 
    {
        SYNTAX_ERROR("Number out of range: %s", yytext);
        BEGIN(ERROR);
    }
    else if (*failed != '\0') 
    {
        SYNTAX_ERROR("Invalid number: %s\n", yytext);
        BEGIN(ERROR);
    }
    else
    {
        LEX_DEBUG("%s %lld", "integer", number);

        yylval->int_val = number;
        return TOK_INTEGER;
    }
}

"[" open_bracket(SQUARE);
"{" open_bracket(CURLY);
"(" open_bracket(CURVED);
"]" close_bracket(SQUARE);
"}" close_bracket(CURLY);
")" close_bracket(CURVED);

\'     begin_string(STR1);
\"     begin_string(STR2);
\'\'\' begin_string(STR3);
\"\"\" begin_string(STR6);

[rR]\'     begin_string(RSTR1);
[rR]\"     begin_string(RSTR2);
[rR]\'\'\' begin_string(RSTR3);
[rR]\"\"\" begin_string(RSTR6);

[rR]?[uU][rR]?\'     SYNTAX_ERROR_("Unicode strings are not supported");
[rR]?[uU][rR]?\"     SYNTAX_ERROR_("Unicode strings are not supported");
[rR]?[uU][rR]?\'\'\' SYNTAX_ERROR_("Unicode strings are not supported");
[rR]?[uU][rR]?\"\"\" SYNTAX_ERROR_("Unicode strings are not supported");

"."  return TOK_DOT;
","  return TOK_COMMA;
";"  return TOK_SEMICOLON;
":"  return TOK_COLON;
"="  return TOK_ASSIGN;
"@"  return TOK_AT;
"`"  return TOK_BACKTICK;

"+"  return TOK_PLUS;
"-"  return TOK_MINUS;
"*"  return TOK_MULTIPLY;
"**" return TOK_POWER;
"/"  return TOK_DIVIDE;
"//" return TOK_TRUNC_DIVIDE;
"%"  return TOK_MODULUS;

"<"  return TOK_LT;
">"  return TOK_GT;
"<>" return TOK_NOTEQ;
"==" return TOK_EQ;
"!=" return TOK_NOTEQ;
"<=" return TOK_LTEQ;
">=" return TOK_GTEQ;

"^"  return TOK_BXOR;
"&"  return TOK_BAND;
"~"  return TOK_BNOT;
"|"  return TOK_BOR;
"<<" return TOK_LEFTSHIFT;
">>" return TOK_RIGHTSHIFT;

"and" return TOK_AND;
"not" return TOK_NOT;
"or"  return TOK_OR;
"in"  return TOK_IN;
"is"  return TOK_IS;

"if"   return TOK_IF;
"elif" return TOK_ELIF;
"else" return TOK_ELSE;

"pass"   return TOK_PASS;
"return" return TOK_RETURN;
"yield"  return TOK_YIELD;
"print"  return TOK_PRINT;

"for"      return TOK_FOR;
"while"    return TOK_WHILE;
"break"    return TOK_BREAK;
"continue" return TOK_CONTINUE;

"try"     return TOK_TRY;
"assert"  return TOK_ASSERT;
"raise"   return TOK_RAISE;
"except"  return TOK_EXCEPT;
"finally" return TOK_FINALLY;

"class"  return TOK_CLASS;
"def"    return TOK_DEF;
"lambda" return TOK_LAMBDA;

"from"   return TOK_FROM;
"global" return TOK_GLOBAL;
"import" return TOK_IMPORT;
"as"     return TOK_AS;

"with" return TOK_WITH;
"del"  return TOK_DEL;
"exec" return TOK_EXEC;

{RE_NAME} { // A variable name
    LEX_DEBUG("%s '%s'", "name", yytext);
    yylval->name = strdup(yytext);
    return TOK_NAME;
}

. {
    SYNTAX_ERROR("Unexpected '%s'", yytext);
}
}

<RSTR1,STR1>{ // 'single quoted string'
\'         end_string();
[^\n\\\']* append_string();
}

<RSTR2,STR2>{ // "double quoted string"
\"         end_string();
[^\n\\\"]* append_string();
}

<RSTR3,STR3>{ // '''triple quoted string'''
\'\'\'     end_string();
\'{1,2}    |
[^\n\\\']* append_string();
}

<RSTR6,STR6>{ // """6-quoted string"""
\"\"\"     end_string();
\"{1,2}    |
[^\n\\\"]* append_string();
}

<RSTR1,STR1,RSTR2,STR2>{ // single-line strings
\n {
    BEGIN(INITIAL);
    SYNTAX_ERROR_("End of line within single-quoted string.")
    line_num++;
}
}

<RSTR3,STR3,RSTR6,STR6>{ // multi-line strings
\n {
    append_string();
    LEX_DEBUG("%s", "string newline");
    line_num++;
}
}

<STR1,STR2,STR3,STR6>{ // All strings - backslash escapes from http://www.python.org/doc/2.5.4/ref/strings.html

\\x[0-9A-Fa-f]{2} {
    unsigned long n = strtol(yytext + 1, NULL, 16);
    append_char((unsigned char) n);
}

\\\x {
    BEGIN(ERROR);
    SYNTAX_ERROR_("Invalid \\x escape");
}

\\[0-7]{1,3} {
    // NOTE: as with CPython this silently takes n % 256
    unsigned long n = strtol(yytext + 1, NULL, 8);
    append_char((unsigned char) n);
}

\\\n {
    LEX_DEBUG("%s", "escaped newline");
    line_num++;
}

\\\\ |
\\\' |
\\\" append_char(yytext[1]);

\\a append_char('\a');
\\b append_char('\b');
\\f append_char('\f');
\\n append_char('\n');
\\r append_char('\r');
\\t append_char('\t');
\\v append_char('\v');
\\. append_string();

}

<RSTR1,RSTR2,RSTR3,RSTR6>{ // Raw strings - backslashes are literals (but need special handling for \" etc.)

\\\n |
\\. append_string();

}

%%

#ifndef YYTOKENTYPE
int main (int argc, char* argv)
{
   int c;
    while (c = yylex());

    printf("Bye\n\n");
    return 0;
}
#endif
