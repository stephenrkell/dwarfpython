/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 1

/* Pull parsers.  */
#define YYPULL 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 2 "parathon.yy"

#line 285 "ast/autogen.py"

#include <cctype>
#include <cstring>
#include <stdio.h>
#include <iostream>
#include "ast.h"
#include "parathon.h"

extern "C" int line_num;
void evaluate(SingleInput * si, ParathonContext* context );
void yyerror(ParathonContext* context, char const *s)
{
    std::cout << "Syntax error, line " << line_num << std::endl;
}



/* Line 189 of yacc.c  */
#line 92 "parathon.yy.cc"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 214 of yacc.c  */
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



/* Line 214 of yacc.c  */
#line 355 "parathon.yy.cc"
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


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 391 "parathon.yy.cc"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   511

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  91
/* YYNRULES -- Number of rules.  */
#define YYNRULES  185
/* YYNRULES -- Number of states.  */
#define YYNSTATES  272

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   328

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    11,    16,    17,    19,    21,
      23,    25,    27,    29,    31,    33,    35,    37,    39,    41,
      43,    45,    47,    49,    51,    55,    57,    59,    61,    63,
      65,    67,    71,    73,    76,    81,    83,    87,    89,    91,
      93,    96,    98,   100,   102,   104,   108,   110,   114,   118,
     124,   126,   128,   130,   132,   134,   136,   138,   140,   142,
     144,   146,   149,   153,   158,   162,   164,   166,   168,   170,
     172,   174,   176,   178,   180,   183,   186,   188,   191,   199,
     202,   206,   211,   216,   219,   224,   231,   239,   241,   243,
     245,   247,   249,   251,   253,   255,   257,   259,   261,   263,
     265,   267,   269,   270,   273,   277,   279,   283,   285,   288,
     292,   298,   301,   304,   309,   311,   314,   316,   320,   324,
     330,   332,   336,   340,   346,   348,   351,   352,   354,   356,
     359,   364,   366,   370,   372,   375,   379,   381,   385,   387,
     391,   393,   396,   398,   400,   404,   408,   410,   414,   416,
     420,   422,   426,   428,   432,   434,   438,   440,   444,   446,
     450,   452,   455,   457,   459,   461,   463,   465,   467,   469,
     471,   473,   475,   477,   481,   487,   492,   494,   496,   498,
     503,   507,   512,   518,   522,   524
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      75,     0,    -1,    -1,    75,    86,    -1,    75,     1,     4,
      -1,    75,     5,     1,     4,    -1,    -1,   131,    -1,   119,
      -1,   121,    -1,   111,    -1,   120,    -1,   116,    -1,    99,
      -1,    95,    -1,   100,    -1,    96,    -1,    94,    -1,   101,
      -1,    97,    -1,   102,    -1,    98,    -1,   103,    -1,    15,
      -1,    80,    19,    15,    -1,   118,    -1,   114,    -1,   124,
      -1,   117,    -1,    83,    -1,   126,    -1,   126,    18,    83,
      -1,   125,    -1,    33,   131,    -1,    33,   131,    18,   125,
      -1,   131,    -1,   163,    20,   131,    -1,   115,    -1,   123,
      -1,     4,    -1,   139,     4,    -1,   108,    -1,    91,    -1,
     106,    -1,    88,    -1,    87,    18,    88,    -1,   131,    -1,
      19,    19,    19,    -1,    76,    21,    76,    -1,    76,    21,
      76,    21,    76,    -1,   128,    -1,   109,    -1,   105,    -1,
      93,    -1,   104,    -1,   127,    -1,   107,    -1,    92,    -1,
      90,    -1,   129,    -1,   131,    -1,   140,    18,    -1,   140,
      18,   131,    -1,    56,   131,    21,   130,    -1,    90,    20,
      90,    -1,    57,    -1,    29,    -1,    28,    -1,    27,    -1,
      45,    -1,    44,    -1,    26,    -1,    25,    -1,    24,    -1,
      43,    45,    -1,    44,    43,    -1,    58,    -1,    72,   135,
      -1,    65,   163,    13,    82,    14,    21,   130,    -1,    68,
     163,    -1,   107,    18,   163,    -1,    48,   131,    21,   130,
      -1,   108,    50,    21,   130,    -1,    69,   132,    -1,    67,
      80,    69,   133,    -1,    67,    80,    69,    13,   133,    14,
      -1,    67,    80,    69,    13,   133,    18,    14,    -1,    40,
      -1,    38,    -1,    39,    -1,    37,    -1,    32,    -1,    42,
      -1,    34,    -1,    30,    -1,    33,    -1,    34,    -1,    35,
      -1,    35,    -1,    36,    -1,    41,    -1,    31,    -1,    -1,
      36,   131,    -1,    36,   131,    18,    -1,    84,    -1,   126,
      18,    84,    -1,    51,    -1,    54,   135,    -1,    54,    41,
     131,    -1,    54,    41,   131,    18,   136,    -1,    52,   135,
      -1,   139,     4,    -1,     4,     5,   134,     6,    -1,   138,
      -1,   138,   137,    -1,    80,    -1,    80,    70,    15,    -1,
     132,    18,    80,    -1,   132,    18,    80,    70,    15,    -1,
      15,    -1,    15,    70,    15,    -1,   133,    18,    15,    -1,
     133,    18,    15,    70,    15,    -1,    86,    -1,   134,    86,
      -1,    -1,   136,    -1,   140,    -1,   140,    18,    -1,    48,
     138,    50,   131,    -1,   141,    -1,   138,    46,   141,    -1,
      89,    -1,   139,    17,    -1,   139,    17,    89,    -1,   131,
      -1,   140,    18,   131,    -1,   142,    -1,   141,    47,   142,
      -1,   143,    -1,    43,   142,    -1,   145,    -1,   144,    -1,
     145,    79,   145,    -1,   144,    79,   145,    -1,   146,    -1,
     146,   112,   145,    -1,   147,    -1,   147,   113,   146,    -1,
     148,    -1,   148,   110,   147,    -1,   149,    -1,   148,    85,
     149,    -1,   150,    -1,   149,    78,   150,    -1,   151,    -1,
     150,    81,   151,    -1,   152,    -1,   152,   122,   151,    -1,
     153,    -1,    77,   152,    -1,   163,    -1,   161,    -1,   160,
      -1,   159,    -1,   162,    -1,   155,    -1,   164,    -1,   154,
      -1,   157,    -1,   156,    -1,   158,    -1,    13,   131,    14,
      -1,    13,   140,    18,   131,    14,    -1,    13,   140,    18,
      14,    -1,     8,    -1,     7,    -1,    16,    -1,   153,    13,
      82,    14,    -1,   153,    19,   163,    -1,   153,     9,    87,
      10,    -1,   153,     9,    87,    18,    10,    -1,     9,   135,
      10,    -1,    15,    -1,    23,   140,    23,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   342,   342,   343,   344,   345,   348,   349,   351,   352,
     353,   355,   356,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   369,   370,   372,   373,   374,   375,   377,
     378,   379,   381,   382,   383,   385,   386,   388,   389,   391,
     392,   393,   394,   395,   397,   398,   400,   401,   402,   403,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     416,   417,   418,   420,   422,   424,   426,   428,   430,   432,
     434,   436,   438,   440,   442,   444,   446,   448,   450,   452,
     453,   455,   456,   458,   459,   460,   461,   463,   465,   467,
     469,   471,   473,   475,   477,   479,   481,   483,   485,   487,
     489,   491,   493,   494,   495,   497,   498,   500,   502,   503,
     504,   506,   508,   509,   511,   512,   514,   515,   516,   517,
     519,   520,   521,   522,   524,   525,   527,   528,   530,   531,
     533,   535,   536,   538,   539,   540,   542,   543,   545,   546,
     548,   549,   551,   552,   554,   555,   557,   558,   560,   561,
     563,   564,   566,   567,   569,   570,   572,   573,   575,   576,
     578,   579,   581,   582,   583,   584,   585,   586,   587,   588,
     589,   590,   591,   593,   595,   596,   598,   600,   602,   604,
     606,   608,   609,   611,   613,   615
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_ERROR", "TOK_NEWLINE", "TOK_INDENT",
  "TOK_OUTDENT", "TOK_INTEGER", "TOK_FLOAT", "TOK_OPEN_SQUARE",
  "TOK_CLOSE_SQUARE", "TOK_OPEN_CURLY", "TOK_CLOSE_CURLY",
  "TOK_OPEN_CURVED", "TOK_CLOSE_CURVED", "TOK_NAME", "TOK_STRING",
  "TOK_SEMICOLON", "TOK_COMMA", "TOK_DOT", "TOK_ASSIGN", "TOK_COLON",
  "TOK_AT", "TOK_BACKTICK", "TOK_NOTEQ", "TOK_LTEQ", "TOK_LT", "TOK_GTEQ",
  "TOK_GT", "TOK_EQ", "TOK_MODULUS", "TOK_TRUNC_DIVIDE", "TOK_DIVIDE",
  "TOK_MULTIPLY", "TOK_MINUS", "TOK_PLUS", "TOK_POWER", "TOK_BXOR",
  "TOK_BNOT", "TOK_BOR", "TOK_BAND", "TOK_RIGHTSHIFT", "TOK_LEFTSHIFT",
  "TOK_NOT", "TOK_IS", "TOK_IN", "TOK_OR", "TOK_AND", "TOK_IF", "TOK_ELIF",
  "TOK_ELSE", "TOK_PASS", "TOK_RETURN", "TOK_YIELD", "TOK_PRINT",
  "TOK_FOR", "TOK_WHILE", "TOK_BREAK", "TOK_CONTINUE", "TOK_TRY",
  "TOK_ASSERT", "TOK_RAISE", "TOK_EXCEPT", "TOK_FINALLY", "TOK_CLASS",
  "TOK_DEF", "TOK_LAMBDA", "TOK_FROM", "TOK_GLOBAL", "TOK_IMPORT",
  "TOK_AS", "TOK_WITH", "TOK_DEL", "TOK_EXEC", "$accept", "all_input",
  "test_phrase_optional", "unary_operator", "arith_operator",
  "comparison_operator", "dotted_name", "mult_operator", "parameter_list",
  "parameter_list_args", "parameter_phrase", "shift_operator",
  "single_input", "slice_list", "slice_phrase", "small_statement",
  "test_statement", "while_statement", "assign_statement",
  "break_statement", "comp_eq", "comp_gt", "comp_gt_eq", "comp_in",
  "comp_is", "comp_lt", "comp_lt_eq", "comp_not_eq", "comp_not_in",
  "comp_not_is", "continue_statement", "delete_statement",
  "function_definition", "global_statement", "if_statement",
  "import_statement", "op_band", "op_bnot", "op_bor", "op_bxor",
  "op_divide", "op_left_shift", "op_minus", "op_mod", "op_mult",
  "op_negative", "op_plus", "op_positive", "op_power", "op_right_shift",
  "op_trunc", "parameter_list_kwargs", "parameter_list_non_args",
  "pass_statement", "print_statement", "return_statement", "suite",
  "test_phrase", "dotted_as_names", "import_as_names", "suite_body",
  "test_list", "test_list_non_empty", "inline_if_phrase", "or_phrase",
  "simple_statement", "test_list_non_trailing", "and_phrase", "not_phrase",
  "comparison_phrase", "comparison_list", "expression", "xor_expression",
  "and_expression", "shift_expression", "arith_expression",
  "mult_expression", "fact_expression", "unary_phrase", "base_phrase",
  "test_phrase_bracketed", "tuple_maker", "value_float", "value_int",
  "value_string", "function_call", "get_attr", "get_item", "list_maker",
  "name_phrase", "repr_phrase", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    75,    75,    75,    76,    76,    77,    77,
      77,    78,    78,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    80,    80,    81,    81,    81,    81,    82,
      82,    82,    83,    83,    83,    84,    84,    85,    85,    86,
      86,    86,    86,    86,    87,    87,    88,    88,    88,    88,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      90,    90,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     107,   108,   108,   109,   109,   109,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   125,   125,   126,   126,   127,   128,   128,
     128,   129,   130,   130,   131,   131,   132,   132,   132,   132,
     133,   133,   133,   133,   134,   134,   135,   135,   136,   136,
     137,   138,   138,   139,   139,   139,   140,   140,   141,   141,
     142,   142,   143,   143,   144,   144,   145,   145,   146,   146,
     147,   147,   148,   148,   149,   149,   150,   150,   151,   151,
     152,   152,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   154,   155,   155,   156,   157,   158,   159,
     160,   161,   161,   162,   163,   164
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     3,     4,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     1,     2,     4,     1,     3,     1,     1,     1,
       2,     1,     1,     1,     1,     3,     1,     3,     3,     5,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     3,     4,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     2,     7,     2,
       3,     4,     4,     2,     4,     6,     7,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     2,     3,     1,     3,     1,     2,     3,
       5,     2,     2,     4,     1,     2,     1,     3,     3,     5,
       1,     3,     3,     5,     1,     2,     0,     1,     1,     2,
       4,     1,     3,     1,     2,     3,     1,     3,     1,     3,
       1,     2,     1,     1,     3,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     5,     4,     1,     1,     1,     4,
       3,     4,     5,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,    39,     0,   177,   176,   126,     0,
     184,   178,     0,    96,    98,    88,     0,     0,   107,   126,
     126,     0,    65,    76,     0,     0,     0,     0,   126,     0,
       3,   133,    58,    42,    57,    53,    54,    52,    43,    56,
      41,    51,    10,     8,     9,    55,    50,    59,    60,   114,
       0,     0,   131,   138,   140,   143,   142,   146,   148,   150,
     152,   154,   156,   158,   160,   169,   167,   171,   170,   172,
     165,   164,   163,   166,   162,   168,     4,     0,   136,     0,
     127,   128,   136,     0,     0,   141,     0,   111,     0,   108,
       0,     0,    23,     0,    79,   116,    83,    77,   161,     0,
       0,     0,     0,     0,   115,    40,   134,    61,     0,    73,
      72,    71,    68,    67,    66,     0,    70,    69,     0,    17,
      14,    16,    19,    21,    13,    15,    18,    20,    22,     0,
      89,     0,    90,     0,    87,   100,    92,     0,     0,    37,
      38,    93,    97,     0,    12,    11,    94,   101,    91,    95,
       0,    26,    28,    25,    27,    99,     0,     6,   102,     0,
       5,   183,   129,   173,     0,     0,   185,     0,   109,     0,
     102,     0,     0,     0,     0,    64,    80,     0,   132,     0,
     135,    62,   139,    74,    75,   145,   144,   147,   149,   153,
     151,   155,   157,   159,     0,     0,     0,    44,    46,     0,
       0,     0,    29,   105,    32,    30,    35,   162,   180,   137,
     175,   137,     0,    81,     0,     0,    63,     0,    24,     0,
     120,    84,   117,   118,    82,     0,     0,     6,   181,     6,
      33,   103,   179,   102,     0,   174,     0,   112,   110,     0,
       0,     0,     0,     0,   130,    47,    48,     7,   182,    45,
     102,   104,    31,   106,    36,   124,     0,     0,    85,     0,
     121,   122,   119,     6,    34,   113,   125,    78,    86,     0,
      49,   123
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,   195,    29,   143,   118,    93,   150,   201,   202,
     203,   137,    30,   196,   197,    31,    32,    33,    34,    35,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
      36,    37,    38,    39,    40,    41,   138,    42,   131,   133,
     151,   139,   144,   152,   153,    43,   145,    44,   156,   140,
     154,   204,   205,    45,    46,    47,   213,    48,    96,   221,
     256,    79,    80,   104,    49,   214,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -215
static const yytype_int16 yypact[] =
{
    -215,    36,  -215,    28,  -215,    53,  -215,  -215,   460,   460,
    -215,  -215,   460,  -215,  -215,  -215,   460,   460,  -215,   460,
     386,   460,  -215,  -215,    49,    70,    49,    70,   460,   473,
    -215,  -215,    66,  -215,  -215,  -215,  -215,  -215,  -215,    78,
      47,  -215,  -215,  -215,  -215,  -215,  -215,  -215,    82,    43,
      21,    84,    59,  -215,  -215,    85,    85,    79,    83,    75,
      38,    45,  -215,    71,    15,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,   115,  -215,   111,
    -215,   104,   109,   106,    30,  -215,   105,  -215,   460,  -215,
     110,   112,  -215,   -11,  -215,    -5,   114,  -215,  -215,   460,
      49,   113,   460,   460,  -215,  -215,   301,   460,   460,  -215,
    -215,  -215,  -215,  -215,  -215,    96,   100,  -215,   473,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,   473,
    -215,   473,  -215,   473,  -215,  -215,  -215,   473,   473,  -215,
    -215,  -215,  -215,   473,  -215,  -215,  -215,  -215,  -215,  -215,
     473,  -215,  -215,  -215,  -215,  -215,   473,   423,   341,    49,
    -215,  -215,   460,  -215,   436,   460,  -215,   261,   128,   261,
     341,   132,    54,   133,    70,  -215,  -215,   261,    59,    10,
    -215,   137,  -215,  -215,  -215,  -215,  -215,  -215,  -215,    38,
    -215,    45,  -215,  -215,   108,   138,    37,  -215,   139,   460,
     460,   144,  -215,  -215,  -215,   143,  -215,   145,  -215,  -215,
    -215,   152,   163,  -215,    29,   460,  -215,   155,  -215,   156,
     103,   157,  -215,    -2,  -215,   460,   151,   460,  -215,   373,
     158,   160,  -215,   341,   460,  -215,   195,  -215,  -215,   153,
      48,   164,   167,   169,  -215,  -215,   168,  -215,  -215,  -215,
     154,  -215,  -215,  -215,  -215,  -215,   129,   261,  -215,    68,
    -215,   118,  -215,   460,  -215,  -215,  -215,  -215,  -215,   178,
    -215,  -215
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -215,  -215,  -206,  -215,  -215,   149,   -21,  -215,    25,   -33,
     -27,  -215,  -214,  -215,   -20,   107,   116,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,   -38,  -215,  -215,  -215,  -215,  -159,    -8,  -215,    -3,
    -215,    11,     5,  -215,   120,     1,     7,   122,   -13,  -215,
    -215,   -68,    94,    90,  -215,    95,    88,  -127,   205,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,   -19,
    -215
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -138
static const yytype_int16 yytable[] =
{
      78,    82,    50,    85,    78,    91,    95,    94,   171,    86,
     216,    78,    78,    90,   171,    81,    83,   171,   224,    84,
      78,   246,   255,   192,   157,   105,    81,    81,   158,   193,
      87,    89,    76,   237,   159,    81,     2,     3,   106,    97,
       4,     5,   266,     6,     7,     8,   106,   228,   165,     9,
     185,    10,    11,   166,    77,   229,   102,   270,   172,    12,
     225,   186,   258,   187,    10,   173,   259,   219,   243,   220,
      13,    14,   141,   142,    15,   146,   147,   148,   149,    16,
     168,   176,   268,   261,    17,    92,    99,    18,    19,   102,
      20,   103,    21,    22,    23,   182,   100,   101,   267,   181,
    -136,    24,   107,    25,    26,    27,   108,   155,    28,   109,
     110,   111,   112,   113,   114,   134,   135,   136,   130,   160,
     132,   161,   162,   163,   164,   170,   167,   226,   115,   116,
     117,   169,   174,     4,   177,   265,     6,     7,     8,   207,
     208,   183,     9,   184,    10,    11,   215,   218,   222,   198,
     206,   207,    12,   223,   209,  -137,   211,   209,   232,   227,
      -7,   233,   206,    13,    14,   234,   235,    15,   236,   239,
     245,   220,    16,   241,   257,   242,   250,    17,   251,   260,
      18,    19,   261,    20,   262,    21,    22,    23,   269,   263,
     200,   230,   231,   271,    24,   217,    25,    26,    27,     4,
     252,    28,     6,     7,     8,   129,   253,    78,     9,   249,
      10,    11,   264,   180,   207,   175,   240,   244,    12,   247,
     238,   198,    81,   179,   178,   206,   254,   188,   190,    13,
      14,   191,   189,    15,    98,     0,     0,    50,    16,     0,
       0,     0,     0,    17,     0,     0,    18,    19,     0,    20,
       0,    21,    22,    23,     0,   247,     0,    50,     0,     0,
      24,     0,    25,    26,    27,   212,     0,    28,     6,     7,
       8,     0,     0,     0,     9,     0,    10,    11,     0,     0,
       0,     0,     0,     0,    12,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    13,    14,     0,     0,    15,
       0,     0,     0,     0,    16,     0,     0,     0,     6,     7,
       8,     0,    18,    19,     9,    20,    10,    11,    22,    23,
       0,     0,     0,     0,    12,     0,     0,     0,    25,    26,
      27,     0,     0,    28,     0,    13,    14,     0,     0,    15,
       0,     0,     0,     0,    16,     0,     0,     0,     6,     7,
       8,     0,    18,    19,     9,    20,    10,    11,    22,    23,
       0,     0,     0,     0,    12,     0,     0,     0,    25,    26,
      27,     0,     0,    28,   199,    13,    14,   200,     0,    15,
       6,     7,     8,   248,    16,     0,     9,     0,    10,    11,
       0,     0,   194,     6,     7,     8,    12,     0,     0,     9,
       0,    10,    11,     0,     0,     0,     0,    13,    14,    12,
       0,    15,     0,     0,     0,     0,    16,     0,     0,     0,
      13,    14,     0,     0,    15,     0,     0,    88,     0,    16,
       6,     7,     8,     0,     0,     0,     9,     0,    10,    11,
       0,     0,   194,     6,     7,     8,    12,     0,     0,     9,
     210,    10,    11,     0,     0,     0,     0,    13,    14,    12,
       0,    15,     0,     0,     0,     0,    16,     6,     7,     8,
      13,    14,     0,     9,    15,    10,    11,     0,     0,    16,
       6,     7,     8,    12,     0,     0,     9,     0,    10,    11,
       0,     0,     0,     0,    13,    14,    12,     0,    15,     0,
       0,     0,     0,    16,     0,     0,     0,    13,    14,     0,
       0,    15
};

static const yytype_int16 yycheck[] =
{
       8,     9,     1,    16,    12,    24,    27,    26,    19,    17,
     169,    19,    20,    21,    19,     8,     9,    19,   177,    12,
      28,   227,   236,   150,     9,     4,    19,    20,    13,   156,
      19,    20,     4,     4,    19,    28,     0,     1,    17,    28,
       4,     5,   256,     7,     8,     9,    17,    10,    18,    13,
     118,    15,    16,    23,     1,    18,    46,   263,    69,    23,
      50,   129,    14,   131,    15,    70,    18,    13,    70,    15,
      34,    35,    34,    35,    38,    30,    31,    32,    33,    43,
      88,   100,    14,    15,    48,    15,    20,    51,    52,    46,
      54,    48,    56,    57,    58,   108,    18,    50,   257,   107,
      18,    65,    18,    67,    68,    69,    47,    36,    72,    24,
      25,    26,    27,    28,    29,    40,    41,    42,    39,     4,
      37,    10,    18,    14,    18,    13,    21,    19,    43,    44,
      45,    21,    18,     4,    21,     6,     7,     8,     9,   158,
     159,    45,    13,    43,    15,    16,    18,    15,    15,   157,
     158,   170,    23,   174,   162,    18,   164,   165,    14,    21,
      21,    18,   170,    34,    35,    20,    14,    38,     5,    14,
      19,    15,    43,    70,    21,    18,    18,    48,    18,    15,
      51,    52,    15,    54,    15,    56,    57,    58,    70,    21,
      36,   199,   200,    15,    65,   170,    67,    68,    69,     4,
     233,    72,     7,     8,     9,    56,   233,   215,    13,   229,
      15,    16,   250,   106,   233,    99,   219,   225,    23,   227,
     215,   229,   215,   103,   102,   233,   234,   133,   138,    34,
      35,   143,   137,    38,    29,    -1,    -1,   236,    43,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    51,    52,    -1,    54,
      -1,    56,    57,    58,    -1,   263,    -1,   256,    -1,    -1,
      65,    -1,    67,    68,    69,     4,    -1,    72,     7,     8,
       9,    -1,    -1,    -1,    13,    -1,    15,    16,    -1,    -1,
      -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    35,    -1,    -1,    38,
      -1,    -1,    -1,    -1,    43,    -1,    -1,    -1,     7,     8,
       9,    -1,    51,    52,    13,    54,    15,    16,    57,    58,
      -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    67,    68,
      69,    -1,    -1,    72,    -1,    34,    35,    -1,    -1,    38,
      -1,    -1,    -1,    -1,    43,    -1,    -1,    -1,     7,     8,
       9,    -1,    51,    52,    13,    54,    15,    16,    57,    58,
      -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    67,    68,
      69,    -1,    -1,    72,    33,    34,    35,    36,    -1,    38,
       7,     8,     9,    10,    43,    -1,    13,    -1,    15,    16,
      -1,    -1,    19,     7,     8,     9,    23,    -1,    -1,    13,
      -1,    15,    16,    -1,    -1,    -1,    -1,    34,    35,    23,
      -1,    38,    -1,    -1,    -1,    -1,    43,    -1,    -1,    -1,
      34,    35,    -1,    -1,    38,    -1,    -1,    41,    -1,    43,
       7,     8,     9,    -1,    -1,    -1,    13,    -1,    15,    16,
      -1,    -1,    19,     7,     8,     9,    23,    -1,    -1,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    34,    35,    23,
      -1,    38,    -1,    -1,    -1,    -1,    43,     7,     8,     9,
      34,    35,    -1,    13,    38,    15,    16,    -1,    -1,    43,
       7,     8,     9,    23,    -1,    -1,    13,    -1,    15,    16,
      -1,    -1,    -1,    -1,    34,    35,    23,    -1,    38,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    -1,    34,    35,    -1,
      -1,    38
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    75,     0,     1,     4,     5,     7,     8,     9,    13,
      15,    16,    23,    34,    35,    38,    43,    48,    51,    52,
      54,    56,    57,    58,    65,    67,    68,    69,    72,    77,
      86,    89,    90,    91,    92,    93,   104,   105,   106,   107,
     108,   109,   111,   119,   121,   127,   128,   129,   131,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,     4,     1,   131,   135,
     136,   140,   131,   140,   140,   142,   131,   135,    41,   135,
     131,   163,    15,    80,   163,    80,   132,   135,   152,    20,
      18,    50,    46,    48,   137,     4,    17,    18,    47,    24,
      25,    26,    27,    28,    29,    43,    44,    45,    79,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,    79,
      39,   112,    37,   113,    40,    41,    42,    85,   110,   115,
     123,    34,    35,    78,   116,   120,    30,    31,    32,    33,
      81,   114,   117,   118,   124,    36,   122,     9,    13,    19,
       4,    10,    18,    14,    18,    18,    23,    21,   131,    21,
      13,    19,    69,    70,    18,    90,   163,    21,   141,   138,
      89,   131,   142,    45,    43,   145,   145,   145,   146,   149,
     147,   150,   151,   151,    19,    76,    87,    88,   131,    33,
      36,    82,    83,    84,   125,   126,   131,   163,   163,   131,
      14,   131,     4,   130,   139,    18,   130,    82,    15,    13,
      15,   133,    15,    80,   130,    50,    19,    21,    10,    18,
     131,   131,    14,    18,    20,    14,     5,     4,   136,    14,
     133,    70,    18,    70,   131,    19,    76,   131,    10,    88,
      18,    18,    83,    84,   131,    86,   134,    21,    14,    18,
      15,    15,    15,    21,   125,     6,    86,   130,    14,    70,
      76,    15
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (context, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, context); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, ParathonContext* context)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, context)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    ParathonContext* context;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (context);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, ParathonContext* context)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, context)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    ParathonContext* context;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, context);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, ParathonContext* context)
#else
static void
yy_reduce_print (yyvsp, yyrule, context)
    YYSTYPE *yyvsp;
    int yyrule;
    ParathonContext* context;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , context);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, context); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, ParathonContext* context)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, context)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    ParathonContext* context;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (context);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}






struct yypstate
  {
        /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

    /* Used to determine if this is the first time this instance has
       been used.  */
    int yynew;
  };

/* Initialize the parser data structure.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
yypstate *
yypstate_new (void)
#else
yypstate *
yypstate_new ()

#endif
{
  yypstate *yyps;
  yyps = (yypstate *) malloc (sizeof *yyps);
  if (!yyps)
    return 0;
  yyps->yynew = 1;
  return yyps;
}

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void
yypstate_delete (yypstate *yyps)
#else
void
yypstate_delete (yyps)
    yypstate *yyps;
#endif
{
#ifndef yyoverflow
  /* If the stack was reallocated but the parse did not complete, then the
     stack still needs to be freed.  */
  if (!yyps->yynew && yyps->yyss != yyps->yyssa)
    YYSTACK_FREE (yyps->yyss);
#endif
  free (yyps);
}

#define yynerrs yyps->yynerrs
#define yystate yyps->yystate
#define yyerrstatus yyps->yyerrstatus
#define yyssa yyps->yyssa
#define yyss yyps->yyss
#define yyssp yyps->yyssp
#define yyvsa yyps->yyvsa
#define yyvs yyps->yyvs
#define yyvsp yyps->yyvsp
#define yystacksize yyps->yystacksize

/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yypush_parse (yypstate *yyps, int yypushed_char, YYSTYPE const *yypushed_val, ParathonContext* context)
#else
int
yypush_parse (yyps, yypushed_char, yypushed_val, context)
    yypstate *yyps;
    int yypushed_char;
    YYSTYPE const *yypushed_val;
    ParathonContext* context;
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;


  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  if (!yyps->yynew)
    {
      yyn = yypact[yystate];
      goto yyread_pushed_token;
    }

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      if (!yyps->yynew)
        {
          YYDPRINTF ((stderr, "Return for a new token:\n"));
          yyresult = YYPUSH_MORE;
          goto yypushreturn;
        }
      yyps->yynew = 0;
yyread_pushed_token:
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yypushed_char;
      if (yypushed_val)
        yylval = *yypushed_val;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1464 of yacc.c  */
#line 342 "ast/autogen.py"
    { ;}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 343 "ast/autogen.py"
    { evaluate((yyvsp[(2) - (2)].single_input), context); ;}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 344 "ast/autogen.py"
    { if (context->interpreterMode) yyerrok; else return 0; ;}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 345 "ast/autogen.py"
    { if (context->interpreterMode) yyerrok; else return 0; ;}
    break;

  case 6:

/* Line 1464 of yacc.c  */
#line 348 "ast/autogen.py"
    { (yyval.test_phrase_optional) = TestPhraseOptional::parse(); (yyval.test_phrase_optional)->linenum = line_num; ;}
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 349 "ast/autogen.py"
    { (yyval.test_phrase_optional) = TestPhraseOptional::parse((yyvsp[(1) - (1)].test_phrase)); (yyval.test_phrase_optional)->linenum = line_num; ;}
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 351 "ast/autogen.py"
    { (yyval.unary_operator) = UnaryOperator::parse((yyvsp[(1) - (1)].op_negative)); (yyval.unary_operator)->linenum = line_num; ;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 352 "ast/autogen.py"
    { (yyval.unary_operator) = UnaryOperator::parse((yyvsp[(1) - (1)].op_positive)); (yyval.unary_operator)->linenum = line_num; ;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 353 "ast/autogen.py"
    { (yyval.unary_operator) = UnaryOperator::parse((yyvsp[(1) - (1)].op_bnot)); (yyval.unary_operator)->linenum = line_num; ;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 355 "ast/autogen.py"
    { (yyval.arith_operator) = ArithOperator::parse((yyvsp[(1) - (1)].op_plus)); (yyval.arith_operator)->linenum = line_num; ;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 356 "ast/autogen.py"
    { (yyval.arith_operator) = ArithOperator::parse((yyvsp[(1) - (1)].op_minus)); (yyval.arith_operator)->linenum = line_num; ;}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 358 "ast/autogen.py"
    { (yyval.comparison_operator) = ComparisonOperator::parse((yyvsp[(1) - (1)].comp_lt)); (yyval.comparison_operator)->linenum = line_num; ;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 359 "ast/autogen.py"
    { (yyval.comparison_operator) = ComparisonOperator::parse((yyvsp[(1) - (1)].comp_gt)); (yyval.comparison_operator)->linenum = line_num; ;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 360 "ast/autogen.py"
    { (yyval.comparison_operator) = ComparisonOperator::parse((yyvsp[(1) - (1)].comp_lt_eq)); (yyval.comparison_operator)->linenum = line_num; ;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 361 "ast/autogen.py"
    { (yyval.comparison_operator) = ComparisonOperator::parse((yyvsp[(1) - (1)].comp_gt_eq)); (yyval.comparison_operator)->linenum = line_num; ;}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 362 "ast/autogen.py"
    { (yyval.comparison_operator) = ComparisonOperator::parse((yyvsp[(1) - (1)].comp_eq)); (yyval.comparison_operator)->linenum = line_num; ;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 363 "ast/autogen.py"
    { (yyval.comparison_operator) = ComparisonOperator::parse((yyvsp[(1) - (1)].comp_not_eq)); (yyval.comparison_operator)->linenum = line_num; ;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 364 "ast/autogen.py"
    { (yyval.comparison_operator) = ComparisonOperator::parse((yyvsp[(1) - (1)].comp_in)); (yyval.comparison_operator)->linenum = line_num; ;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 365 "ast/autogen.py"
    { (yyval.comparison_operator) = ComparisonOperator::parse((yyvsp[(1) - (1)].comp_not_in)); (yyval.comparison_operator)->linenum = line_num; ;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 366 "ast/autogen.py"
    { (yyval.comparison_operator) = ComparisonOperator::parse((yyvsp[(1) - (1)].comp_is)); (yyval.comparison_operator)->linenum = line_num; ;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 367 "ast/autogen.py"
    { (yyval.comparison_operator) = ComparisonOperator::parse((yyvsp[(1) - (1)].comp_not_is)); (yyval.comparison_operator)->linenum = line_num; ;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 369 "ast/autogen.py"
    { (yyval.dotted_name) = DottedName::parse((yyvsp[(1) - (1)].t_name)); (yyval.dotted_name)->linenum = line_num; ;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 370 "ast/autogen.py"
    { (yyval.dotted_name) = DottedName::parse((yyvsp[(1) - (3)].dotted_name), (yyvsp[(2) - (3)].t_dot), (yyvsp[(3) - (3)].t_name)); (yyval.dotted_name)->linenum = line_num; ;}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 372 "ast/autogen.py"
    { (yyval.mult_operator) = MultOperator::parse((yyvsp[(1) - (1)].op_mult)); (yyval.mult_operator)->linenum = line_num; ;}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 373 "ast/autogen.py"
    { (yyval.mult_operator) = MultOperator::parse((yyvsp[(1) - (1)].op_divide)); (yyval.mult_operator)->linenum = line_num; ;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 374 "ast/autogen.py"
    { (yyval.mult_operator) = MultOperator::parse((yyvsp[(1) - (1)].op_trunc)); (yyval.mult_operator)->linenum = line_num; ;}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 375 "ast/autogen.py"
    { (yyval.mult_operator) = MultOperator::parse((yyvsp[(1) - (1)].op_mod)); (yyval.mult_operator)->linenum = line_num; ;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 377 "ast/autogen.py"
    { (yyval.parameter_list) = ParameterList::parse((yyvsp[(1) - (1)].parameter_list_args)); (yyval.parameter_list)->linenum = line_num; ;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 378 "ast/autogen.py"
    { (yyval.parameter_list) = ParameterList::parse((yyvsp[(1) - (1)].parameter_list_non_args)); (yyval.parameter_list)->linenum = line_num; ;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 379 "ast/autogen.py"
    { (yyval.parameter_list) = ParameterList::parse((yyvsp[(1) - (3)].parameter_list_non_args), (yyvsp[(2) - (3)].t_comma), (yyvsp[(3) - (3)].parameter_list_args)); (yyval.parameter_list)->linenum = line_num; ;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 381 "ast/autogen.py"
    { (yyval.parameter_list_args) = ParameterListArgs::parse((yyvsp[(1) - (1)].parameter_list_kwargs)); (yyval.parameter_list_args)->linenum = line_num; ;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 382 "ast/autogen.py"
    { (yyval.parameter_list_args) = ParameterListArgs::parse((yyvsp[(1) - (2)].t_multiply), (yyvsp[(2) - (2)].test_phrase)); (yyval.parameter_list_args)->linenum = line_num; ;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 383 "ast/autogen.py"
    { (yyval.parameter_list_args) = ParameterListArgs::parse((yyvsp[(1) - (4)].t_multiply), (yyvsp[(2) - (4)].test_phrase), (yyvsp[(3) - (4)].t_comma), (yyvsp[(4) - (4)].parameter_list_kwargs)); (yyval.parameter_list_args)->linenum = line_num; ;}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 385 "ast/autogen.py"
    { (yyval.parameter_phrase) = ParameterPhrase::parse((yyvsp[(1) - (1)].test_phrase)); (yyval.parameter_phrase)->linenum = line_num; ;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 386 "ast/autogen.py"
    { (yyval.parameter_phrase) = ParameterPhrase::parse((yyvsp[(1) - (3)].name_phrase), (yyvsp[(2) - (3)].t_assign), (yyvsp[(3) - (3)].test_phrase)); (yyval.parameter_phrase)->linenum = line_num; ;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 388 "ast/autogen.py"
    { (yyval.shift_operator) = ShiftOperator::parse((yyvsp[(1) - (1)].op_left_shift)); (yyval.shift_operator)->linenum = line_num; ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 389 "ast/autogen.py"
    { (yyval.shift_operator) = ShiftOperator::parse((yyvsp[(1) - (1)].op_right_shift)); (yyval.shift_operator)->linenum = line_num; ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 391 "ast/autogen.py"
    { (yyval.single_input) = SingleInput::parse((yyvsp[(1) - (1)].t_newline)); (yyval.single_input)->linenum = line_num; ;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 392 "ast/autogen.py"
    { (yyval.single_input) = SingleInput::parse((yyvsp[(1) - (2)].simple_statement), (yyvsp[(2) - (2)].t_newline)); (yyval.single_input)->linenum = line_num; ;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 393 "ast/autogen.py"
    { (yyval.single_input) = SingleInput::parse((yyvsp[(1) - (1)].if_statement)); (yyval.single_input)->linenum = line_num; ;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 394 "ast/autogen.py"
    { (yyval.single_input) = SingleInput::parse((yyvsp[(1) - (1)].while_statement)); (yyval.single_input)->linenum = line_num; ;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 395 "ast/autogen.py"
    { (yyval.single_input) = SingleInput::parse((yyvsp[(1) - (1)].function_definition)); (yyval.single_input)->linenum = line_num; ;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 397 "ast/autogen.py"
    { (yyval.slice_list) = SliceList::parse((yyvsp[(1) - (1)].slice_phrase)); (yyval.slice_list)->linenum = line_num; ;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 398 "ast/autogen.py"
    { (yyval.slice_list) = SliceList::parse((yyvsp[(1) - (3)].slice_list), (yyvsp[(2) - (3)].t_comma), (yyvsp[(3) - (3)].slice_phrase)); (yyval.slice_list)->linenum = line_num; ;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 400 "ast/autogen.py"
    { (yyval.slice_phrase) = SlicePhrase::parse((yyvsp[(1) - (1)].test_phrase)); (yyval.slice_phrase)->linenum = line_num; ;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 401 "ast/autogen.py"
    { (yyval.slice_phrase) = SlicePhrase::parse((yyvsp[(1) - (3)].t_dot), (yyvsp[(2) - (3)].t_dot), (yyvsp[(3) - (3)].t_dot)); (yyval.slice_phrase)->linenum = line_num; ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 402 "ast/autogen.py"
    { (yyval.slice_phrase) = SlicePhrase::parse((yyvsp[(1) - (3)].test_phrase_optional), (yyvsp[(2) - (3)].t_colon), (yyvsp[(3) - (3)].test_phrase_optional)); (yyval.slice_phrase)->linenum = line_num; ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 403 "ast/autogen.py"
    { (yyval.slice_phrase) = SlicePhrase::parse((yyvsp[(1) - (5)].test_phrase_optional), (yyvsp[(2) - (5)].t_colon), (yyvsp[(3) - (5)].test_phrase_optional), (yyvsp[(4) - (5)].t_colon), (yyvsp[(5) - (5)].test_phrase_optional)); (yyval.slice_phrase)->linenum = line_num; ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 405 "ast/autogen.py"
    { (yyval.small_statement) = SmallStatement::parse((yyvsp[(1) - (1)].print_statement)); (yyval.small_statement)->linenum = line_num; ;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 406 "ast/autogen.py"
    { (yyval.small_statement) = SmallStatement::parse((yyvsp[(1) - (1)].import_statement)); (yyval.small_statement)->linenum = line_num; ;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 407 "ast/autogen.py"
    { (yyval.small_statement) = SmallStatement::parse((yyvsp[(1) - (1)].delete_statement)); (yyval.small_statement)->linenum = line_num; ;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 408 "ast/autogen.py"
    { (yyval.small_statement) = SmallStatement::parse((yyvsp[(1) - (1)].break_statement)); (yyval.small_statement)->linenum = line_num; ;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 409 "ast/autogen.py"
    { (yyval.small_statement) = SmallStatement::parse((yyvsp[(1) - (1)].continue_statement)); (yyval.small_statement)->linenum = line_num; ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 410 "ast/autogen.py"
    { (yyval.small_statement) = SmallStatement::parse((yyvsp[(1) - (1)].pass_statement)); (yyval.small_statement)->linenum = line_num; ;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 411 "ast/autogen.py"
    { (yyval.small_statement) = SmallStatement::parse((yyvsp[(1) - (1)].global_statement)); (yyval.small_statement)->linenum = line_num; ;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 412 "ast/autogen.py"
    { (yyval.small_statement) = SmallStatement::parse((yyvsp[(1) - (1)].assign_statement)); (yyval.small_statement)->linenum = line_num; ;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 413 "ast/autogen.py"
    { (yyval.small_statement) = SmallStatement::parse((yyvsp[(1) - (1)].test_statement)); (yyval.small_statement)->linenum = line_num; ;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 414 "ast/autogen.py"
    { (yyval.small_statement) = SmallStatement::parse((yyvsp[(1) - (1)].return_statement)); (yyval.small_statement)->linenum = line_num; ;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 416 "ast/autogen.py"
    { (yyval.test_statement) = TestStatement::parse((yyvsp[(1) - (1)].test_phrase)); (yyval.test_statement)->linenum = line_num; ;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 417 "ast/autogen.py"
    { (yyval.test_statement) = TestStatement::parse((yyvsp[(1) - (2)].test_list_non_trailing), (yyvsp[(2) - (2)].t_comma)); (yyval.test_statement)->linenum = line_num; ;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 418 "ast/autogen.py"
    { (yyval.test_statement) = TestStatement::parse((yyvsp[(1) - (3)].test_list_non_trailing), (yyvsp[(2) - (3)].t_comma), (yyvsp[(3) - (3)].test_phrase)); (yyval.test_statement)->linenum = line_num; ;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 420 "ast/autogen.py"
    { (yyval.while_statement) = WhileStatement::parse((yyvsp[(1) - (4)].t_while), (yyvsp[(2) - (4)].test_phrase), (yyvsp[(3) - (4)].t_colon), (yyvsp[(4) - (4)].suite)); (yyval.while_statement)->linenum = line_num; ;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 422 "ast/autogen.py"
    { (yyval.assign_statement) = AssignStatement::parse((yyvsp[(1) - (3)].test_statement), (yyvsp[(2) - (3)].t_assign), (yyvsp[(3) - (3)].test_statement)); (yyval.assign_statement)->linenum = line_num; ;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 424 "ast/autogen.py"
    { (yyval.break_statement) = BreakStatement::parse((yyvsp[(1) - (1)].t_break)); (yyval.break_statement)->linenum = line_num; ;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 426 "ast/autogen.py"
    { (yyval.comp_eq) = CompEq::parse((yyvsp[(1) - (1)].t_eq)); (yyval.comp_eq)->linenum = line_num; ;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 428 "ast/autogen.py"
    { (yyval.comp_gt) = CompGt::parse((yyvsp[(1) - (1)].t_gt)); (yyval.comp_gt)->linenum = line_num; ;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 430 "ast/autogen.py"
    { (yyval.comp_gt_eq) = CompGtEq::parse((yyvsp[(1) - (1)].t_gteq)); (yyval.comp_gt_eq)->linenum = line_num; ;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 432 "ast/autogen.py"
    { (yyval.comp_in) = CompIn::parse((yyvsp[(1) - (1)].t_in)); (yyval.comp_in)->linenum = line_num; ;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 434 "ast/autogen.py"
    { (yyval.comp_is) = CompIs::parse((yyvsp[(1) - (1)].t_is)); (yyval.comp_is)->linenum = line_num; ;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 436 "ast/autogen.py"
    { (yyval.comp_lt) = CompLt::parse((yyvsp[(1) - (1)].t_lt)); (yyval.comp_lt)->linenum = line_num; ;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 438 "ast/autogen.py"
    { (yyval.comp_lt_eq) = CompLtEq::parse((yyvsp[(1) - (1)].t_lteq)); (yyval.comp_lt_eq)->linenum = line_num; ;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 440 "ast/autogen.py"
    { (yyval.comp_not_eq) = CompNotEq::parse((yyvsp[(1) - (1)].t_noteq)); (yyval.comp_not_eq)->linenum = line_num; ;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 442 "ast/autogen.py"
    { (yyval.comp_not_in) = CompNotIn::parse((yyvsp[(1) - (2)].t_not), (yyvsp[(2) - (2)].t_in)); (yyval.comp_not_in)->linenum = line_num; ;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 444 "ast/autogen.py"
    { (yyval.comp_not_is) = CompNotIs::parse((yyvsp[(1) - (2)].t_is), (yyvsp[(2) - (2)].t_not)); (yyval.comp_not_is)->linenum = line_num; ;}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 446 "ast/autogen.py"
    { (yyval.continue_statement) = ContinueStatement::parse((yyvsp[(1) - (1)].t_continue)); (yyval.continue_statement)->linenum = line_num; ;}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 448 "ast/autogen.py"
    { (yyval.delete_statement) = DeleteStatement::parse((yyvsp[(1) - (2)].t_del), (yyvsp[(2) - (2)].test_list)); (yyval.delete_statement)->linenum = line_num; ;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 450 "ast/autogen.py"
    { (yyval.function_definition) = FunctionDefinition::parse((yyvsp[(1) - (7)].t_def), (yyvsp[(2) - (7)].name_phrase), (yyvsp[(3) - (7)].t_open_curved), (yyvsp[(4) - (7)].parameter_list), (yyvsp[(5) - (7)].t_close_curved), (yyvsp[(6) - (7)].t_colon), (yyvsp[(7) - (7)].suite)); (yyval.function_definition)->linenum = line_num; ;}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 452 "ast/autogen.py"
    { (yyval.global_statement) = GlobalStatement::parse((yyvsp[(1) - (2)].t_global), (yyvsp[(2) - (2)].name_phrase)); (yyval.global_statement)->linenum = line_num; ;}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 453 "ast/autogen.py"
    { (yyval.global_statement) = GlobalStatement::parse((yyvsp[(1) - (3)].global_statement), (yyvsp[(2) - (3)].t_comma), (yyvsp[(3) - (3)].name_phrase)); (yyval.global_statement)->linenum = line_num; ;}
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 455 "ast/autogen.py"
    { (yyval.if_statement) = IfStatement::parse((yyvsp[(1) - (4)].t_if), (yyvsp[(2) - (4)].test_phrase), (yyvsp[(3) - (4)].t_colon), (yyvsp[(4) - (4)].suite)); (yyval.if_statement)->linenum = line_num; ;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 456 "ast/autogen.py"
    { (yyval.if_statement) = IfStatement::parse((yyvsp[(1) - (4)].if_statement), (yyvsp[(2) - (4)].t_else), (yyvsp[(3) - (4)].t_colon), (yyvsp[(4) - (4)].suite)); (yyval.if_statement)->linenum = line_num; ;}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 458 "ast/autogen.py"
    { (yyval.import_statement) = ImportStatement::parse((yyvsp[(1) - (2)].t_import), (yyvsp[(2) - (2)].dotted_as_names)); (yyval.import_statement)->linenum = line_num; ;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 459 "ast/autogen.py"
    { (yyval.import_statement) = ImportStatement::parse((yyvsp[(1) - (4)].t_from), (yyvsp[(2) - (4)].dotted_name), (yyvsp[(3) - (4)].t_import), (yyvsp[(4) - (4)].import_as_names)); (yyval.import_statement)->linenum = line_num; ;}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 460 "ast/autogen.py"
    { (yyval.import_statement) = ImportStatement::parse((yyvsp[(1) - (6)].t_from), (yyvsp[(2) - (6)].dotted_name), (yyvsp[(3) - (6)].t_import), (yyvsp[(4) - (6)].t_open_curved), (yyvsp[(5) - (6)].import_as_names), (yyvsp[(6) - (6)].t_close_curved)); (yyval.import_statement)->linenum = line_num; ;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 461 "ast/autogen.py"
    { (yyval.import_statement) = ImportStatement::parse((yyvsp[(1) - (7)].t_from), (yyvsp[(2) - (7)].dotted_name), (yyvsp[(3) - (7)].t_import), (yyvsp[(4) - (7)].t_open_curved), (yyvsp[(5) - (7)].import_as_names), (yyvsp[(6) - (7)].t_comma), (yyvsp[(7) - (7)].t_close_curved)); (yyval.import_statement)->linenum = line_num; ;}
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 463 "ast/autogen.py"
    { (yyval.op_band) = OpBand::parse((yyvsp[(1) - (1)].t_band)); (yyval.op_band)->linenum = line_num; ;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 465 "ast/autogen.py"
    { (yyval.op_bnot) = OpBnot::parse((yyvsp[(1) - (1)].t_bnot)); (yyval.op_bnot)->linenum = line_num; ;}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 467 "ast/autogen.py"
    { (yyval.op_bor) = OpBor::parse((yyvsp[(1) - (1)].t_bor)); (yyval.op_bor)->linenum = line_num; ;}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 469 "ast/autogen.py"
    { (yyval.op_bxor) = OpBxor::parse((yyvsp[(1) - (1)].t_bxor)); (yyval.op_bxor)->linenum = line_num; ;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 471 "ast/autogen.py"
    { (yyval.op_divide) = OpDivide::parse((yyvsp[(1) - (1)].t_divide)); (yyval.op_divide)->linenum = line_num; ;}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 473 "ast/autogen.py"
    { (yyval.op_left_shift) = OpLeftShift::parse((yyvsp[(1) - (1)].t_leftshift)); (yyval.op_left_shift)->linenum = line_num; ;}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 475 "ast/autogen.py"
    { (yyval.op_minus) = OpMinus::parse((yyvsp[(1) - (1)].t_minus)); (yyval.op_minus)->linenum = line_num; ;}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 477 "ast/autogen.py"
    { (yyval.op_mod) = OpMod::parse((yyvsp[(1) - (1)].t_modulus)); (yyval.op_mod)->linenum = line_num; ;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 479 "ast/autogen.py"
    { (yyval.op_mult) = OpMult::parse((yyvsp[(1) - (1)].t_multiply)); (yyval.op_mult)->linenum = line_num; ;}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 481 "ast/autogen.py"
    { (yyval.op_negative) = OpNegative::parse((yyvsp[(1) - (1)].t_minus)); (yyval.op_negative)->linenum = line_num; ;}
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 483 "ast/autogen.py"
    { (yyval.op_plus) = OpPlus::parse((yyvsp[(1) - (1)].t_plus)); (yyval.op_plus)->linenum = line_num; ;}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 485 "ast/autogen.py"
    { (yyval.op_positive) = OpPositive::parse((yyvsp[(1) - (1)].t_plus)); (yyval.op_positive)->linenum = line_num; ;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 487 "ast/autogen.py"
    { (yyval.op_power) = OpPower::parse((yyvsp[(1) - (1)].t_power)); (yyval.op_power)->linenum = line_num; ;}
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 489 "ast/autogen.py"
    { (yyval.op_right_shift) = OpRightShift::parse((yyvsp[(1) - (1)].t_rightshift)); (yyval.op_right_shift)->linenum = line_num; ;}
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 491 "ast/autogen.py"
    { (yyval.op_trunc) = OpTrunc::parse((yyvsp[(1) - (1)].t_trunc_divide)); (yyval.op_trunc)->linenum = line_num; ;}
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 493 "ast/autogen.py"
    { (yyval.parameter_list_kwargs) = ParameterListKwargs::parse(); (yyval.parameter_list_kwargs)->linenum = line_num; ;}
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 494 "ast/autogen.py"
    { (yyval.parameter_list_kwargs) = ParameterListKwargs::parse((yyvsp[(1) - (2)].t_power), (yyvsp[(2) - (2)].test_phrase)); (yyval.parameter_list_kwargs)->linenum = line_num; ;}
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 495 "ast/autogen.py"
    { (yyval.parameter_list_kwargs) = ParameterListKwargs::parse((yyvsp[(1) - (3)].t_power), (yyvsp[(2) - (3)].test_phrase), (yyvsp[(3) - (3)].t_comma)); (yyval.parameter_list_kwargs)->linenum = line_num; ;}
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 497 "ast/autogen.py"
    { (yyval.parameter_list_non_args) = ParameterListNonArgs::parse((yyvsp[(1) - (1)].parameter_phrase)); (yyval.parameter_list_non_args)->linenum = line_num; ;}
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 498 "ast/autogen.py"
    { (yyval.parameter_list_non_args) = ParameterListNonArgs::parse((yyvsp[(1) - (3)].parameter_list_non_args), (yyvsp[(2) - (3)].t_comma), (yyvsp[(3) - (3)].parameter_phrase)); (yyval.parameter_list_non_args)->linenum = line_num; ;}
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 500 "ast/autogen.py"
    { (yyval.pass_statement) = PassStatement::parse((yyvsp[(1) - (1)].t_pass)); (yyval.pass_statement)->linenum = line_num; ;}
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 502 "ast/autogen.py"
    { (yyval.print_statement) = PrintStatement::parse((yyvsp[(1) - (2)].t_print), (yyvsp[(2) - (2)].test_list)); (yyval.print_statement)->linenum = line_num; ;}
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 503 "ast/autogen.py"
    { (yyval.print_statement) = PrintStatement::parse((yyvsp[(1) - (3)].t_print), (yyvsp[(2) - (3)].t_rightshift), (yyvsp[(3) - (3)].test_phrase)); (yyval.print_statement)->linenum = line_num; ;}
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 504 "ast/autogen.py"
    { (yyval.print_statement) = PrintStatement::parse((yyvsp[(1) - (5)].t_print), (yyvsp[(2) - (5)].t_rightshift), (yyvsp[(3) - (5)].test_phrase), (yyvsp[(4) - (5)].t_comma), (yyvsp[(5) - (5)].test_list_non_empty)); (yyval.print_statement)->linenum = line_num; ;}
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 506 "ast/autogen.py"
    { (yyval.return_statement) = ReturnStatement::parse((yyvsp[(1) - (2)].t_return), (yyvsp[(2) - (2)].test_list)); (yyval.return_statement)->linenum = line_num; ;}
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 508 "ast/autogen.py"
    { (yyval.suite) = Suite::parse((yyvsp[(1) - (2)].simple_statement), (yyvsp[(2) - (2)].t_newline)); (yyval.suite)->linenum = line_num; ;}
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 509 "ast/autogen.py"
    { (yyval.suite) = Suite::parse((yyvsp[(1) - (4)].t_newline), (yyvsp[(2) - (4)].t_indent), (yyvsp[(3) - (4)].suite_body), (yyvsp[(4) - (4)].t_outdent)); (yyval.suite)->linenum = line_num; ;}
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 511 "ast/autogen.py"
    { (yyval.test_phrase) = TestPhrase::parse((yyvsp[(1) - (1)].or_phrase)); (yyval.test_phrase)->linenum = line_num; ;}
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 512 "ast/autogen.py"
    { (yyval.test_phrase) = TestPhrase::parse((yyvsp[(1) - (2)].or_phrase), (yyvsp[(2) - (2)].inline_if_phrase)); (yyval.test_phrase)->linenum = line_num; ;}
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 514 "ast/autogen.py"
    { (yyval.dotted_as_names) = DottedAsNames::parse((yyvsp[(1) - (1)].dotted_name)); (yyval.dotted_as_names)->linenum = line_num; ;}
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 515 "ast/autogen.py"
    { (yyval.dotted_as_names) = DottedAsNames::parse((yyvsp[(1) - (3)].dotted_name), (yyvsp[(2) - (3)].t_as), (yyvsp[(3) - (3)].t_name)); (yyval.dotted_as_names)->linenum = line_num; ;}
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 516 "ast/autogen.py"
    { (yyval.dotted_as_names) = DottedAsNames::parse((yyvsp[(1) - (3)].dotted_as_names), (yyvsp[(2) - (3)].t_comma), (yyvsp[(3) - (3)].dotted_name)); (yyval.dotted_as_names)->linenum = line_num; ;}
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 517 "ast/autogen.py"
    { (yyval.dotted_as_names) = DottedAsNames::parse((yyvsp[(1) - (5)].dotted_as_names), (yyvsp[(2) - (5)].t_comma), (yyvsp[(3) - (5)].dotted_name), (yyvsp[(4) - (5)].t_as), (yyvsp[(5) - (5)].t_name)); (yyval.dotted_as_names)->linenum = line_num; ;}
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 519 "ast/autogen.py"
    { (yyval.import_as_names) = ImportAsNames::parse((yyvsp[(1) - (1)].t_name)); (yyval.import_as_names)->linenum = line_num; ;}
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 520 "ast/autogen.py"
    { (yyval.import_as_names) = ImportAsNames::parse((yyvsp[(1) - (3)].t_name), (yyvsp[(2) - (3)].t_as), (yyvsp[(3) - (3)].t_name)); (yyval.import_as_names)->linenum = line_num; ;}
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 521 "ast/autogen.py"
    { (yyval.import_as_names) = ImportAsNames::parse((yyvsp[(1) - (3)].import_as_names), (yyvsp[(2) - (3)].t_comma), (yyvsp[(3) - (3)].t_name)); (yyval.import_as_names)->linenum = line_num; ;}
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 522 "ast/autogen.py"
    { (yyval.import_as_names) = ImportAsNames::parse((yyvsp[(1) - (5)].import_as_names), (yyvsp[(2) - (5)].t_comma), (yyvsp[(3) - (5)].t_name), (yyvsp[(4) - (5)].t_as), (yyvsp[(5) - (5)].t_name)); (yyval.import_as_names)->linenum = line_num; ;}
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 524 "ast/autogen.py"
    { (yyval.suite_body) = SuiteBody::parse((yyvsp[(1) - (1)].single_input)); (yyval.suite_body)->linenum = line_num; ;}
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 525 "ast/autogen.py"
    { (yyval.suite_body) = SuiteBody::parse((yyvsp[(1) - (2)].suite_body), (yyvsp[(2) - (2)].single_input)); (yyval.suite_body)->linenum = line_num; ;}
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 527 "ast/autogen.py"
    { (yyval.test_list) = TestList::parse(); (yyval.test_list)->linenum = line_num; ;}
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 528 "ast/autogen.py"
    { (yyval.test_list) = TestList::parse((yyvsp[(1) - (1)].test_list_non_empty)); (yyval.test_list)->linenum = line_num; ;}
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 530 "ast/autogen.py"
    { (yyval.test_list_non_empty) = TestListNonEmpty::parse((yyvsp[(1) - (1)].test_list_non_trailing)); (yyval.test_list_non_empty)->linenum = line_num; ;}
    break;

  case 129:

/* Line 1464 of yacc.c  */
#line 531 "ast/autogen.py"
    { (yyval.test_list_non_empty) = TestListNonEmpty::parse((yyvsp[(1) - (2)].test_list_non_trailing), (yyvsp[(2) - (2)].t_comma)); (yyval.test_list_non_empty)->linenum = line_num; ;}
    break;

  case 130:

/* Line 1464 of yacc.c  */
#line 533 "ast/autogen.py"
    { (yyval.inline_if_phrase) = InlineIfPhrase::parse((yyvsp[(1) - (4)].t_if), (yyvsp[(2) - (4)].or_phrase), (yyvsp[(3) - (4)].t_else), (yyvsp[(4) - (4)].test_phrase)); (yyval.inline_if_phrase)->linenum = line_num; ;}
    break;

  case 131:

/* Line 1464 of yacc.c  */
#line 535 "ast/autogen.py"
    { (yyval.or_phrase) = OrPhrase::parse((yyvsp[(1) - (1)].and_phrase)); (yyval.or_phrase)->linenum = line_num; ;}
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 536 "ast/autogen.py"
    { (yyval.or_phrase) = OrPhrase::parse((yyvsp[(1) - (3)].or_phrase), (yyvsp[(2) - (3)].t_or), (yyvsp[(3) - (3)].and_phrase)); (yyval.or_phrase)->linenum = line_num; ;}
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 538 "ast/autogen.py"
    { (yyval.simple_statement) = SimpleStatement::parse((yyvsp[(1) - (1)].small_statement)); (yyval.simple_statement)->linenum = line_num; ;}
    break;

  case 134:

/* Line 1464 of yacc.c  */
#line 539 "ast/autogen.py"
    { (yyval.simple_statement) = SimpleStatement::parse((yyvsp[(1) - (2)].simple_statement), (yyvsp[(2) - (2)].t_semicolon)); (yyval.simple_statement)->linenum = line_num; ;}
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 540 "ast/autogen.py"
    { (yyval.simple_statement) = SimpleStatement::parse((yyvsp[(1) - (3)].simple_statement), (yyvsp[(2) - (3)].t_semicolon), (yyvsp[(3) - (3)].small_statement)); (yyval.simple_statement)->linenum = line_num; ;}
    break;

  case 136:

/* Line 1464 of yacc.c  */
#line 542 "ast/autogen.py"
    { (yyval.test_list_non_trailing) = TestListNonTrailing::parse((yyvsp[(1) - (1)].test_phrase)); (yyval.test_list_non_trailing)->linenum = line_num; ;}
    break;

  case 137:

/* Line 1464 of yacc.c  */
#line 543 "ast/autogen.py"
    { (yyval.test_list_non_trailing) = TestListNonTrailing::parse((yyvsp[(1) - (3)].test_list_non_trailing), (yyvsp[(2) - (3)].t_comma), (yyvsp[(3) - (3)].test_phrase)); (yyval.test_list_non_trailing)->linenum = line_num; ;}
    break;

  case 138:

/* Line 1464 of yacc.c  */
#line 545 "ast/autogen.py"
    { (yyval.and_phrase) = AndPhrase::parse((yyvsp[(1) - (1)].not_phrase)); (yyval.and_phrase)->linenum = line_num; ;}
    break;

  case 139:

/* Line 1464 of yacc.c  */
#line 546 "ast/autogen.py"
    { (yyval.and_phrase) = AndPhrase::parse((yyvsp[(1) - (3)].and_phrase), (yyvsp[(2) - (3)].t_and), (yyvsp[(3) - (3)].not_phrase)); (yyval.and_phrase)->linenum = line_num; ;}
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 548 "ast/autogen.py"
    { (yyval.not_phrase) = NotPhrase::parse((yyvsp[(1) - (1)].comparison_phrase)); (yyval.not_phrase)->linenum = line_num; ;}
    break;

  case 141:

/* Line 1464 of yacc.c  */
#line 549 "ast/autogen.py"
    { (yyval.not_phrase) = NotPhrase::parse((yyvsp[(1) - (2)].t_not), (yyvsp[(2) - (2)].not_phrase)); (yyval.not_phrase)->linenum = line_num; ;}
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 551 "ast/autogen.py"
    { (yyval.comparison_phrase) = ComparisonPhrase::parse((yyvsp[(1) - (1)].expression)); (yyval.comparison_phrase)->linenum = line_num; ;}
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 552 "ast/autogen.py"
    { (yyval.comparison_phrase) = ComparisonPhrase::parse((yyvsp[(1) - (1)].comparison_list)); (yyval.comparison_phrase)->linenum = line_num; ;}
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 554 "ast/autogen.py"
    { (yyval.comparison_list) = ComparisonList::parse((yyvsp[(1) - (3)].expression), (yyvsp[(2) - (3)].comparison_operator), (yyvsp[(3) - (3)].expression)); (yyval.comparison_list)->linenum = line_num; ;}
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 555 "ast/autogen.py"
    { (yyval.comparison_list) = ComparisonList::parse((yyvsp[(1) - (3)].comparison_list), (yyvsp[(2) - (3)].comparison_operator), (yyvsp[(3) - (3)].expression)); (yyval.comparison_list)->linenum = line_num; ;}
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 557 "ast/autogen.py"
    { (yyval.expression) = Expression::parse((yyvsp[(1) - (1)].xor_expression)); (yyval.expression)->linenum = line_num; ;}
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 558 "ast/autogen.py"
    { (yyval.expression) = Expression::parse((yyvsp[(1) - (3)].xor_expression), (yyvsp[(2) - (3)].op_bor), (yyvsp[(3) - (3)].expression)); (yyval.expression)->linenum = line_num; ;}
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 560 "ast/autogen.py"
    { (yyval.xor_expression) = XorExpression::parse((yyvsp[(1) - (1)].and_expression)); (yyval.xor_expression)->linenum = line_num; ;}
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 561 "ast/autogen.py"
    { (yyval.xor_expression) = XorExpression::parse((yyvsp[(1) - (3)].and_expression), (yyvsp[(2) - (3)].op_bxor), (yyvsp[(3) - (3)].xor_expression)); (yyval.xor_expression)->linenum = line_num; ;}
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 563 "ast/autogen.py"
    { (yyval.and_expression) = AndExpression::parse((yyvsp[(1) - (1)].shift_expression)); (yyval.and_expression)->linenum = line_num; ;}
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 564 "ast/autogen.py"
    { (yyval.and_expression) = AndExpression::parse((yyvsp[(1) - (3)].shift_expression), (yyvsp[(2) - (3)].op_band), (yyvsp[(3) - (3)].and_expression)); (yyval.and_expression)->linenum = line_num; ;}
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 566 "ast/autogen.py"
    { (yyval.shift_expression) = ShiftExpression::parse((yyvsp[(1) - (1)].arith_expression)); (yyval.shift_expression)->linenum = line_num; ;}
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 567 "ast/autogen.py"
    { (yyval.shift_expression) = ShiftExpression::parse((yyvsp[(1) - (3)].shift_expression), (yyvsp[(2) - (3)].shift_operator), (yyvsp[(3) - (3)].arith_expression)); (yyval.shift_expression)->linenum = line_num; ;}
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 569 "ast/autogen.py"
    { (yyval.arith_expression) = ArithExpression::parse((yyvsp[(1) - (1)].mult_expression)); (yyval.arith_expression)->linenum = line_num; ;}
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 570 "ast/autogen.py"
    { (yyval.arith_expression) = ArithExpression::parse((yyvsp[(1) - (3)].arith_expression), (yyvsp[(2) - (3)].arith_operator), (yyvsp[(3) - (3)].mult_expression)); (yyval.arith_expression)->linenum = line_num; ;}
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 572 "ast/autogen.py"
    { (yyval.mult_expression) = MultExpression::parse((yyvsp[(1) - (1)].fact_expression)); (yyval.mult_expression)->linenum = line_num; ;}
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 573 "ast/autogen.py"
    { (yyval.mult_expression) = MultExpression::parse((yyvsp[(1) - (3)].mult_expression), (yyvsp[(2) - (3)].mult_operator), (yyvsp[(3) - (3)].fact_expression)); (yyval.mult_expression)->linenum = line_num; ;}
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 575 "ast/autogen.py"
    { (yyval.fact_expression) = FactExpression::parse((yyvsp[(1) - (1)].unary_phrase)); (yyval.fact_expression)->linenum = line_num; ;}
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 576 "ast/autogen.py"
    { (yyval.fact_expression) = FactExpression::parse((yyvsp[(1) - (3)].unary_phrase), (yyvsp[(2) - (3)].op_power), (yyvsp[(3) - (3)].fact_expression)); (yyval.fact_expression)->linenum = line_num; ;}
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 578 "ast/autogen.py"
    { (yyval.unary_phrase) = UnaryPhrase::parse((yyvsp[(1) - (1)].base_phrase)); (yyval.unary_phrase)->linenum = line_num; ;}
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 579 "ast/autogen.py"
    { (yyval.unary_phrase) = UnaryPhrase::parse((yyvsp[(1) - (2)].unary_operator), (yyvsp[(2) - (2)].unary_phrase)); (yyval.unary_phrase)->linenum = line_num; ;}
    break;

  case 162:

/* Line 1464 of yacc.c  */
#line 581 "ast/autogen.py"
    { (yyval.base_phrase) = BasePhrase::parse((yyvsp[(1) - (1)].name_phrase)); (yyval.base_phrase)->linenum = line_num; ;}
    break;

  case 163:

/* Line 1464 of yacc.c  */
#line 582 "ast/autogen.py"
    { (yyval.base_phrase) = BasePhrase::parse((yyvsp[(1) - (1)].get_item)); (yyval.base_phrase)->linenum = line_num; ;}
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 583 "ast/autogen.py"
    { (yyval.base_phrase) = BasePhrase::parse((yyvsp[(1) - (1)].get_attr)); (yyval.base_phrase)->linenum = line_num; ;}
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 584 "ast/autogen.py"
    { (yyval.base_phrase) = BasePhrase::parse((yyvsp[(1) - (1)].function_call)); (yyval.base_phrase)->linenum = line_num; ;}
    break;

  case 166:

/* Line 1464 of yacc.c  */
#line 585 "ast/autogen.py"
    { (yyval.base_phrase) = BasePhrase::parse((yyvsp[(1) - (1)].list_maker)); (yyval.base_phrase)->linenum = line_num; ;}
    break;

  case 167:

/* Line 1464 of yacc.c  */
#line 586 "ast/autogen.py"
    { (yyval.base_phrase) = BasePhrase::parse((yyvsp[(1) - (1)].tuple_maker)); (yyval.base_phrase)->linenum = line_num; ;}
    break;

  case 168:

/* Line 1464 of yacc.c  */
#line 587 "ast/autogen.py"
    { (yyval.base_phrase) = BasePhrase::parse((yyvsp[(1) - (1)].repr_phrase)); (yyval.base_phrase)->linenum = line_num; ;}
    break;

  case 169:

/* Line 1464 of yacc.c  */
#line 588 "ast/autogen.py"
    { (yyval.base_phrase) = BasePhrase::parse((yyvsp[(1) - (1)].test_phrase_bracketed)); (yyval.base_phrase)->linenum = line_num; ;}
    break;

  case 170:

/* Line 1464 of yacc.c  */
#line 589 "ast/autogen.py"
    { (yyval.base_phrase) = BasePhrase::parse((yyvsp[(1) - (1)].value_int)); (yyval.base_phrase)->linenum = line_num; ;}
    break;

  case 171:

/* Line 1464 of yacc.c  */
#line 590 "ast/autogen.py"
    { (yyval.base_phrase) = BasePhrase::parse((yyvsp[(1) - (1)].value_float)); (yyval.base_phrase)->linenum = line_num; ;}
    break;

  case 172:

/* Line 1464 of yacc.c  */
#line 591 "ast/autogen.py"
    { (yyval.base_phrase) = BasePhrase::parse((yyvsp[(1) - (1)].value_string)); (yyval.base_phrase)->linenum = line_num; ;}
    break;

  case 173:

/* Line 1464 of yacc.c  */
#line 593 "ast/autogen.py"
    { (yyval.test_phrase_bracketed) = TestPhraseBracketed::parse((yyvsp[(1) - (3)].t_open_curved), (yyvsp[(2) - (3)].test_phrase), (yyvsp[(3) - (3)].t_close_curved)); (yyval.test_phrase_bracketed)->linenum = line_num; ;}
    break;

  case 174:

/* Line 1464 of yacc.c  */
#line 595 "ast/autogen.py"
    { (yyval.tuple_maker) = TupleMaker::parse((yyvsp[(1) - (5)].t_open_curved), (yyvsp[(2) - (5)].test_list_non_trailing), (yyvsp[(3) - (5)].t_comma), (yyvsp[(4) - (5)].test_phrase), (yyvsp[(5) - (5)].t_close_curved)); (yyval.tuple_maker)->linenum = line_num; ;}
    break;

  case 175:

/* Line 1464 of yacc.c  */
#line 596 "ast/autogen.py"
    { (yyval.tuple_maker) = TupleMaker::parse((yyvsp[(1) - (4)].t_open_curved), (yyvsp[(2) - (4)].test_list_non_trailing), (yyvsp[(3) - (4)].t_comma), (yyvsp[(4) - (4)].t_close_curved)); (yyval.tuple_maker)->linenum = line_num; ;}
    break;

  case 176:

/* Line 1464 of yacc.c  */
#line 598 "ast/autogen.py"
    { (yyval.value_float) = ValueFloat::parse((yyvsp[(1) - (1)].t_float)); (yyval.value_float)->linenum = line_num; ;}
    break;

  case 177:

/* Line 1464 of yacc.c  */
#line 600 "ast/autogen.py"
    { (yyval.value_int) = ValueInt::parse((yyvsp[(1) - (1)].t_integer)); (yyval.value_int)->linenum = line_num; ;}
    break;

  case 178:

/* Line 1464 of yacc.c  */
#line 602 "ast/autogen.py"
    { (yyval.value_string) = ValueString::parse((yyvsp[(1) - (1)].t_string)); (yyval.value_string)->linenum = line_num; ;}
    break;

  case 179:

/* Line 1464 of yacc.c  */
#line 604 "ast/autogen.py"
    { (yyval.function_call) = FunctionCall::parse((yyvsp[(1) - (4)].base_phrase), (yyvsp[(2) - (4)].t_open_curved), (yyvsp[(3) - (4)].parameter_list), (yyvsp[(4) - (4)].t_close_curved)); (yyval.function_call)->linenum = line_num; ;}
    break;

  case 180:

/* Line 1464 of yacc.c  */
#line 606 "ast/autogen.py"
    { (yyval.get_attr) = GetAttr::parse((yyvsp[(1) - (3)].base_phrase), (yyvsp[(2) - (3)].t_dot), (yyvsp[(3) - (3)].name_phrase)); (yyval.get_attr)->linenum = line_num; ;}
    break;

  case 181:

/* Line 1464 of yacc.c  */
#line 608 "ast/autogen.py"
    { (yyval.get_item) = GetItem::parse((yyvsp[(1) - (4)].base_phrase), (yyvsp[(2) - (4)].t_open_square), (yyvsp[(3) - (4)].slice_list), (yyvsp[(4) - (4)].t_close_square)); (yyval.get_item)->linenum = line_num; ;}
    break;

  case 182:

/* Line 1464 of yacc.c  */
#line 609 "ast/autogen.py"
    { (yyval.get_item) = GetItem::parse((yyvsp[(1) - (5)].base_phrase), (yyvsp[(2) - (5)].t_open_square), (yyvsp[(3) - (5)].slice_list), (yyvsp[(4) - (5)].t_comma), (yyvsp[(5) - (5)].t_close_square)); (yyval.get_item)->linenum = line_num; ;}
    break;

  case 183:

/* Line 1464 of yacc.c  */
#line 611 "ast/autogen.py"
    { (yyval.list_maker) = ListMaker::parse((yyvsp[(1) - (3)].t_open_square), (yyvsp[(2) - (3)].test_list), (yyvsp[(3) - (3)].t_close_square)); (yyval.list_maker)->linenum = line_num; ;}
    break;

  case 184:

/* Line 1464 of yacc.c  */
#line 613 "ast/autogen.py"
    { (yyval.name_phrase) = NamePhrase::parse((yyvsp[(1) - (1)].t_name)); (yyval.name_phrase)->linenum = line_num; ;}
    break;

  case 185:

/* Line 1464 of yacc.c  */
#line 615 "ast/autogen.py"
    { (yyval.repr_phrase) = ReprPhrase::parse((yyvsp[(1) - (3)].t_backtick), (yyvsp[(2) - (3)].test_list_non_trailing), (yyvsp[(3) - (3)].t_backtick)); (yyval.repr_phrase)->linenum = line_num; ;}
    break;



/* Line 1464 of yacc.c  */
#line 3269 "parathon.yy.cc"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (context, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (context, yymsg);
	  }
	else
	  {
	    yyerror (context, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, context);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, context);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (context, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, context);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, context);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  yyps->yynew = 1;

yypushreturn:
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1684 of yacc.c  */
#line 618 "ast/autogen.py"


