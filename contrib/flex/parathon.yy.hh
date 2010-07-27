/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOK_ERROR = 258,
     TOK_NEWLINE = 259,
     TOK_INDENT = 260,
     TOK_OUTDENT = 261,
     TOK_INTEGER = 262,
     TOK_FLOAT = 263,
     TOK_OPEN_SQUARE = 264,
     TOK_CLOSE_SQUARE = 265,
     TOK_OPEN_CURLY = 266,
     TOK_CLOSE_CURLY = 267,
     TOK_OPEN_CURVED = 268,
     TOK_CLOSE_CURVED = 269,
     TOK_NAME = 270,
     TOK_STRING = 271,
     TOK_SEMICOLON = 272,
     TOK_COMMA = 273,
     TOK_DOT = 274,
     TOK_ASSIGN = 275,
     TOK_COLON = 276,
     TOK_AT = 277,
     TOK_BACKTICK = 278,
     TOK_NOTEQ = 279,
     TOK_LTEQ = 280,
     TOK_LT = 281,
     TOK_GTEQ = 282,
     TOK_GT = 283,
     TOK_EQ = 284,
     TOK_MODULUS = 285,
     TOK_TRUNC_DIVIDE = 286,
     TOK_DIVIDE = 287,
     TOK_MULTIPLY = 288,
     TOK_MINUS = 289,
     TOK_PLUS = 290,
     TOK_POWER = 291,
     TOK_BXOR = 292,
     TOK_BNOT = 293,
     TOK_BOR = 294,
     TOK_BAND = 295,
     TOK_RIGHTSHIFT = 296,
     TOK_LEFTSHIFT = 297,
     TOK_NOT = 298,
     TOK_IS = 299,
     TOK_IN = 300,
     TOK_OR = 301,
     TOK_AND = 302,
     TOK_IF = 303,
     TOK_ELIF = 304,
     TOK_ELSE = 305,
     TOK_PASS = 306,
     TOK_RETURN = 307,
     TOK_YIELD = 308,
     TOK_PRINT = 309,
     TOK_FOR = 310,
     TOK_WHILE = 311,
     TOK_BREAK = 312,
     TOK_CONTINUE = 313,
     TOK_TRY = 314,
     TOK_ASSERT = 315,
     TOK_RAISE = 316,
     TOK_EXCEPT = 317,
     TOK_FINALLY = 318,
     TOK_CLASS = 319,
     TOK_DEF = 320,
     TOK_LAMBDA = 321,
     TOK_FROM = 322,
     TOK_GLOBAL = 323,
     TOK_IMPORT = 324,
     TOK_AS = 325,
     TOK_WITH = 326,
     TOK_DEL = 327,
     TOK_EXEC = 328
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1685 of yacc.c  */
#line 48 "parathon.yy"

    TestPhraseOptional *test_phrase_optional;
    UnaryOperator *unary_operator;
    ArithOperator *arith_operator;
    ComparisonOperator *comparison_operator;
    DottedName *dotted_name;
    MultOperator *mult_operator;
    ParameterList *parameter_list;
    ParameterListArgs *parameter_list_args;
    ParameterPhrase *parameter_phrase;
    ShiftOperator *shift_operator;
    SingleInput *single_input;
    SliceList *slice_list;
    SlicePhrase *slice_phrase;
    SmallStatement *small_statement;
    TestStatement *test_statement;
    WhileStatement *while_statement;
    AssignStatement *assign_statement;
    BreakStatement *break_statement;
    CompEq *comp_eq;
    CompGt *comp_gt;
    CompGtEq *comp_gt_eq;
    CompIn *comp_in;
    CompIs *comp_is;
    CompLt *comp_lt;
    CompLtEq *comp_lt_eq;
    CompNotEq *comp_not_eq;
    CompNotIn *comp_not_in;
    CompNotIs *comp_not_is;
    ContinueStatement *continue_statement;
    DeleteStatement *delete_statement;
    FunctionDefinition *function_definition;
    GlobalStatement *global_statement;
    IfStatement *if_statement;
    ImportStatement *import_statement;
    OpBand *op_band;
    OpBnot *op_bnot;
    OpBor *op_bor;
    OpBxor *op_bxor;
    OpDivide *op_divide;
    OpLeftShift *op_left_shift;
    OpMinus *op_minus;
    OpMod *op_mod;
    OpMult *op_mult;
    OpNegative *op_negative;
    OpPlus *op_plus;
    OpPositive *op_positive;
    OpPower *op_power;
    OpRightShift *op_right_shift;
    OpTrunc *op_trunc;
    ParameterListKwargs *parameter_list_kwargs;
    ParameterListNonArgs *parameter_list_non_args;
    PassStatement *pass_statement;
    PrintStatement *print_statement;
    ReturnStatement *return_statement;
    Suite *suite;
    TestPhrase *test_phrase;
    DottedAsNames *dotted_as_names;
    ImportAsNames *import_as_names;
    SuiteBody *suite_body;
    TestList *test_list;
    TestListNonEmpty *test_list_non_empty;
    InlineIfPhrase *inline_if_phrase;
    OrPhrase *or_phrase;
    SimpleStatement *simple_statement;
    TestListNonTrailing *test_list_non_trailing;
    AndPhrase *and_phrase;
    NotPhrase *not_phrase;
    ComparisonPhrase *comparison_phrase;
    ComparisonList *comparison_list;
    Expression *expression;
    XorExpression *xor_expression;
    AndExpression *and_expression;
    ShiftExpression *shift_expression;
    ArithExpression *arith_expression;
    MultExpression *mult_expression;
    FactExpression *fact_expression;
    UnaryPhrase *unary_phrase;
    BasePhrase *base_phrase;
    TestPhraseBracketed *test_phrase_bracketed;
    TupleMaker *tuple_maker;
    ValueFloat *value_float;
    ValueInt *value_int;
    ValueString *value_string;
    FunctionCall *function_call;
    GetAttr *get_attr;
    GetItem *get_item;
    ListMaker *list_maker;
    NamePhrase *name_phrase;
    ReprPhrase *repr_phrase;
    T_COMMA t_comma;
    T_DEF t_def;
    T_DOT t_dot;
    T_DEL t_del;
    T_EQ t_eq;
    T_BREAK t_break;
    T_NEWLINE t_newline;
    T_RIGHTSHIFT t_rightshift;
    T_NOTEQ t_noteq;
    T_OPEN_CURVED t_open_curved;
    T_GT t_gt;
    T_TRUNC_DIVIDE t_trunc_divide;
    T_AND t_and;
    T_STRING t_string;
    T_MODULUS t_modulus;
    T_WHILE t_while;
    T_CONTINUE t_continue;
    T_PLUS t_plus;
    T_MINUS t_minus;
    T_POWER t_power;
    T_IMPORT t_import;
    T_CLOSE_CURVED t_close_curved;
    T_BOR t_bor;
    T_LT t_lt;
    T_MULTIPLY t_multiply;
    T_SEMICOLON t_semicolon;
    T_OUTDENT t_outdent;
    T_GTEQ t_gteq;
    T_LTEQ t_lteq;
    T_ELSE t_else;
    T_OPEN_SQUARE t_open_square;
    T_CLOSE_SQUARE t_close_square;
    T_DIVIDE t_divide;
    T_INDENT t_indent;
    T_BXOR t_bxor;
    T_RETURN t_return;
    T_NOT t_not;
    T_IF t_if;
    T_OR t_or;
    T_PRINT t_print;
    T_ASSIGN t_assign;
    T_IN t_in;
    T_LEFTSHIFT t_leftshift;
    T_PASS t_pass;
    T_AS t_as;
    T_NAME t_name;
    T_BAND t_band;
    T_BNOT t_bnot;
    T_IS t_is;
    T_INTEGER t_integer;
    T_BACKTICK t_backtick;
    T_FLOAT t_float;
    T_FROM t_from;
    T_GLOBAL t_global;
    T_COLON t_colon;
    /* lexer */
    long long int_val;
    double float_val;
    char *string;
    char *name;



/* Line 1685 of yacc.c  */
#line 278 "parathon.yy.hh"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif




#ifndef YYPUSH_DECLS
#  define YYPUSH_DECLS
struct yypstate;
typedef struct yypstate yypstate;
enum { YYPUSH_MORE = 4 };
#if defined __STDC__ || defined __cplusplus
int yypush_parse (yypstate *yyps, int yypushed_char, YYSTYPE const *yypushed_val, ParathonContext* context);
#else
int yypush_parse ();
#endif

#if defined __STDC__ || defined __cplusplus
yypstate * yypstate_new (void);
#else
yypstate * yypstate_new ();
#endif
#if defined __STDC__ || defined __cplusplus
void yypstate_delete (yypstate *yyps);
#else
void yypstate_delete ();
#endif
#endif

