
%{
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

%}

%define api.pure
%define api.push_pull "push"
%parse-param { ParathonContext* context }

%token TOK_ERROR

%token TOK_NEWLINE TOK_INDENT TOK_OUTDENT 
%token TOK_INTEGER TOK_FLOAT 
%token TOK_OPEN_SQUARE TOK_CLOSE_SQUARE TOK_OPEN_CURLY TOK_CLOSE_CURLY TOK_OPEN_CURVED TOK_CLOSE_CURVED 
%token TOK_NAME TOK_STRING 
%left TOK_DOT TOK_COMMA TOK_SEMICOLON
%token TOK_ASSIGN TOK_COLON TOK_AT TOK_BACKTICK
%left TOK_EQ TOK_GT TOK_GTEQ TOK_LT TOK_LTEQ TOK_NOTEQ
%left TOK_PLUS TOK_MINUS TOK_MULTIPLY TOK_DIVIDE TOK_TRUNC_DIVIDE TOK_MODULUS
%right TOK_POWER
%left TOK_BAND TOK_BOR TOK_BNOT TOK_BXOR
%left TOK_LEFTSHIFT TOK_RIGHTSHIFT
%token TOK_NOT
%left TOK_AND TOK_OR TOK_IN TOK_IS
%token TOK_IF TOK_ELIF TOK_ELSE
%token TOK_PASS TOK_RETURN TOK_YIELD TOK_PRINT 
%token TOK_FOR TOK_WHILE TOK_BREAK TOK_CONTINUE 
%token TOK_TRY TOK_ASSERT TOK_RAISE TOK_EXCEPT TOK_FINALLY 
%token TOK_CLASS TOK_DEF TOK_LAMBDA 
%token TOK_FROM TOK_GLOBAL TOK_IMPORT TOK_AS 
%token TOK_WITH TOK_DEL TOK_EXEC 

%union {
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
}

%type <test_phrase_optional> test_phrase_optional
%type <unary_operator> unary_operator
%type <arith_operator> arith_operator
%type <comparison_operator> comparison_operator
%type <dotted_name> dotted_name
%type <mult_operator> mult_operator
%type <parameter_list> parameter_list
%type <parameter_list_args> parameter_list_args
%type <parameter_phrase> parameter_phrase
%type <shift_operator> shift_operator
%type <single_input> single_input
%type <slice_list> slice_list
%type <slice_phrase> slice_phrase
%type <small_statement> small_statement
%type <test_statement> test_statement
%type <while_statement> while_statement
%type <assign_statement> assign_statement
%type <break_statement> break_statement
%type <comp_eq> comp_eq
%type <comp_gt> comp_gt
%type <comp_gt_eq> comp_gt_eq
%type <comp_in> comp_in
%type <comp_is> comp_is
%type <comp_lt> comp_lt
%type <comp_lt_eq> comp_lt_eq
%type <comp_not_eq> comp_not_eq
%type <comp_not_in> comp_not_in
%type <comp_not_is> comp_not_is
%type <continue_statement> continue_statement
%type <delete_statement> delete_statement
%type <function_definition> function_definition
%type <global_statement> global_statement
%type <if_statement> if_statement
%type <import_statement> import_statement
%type <op_band> op_band
%type <op_bnot> op_bnot
%type <op_bor> op_bor
%type <op_bxor> op_bxor
%type <op_divide> op_divide
%type <op_left_shift> op_left_shift
%type <op_minus> op_minus
%type <op_mod> op_mod
%type <op_mult> op_mult
%type <op_negative> op_negative
%type <op_plus> op_plus
%type <op_positive> op_positive
%type <op_power> op_power
%type <op_right_shift> op_right_shift
%type <op_trunc> op_trunc
%type <parameter_list_kwargs> parameter_list_kwargs
%type <parameter_list_non_args> parameter_list_non_args
%type <pass_statement> pass_statement
%type <print_statement> print_statement
%type <return_statement> return_statement
%type <suite> suite
%type <test_phrase> test_phrase
%type <dotted_as_names> dotted_as_names
%type <import_as_names> import_as_names
%type <suite_body> suite_body
%type <test_list> test_list
%type <test_list_non_empty> test_list_non_empty
%type <inline_if_phrase> inline_if_phrase
%type <or_phrase> or_phrase
%type <simple_statement> simple_statement
%type <test_list_non_trailing> test_list_non_trailing
%type <and_phrase> and_phrase
%type <not_phrase> not_phrase
%type <comparison_phrase> comparison_phrase
%type <comparison_list> comparison_list
%type <expression> expression
%type <xor_expression> xor_expression
%type <and_expression> and_expression
%type <shift_expression> shift_expression
%type <arith_expression> arith_expression
%type <mult_expression> mult_expression
%type <fact_expression> fact_expression
%type <unary_phrase> unary_phrase
%type <base_phrase> base_phrase
%type <test_phrase_bracketed> test_phrase_bracketed
%type <tuple_maker> tuple_maker
%type <value_float> value_float
%type <value_int> value_int
%type <value_string> value_string
%type <function_call> function_call
%type <get_attr> get_attr
%type <get_item> get_item
%type <list_maker> list_maker
%type <name_phrase> name_phrase
%type <repr_phrase> repr_phrase
%type <t_comma> TOK_COMMA
%type <t_def> TOK_DEF
%type <t_dot> TOK_DOT
%type <t_del> TOK_DEL
%type <t_eq> TOK_EQ
%type <t_break> TOK_BREAK
%type <t_newline> TOK_NEWLINE
%type <t_rightshift> TOK_RIGHTSHIFT
%type <t_noteq> TOK_NOTEQ
%type <t_open_curved> TOK_OPEN_CURVED
%type <t_gt> TOK_GT
%type <t_trunc_divide> TOK_TRUNC_DIVIDE
%type <t_and> TOK_AND
%type <t_string> TOK_STRING
%type <t_modulus> TOK_MODULUS
%type <t_while> TOK_WHILE
%type <t_continue> TOK_CONTINUE
%type <t_plus> TOK_PLUS
%type <t_minus> TOK_MINUS
%type <t_power> TOK_POWER
%type <t_import> TOK_IMPORT
%type <t_close_curved> TOK_CLOSE_CURVED
%type <t_bor> TOK_BOR
%type <t_lt> TOK_LT
%type <t_multiply> TOK_MULTIPLY
%type <t_semicolon> TOK_SEMICOLON
%type <t_outdent> TOK_OUTDENT
%type <t_gteq> TOK_GTEQ
%type <t_lteq> TOK_LTEQ
%type <t_else> TOK_ELSE
%type <t_open_square> TOK_OPEN_SQUARE
%type <t_close_square> TOK_CLOSE_SQUARE
%type <t_divide> TOK_DIVIDE
%type <t_indent> TOK_INDENT
%type <t_bxor> TOK_BXOR
%type <t_return> TOK_RETURN
%type <t_not> TOK_NOT
%type <t_if> TOK_IF
%type <t_or> TOK_OR
%type <t_print> TOK_PRINT
%type <t_assign> TOK_ASSIGN
%type <t_in> TOK_IN
%type <t_leftshift> TOK_LEFTSHIFT
%type <t_pass> TOK_PASS
%type <t_as> TOK_AS
%type <t_name> TOK_NAME
%type <t_band> TOK_BAND
%type <t_bnot> TOK_BNOT
%type <t_is> TOK_IS
%type <t_integer> TOK_INTEGER
%type <t_backtick> TOK_BACKTICK
%type <t_float> TOK_FLOAT
%type <t_from> TOK_FROM
%type <t_global> TOK_GLOBAL
%type <t_colon> TOK_COLON
%%
#line 341 "ast/autogen.py"

all_input: /* empty */ { }
         | all_input single_input { evaluate($2, context); }
         | all_input error TOK_NEWLINE { if (context->interpreterMode) yyerrok; else return 0; }
         | all_input TOK_INDENT error TOK_NEWLINE { if (context->interpreterMode) yyerrok; else return 0; }
         ;

test_phrase_optional:  { $$ = TestPhraseOptional::parse(); $$->linenum = line_num; }
                    | test_phrase { $$ = TestPhraseOptional::parse($1); $$->linenum = line_num; }
                    ;
unary_operator: op_negative { $$ = UnaryOperator::parse($1); $$->linenum = line_num; }
              | op_positive { $$ = UnaryOperator::parse($1); $$->linenum = line_num; }
              | op_bnot { $$ = UnaryOperator::parse($1); $$->linenum = line_num; }
              ;
arith_operator: op_plus { $$ = ArithOperator::parse($1); $$->linenum = line_num; }
              | op_minus { $$ = ArithOperator::parse($1); $$->linenum = line_num; }
              ;
comparison_operator: comp_lt { $$ = ComparisonOperator::parse($1); $$->linenum = line_num; }
                   | comp_gt { $$ = ComparisonOperator::parse($1); $$->linenum = line_num; }
                   | comp_lt_eq { $$ = ComparisonOperator::parse($1); $$->linenum = line_num; }
                   | comp_gt_eq { $$ = ComparisonOperator::parse($1); $$->linenum = line_num; }
                   | comp_eq { $$ = ComparisonOperator::parse($1); $$->linenum = line_num; }
                   | comp_not_eq { $$ = ComparisonOperator::parse($1); $$->linenum = line_num; }
                   | comp_in { $$ = ComparisonOperator::parse($1); $$->linenum = line_num; }
                   | comp_not_in { $$ = ComparisonOperator::parse($1); $$->linenum = line_num; }
                   | comp_is { $$ = ComparisonOperator::parse($1); $$->linenum = line_num; }
                   | comp_not_is { $$ = ComparisonOperator::parse($1); $$->linenum = line_num; }
                   ;
dotted_name: TOK_NAME { $$ = DottedName::parse($1); $$->linenum = line_num; }
           | dotted_name TOK_DOT TOK_NAME { $$ = DottedName::parse($1, $2, $3); $$->linenum = line_num; }
           ;
mult_operator: op_mult { $$ = MultOperator::parse($1); $$->linenum = line_num; }
             | op_divide { $$ = MultOperator::parse($1); $$->linenum = line_num; }
             | op_trunc { $$ = MultOperator::parse($1); $$->linenum = line_num; }
             | op_mod { $$ = MultOperator::parse($1); $$->linenum = line_num; }
             ;
parameter_list: parameter_list_args { $$ = ParameterList::parse($1); $$->linenum = line_num; }
              | parameter_list_non_args { $$ = ParameterList::parse($1); $$->linenum = line_num; }
              | parameter_list_non_args TOK_COMMA parameter_list_args { $$ = ParameterList::parse($1, $2, $3); $$->linenum = line_num; }
              ;
parameter_list_args: parameter_list_kwargs { $$ = ParameterListArgs::parse($1); $$->linenum = line_num; }
                   | TOK_MULTIPLY test_phrase { $$ = ParameterListArgs::parse($1, $2); $$->linenum = line_num; }
                   | TOK_MULTIPLY test_phrase TOK_COMMA parameter_list_kwargs { $$ = ParameterListArgs::parse($1, $2, $3, $4); $$->linenum = line_num; }
                   ;
parameter_phrase: test_phrase { $$ = ParameterPhrase::parse($1); $$->linenum = line_num; }
                | name_phrase TOK_ASSIGN test_phrase { $$ = ParameterPhrase::parse($1, $2, $3); $$->linenum = line_num; }
                ;
shift_operator: op_left_shift { $$ = ShiftOperator::parse($1); $$->linenum = line_num; }
              | op_right_shift { $$ = ShiftOperator::parse($1); $$->linenum = line_num; }
              ;
single_input: TOK_NEWLINE { $$ = SingleInput::parse($1); $$->linenum = line_num; }
            | simple_statement TOK_NEWLINE { $$ = SingleInput::parse($1, $2); $$->linenum = line_num; }
            | if_statement { $$ = SingleInput::parse($1); $$->linenum = line_num; }
            | while_statement { $$ = SingleInput::parse($1); $$->linenum = line_num; }
            | function_definition { $$ = SingleInput::parse($1); $$->linenum = line_num; }
            ;
slice_list: slice_phrase { $$ = SliceList::parse($1); $$->linenum = line_num; }
          | slice_list TOK_COMMA slice_phrase { $$ = SliceList::parse($1, $2, $3); $$->linenum = line_num; }
          ;
slice_phrase: test_phrase { $$ = SlicePhrase::parse($1); $$->linenum = line_num; }
            | TOK_DOT TOK_DOT TOK_DOT { $$ = SlicePhrase::parse($1, $2, $3); $$->linenum = line_num; }
            | test_phrase_optional TOK_COLON test_phrase_optional { $$ = SlicePhrase::parse($1, $2, $3); $$->linenum = line_num; }
            | test_phrase_optional TOK_COLON test_phrase_optional TOK_COLON test_phrase_optional { $$ = SlicePhrase::parse($1, $2, $3, $4, $5); $$->linenum = line_num; }
            ;
small_statement: print_statement { $$ = SmallStatement::parse($1); $$->linenum = line_num; }
               | import_statement { $$ = SmallStatement::parse($1); $$->linenum = line_num; }
               | delete_statement { $$ = SmallStatement::parse($1); $$->linenum = line_num; }
               | break_statement { $$ = SmallStatement::parse($1); $$->linenum = line_num; }
               | continue_statement { $$ = SmallStatement::parse($1); $$->linenum = line_num; }
               | pass_statement { $$ = SmallStatement::parse($1); $$->linenum = line_num; }
               | global_statement { $$ = SmallStatement::parse($1); $$->linenum = line_num; }
               | assign_statement { $$ = SmallStatement::parse($1); $$->linenum = line_num; }
               | test_statement { $$ = SmallStatement::parse($1); $$->linenum = line_num; }
               | return_statement { $$ = SmallStatement::parse($1); $$->linenum = line_num; }
               ;
test_statement: test_phrase { $$ = TestStatement::parse($1); $$->linenum = line_num; }
              | test_list_non_trailing TOK_COMMA { $$ = TestStatement::parse($1, $2); $$->linenum = line_num; }
              | test_list_non_trailing TOK_COMMA test_phrase { $$ = TestStatement::parse($1, $2, $3); $$->linenum = line_num; }
              ;
while_statement: TOK_WHILE test_phrase TOK_COLON suite { $$ = WhileStatement::parse($1, $2, $3, $4); $$->linenum = line_num; }
               ;
assign_statement: test_statement TOK_ASSIGN test_statement { $$ = AssignStatement::parse($1, $2, $3); $$->linenum = line_num; }
                ;
break_statement: TOK_BREAK { $$ = BreakStatement::parse($1); $$->linenum = line_num; }
               ;
comp_eq: TOK_EQ { $$ = CompEq::parse($1); $$->linenum = line_num; }
       ;
comp_gt: TOK_GT { $$ = CompGt::parse($1); $$->linenum = line_num; }
       ;
comp_gt_eq: TOK_GTEQ { $$ = CompGtEq::parse($1); $$->linenum = line_num; }
          ;
comp_in: TOK_IN { $$ = CompIn::parse($1); $$->linenum = line_num; }
       ;
comp_is: TOK_IS { $$ = CompIs::parse($1); $$->linenum = line_num; }
       ;
comp_lt: TOK_LT { $$ = CompLt::parse($1); $$->linenum = line_num; }
       ;
comp_lt_eq: TOK_LTEQ { $$ = CompLtEq::parse($1); $$->linenum = line_num; }
          ;
comp_not_eq: TOK_NOTEQ { $$ = CompNotEq::parse($1); $$->linenum = line_num; }
           ;
comp_not_in: TOK_NOT TOK_IN { $$ = CompNotIn::parse($1, $2); $$->linenum = line_num; }
           ;
comp_not_is: TOK_IS TOK_NOT { $$ = CompNotIs::parse($1, $2); $$->linenum = line_num; }
           ;
continue_statement: TOK_CONTINUE { $$ = ContinueStatement::parse($1); $$->linenum = line_num; }
                  ;
delete_statement: TOK_DEL test_list { $$ = DeleteStatement::parse($1, $2); $$->linenum = line_num; }
                ;
function_definition: TOK_DEF name_phrase TOK_OPEN_CURVED parameter_list TOK_CLOSE_CURVED TOK_COLON suite { $$ = FunctionDefinition::parse($1, $2, $3, $4, $5, $6, $7); $$->linenum = line_num; }
                   ;
global_statement: TOK_GLOBAL name_phrase { $$ = GlobalStatement::parse($1, $2); $$->linenum = line_num; }
                | global_statement TOK_COMMA name_phrase { $$ = GlobalStatement::parse($1, $2, $3); $$->linenum = line_num; }
                ;
if_statement: TOK_IF test_phrase TOK_COLON suite { $$ = IfStatement::parse($1, $2, $3, $4); $$->linenum = line_num; }
            | if_statement TOK_ELSE TOK_COLON suite { $$ = IfStatement::parse($1, $2, $3, $4); $$->linenum = line_num; }
            ;
import_statement: TOK_IMPORT dotted_as_names { $$ = ImportStatement::parse($1, $2); $$->linenum = line_num; }
                | TOK_FROM dotted_name TOK_IMPORT import_as_names { $$ = ImportStatement::parse($1, $2, $3, $4); $$->linenum = line_num; }
                | TOK_FROM dotted_name TOK_IMPORT TOK_OPEN_CURVED import_as_names TOK_CLOSE_CURVED { $$ = ImportStatement::parse($1, $2, $3, $4, $5, $6); $$->linenum = line_num; }
                | TOK_FROM dotted_name TOK_IMPORT TOK_OPEN_CURVED import_as_names TOK_COMMA TOK_CLOSE_CURVED { $$ = ImportStatement::parse($1, $2, $3, $4, $5, $6, $7); $$->linenum = line_num; }
                ;
op_band: TOK_BAND { $$ = OpBand::parse($1); $$->linenum = line_num; }
       ;
op_bnot: TOK_BNOT { $$ = OpBnot::parse($1); $$->linenum = line_num; }
       ;
op_bor: TOK_BOR { $$ = OpBor::parse($1); $$->linenum = line_num; }
      ;
op_bxor: TOK_BXOR { $$ = OpBxor::parse($1); $$->linenum = line_num; }
       ;
op_divide: TOK_DIVIDE { $$ = OpDivide::parse($1); $$->linenum = line_num; }
         ;
op_left_shift: TOK_LEFTSHIFT { $$ = OpLeftShift::parse($1); $$->linenum = line_num; }
             ;
op_minus: TOK_MINUS { $$ = OpMinus::parse($1); $$->linenum = line_num; }
        ;
op_mod: TOK_MODULUS { $$ = OpMod::parse($1); $$->linenum = line_num; }
      ;
op_mult: TOK_MULTIPLY { $$ = OpMult::parse($1); $$->linenum = line_num; }
       ;
op_negative: TOK_MINUS { $$ = OpNegative::parse($1); $$->linenum = line_num; }
           ;
op_plus: TOK_PLUS { $$ = OpPlus::parse($1); $$->linenum = line_num; }
       ;
op_positive: TOK_PLUS { $$ = OpPositive::parse($1); $$->linenum = line_num; }
           ;
op_power: TOK_POWER { $$ = OpPower::parse($1); $$->linenum = line_num; }
        ;
op_right_shift: TOK_RIGHTSHIFT { $$ = OpRightShift::parse($1); $$->linenum = line_num; }
              ;
op_trunc: TOK_TRUNC_DIVIDE { $$ = OpTrunc::parse($1); $$->linenum = line_num; }
        ;
parameter_list_kwargs:  { $$ = ParameterListKwargs::parse(); $$->linenum = line_num; }
                     | TOK_POWER test_phrase { $$ = ParameterListKwargs::parse($1, $2); $$->linenum = line_num; }
                     | TOK_POWER test_phrase TOK_COMMA { $$ = ParameterListKwargs::parse($1, $2, $3); $$->linenum = line_num; }
                     ;
parameter_list_non_args: parameter_phrase { $$ = ParameterListNonArgs::parse($1); $$->linenum = line_num; }
                       | parameter_list_non_args TOK_COMMA parameter_phrase { $$ = ParameterListNonArgs::parse($1, $2, $3); $$->linenum = line_num; }
                       ;
pass_statement: TOK_PASS { $$ = PassStatement::parse($1); $$->linenum = line_num; }
              ;
print_statement: TOK_PRINT test_list { $$ = PrintStatement::parse($1, $2); $$->linenum = line_num; }
               | TOK_PRINT TOK_RIGHTSHIFT test_phrase { $$ = PrintStatement::parse($1, $2, $3); $$->linenum = line_num; }
               | TOK_PRINT TOK_RIGHTSHIFT test_phrase TOK_COMMA test_list_non_empty { $$ = PrintStatement::parse($1, $2, $3, $4, $5); $$->linenum = line_num; }
               ;
return_statement: TOK_RETURN test_list { $$ = ReturnStatement::parse($1, $2); $$->linenum = line_num; }
                ;
suite: simple_statement TOK_NEWLINE { $$ = Suite::parse($1, $2); $$->linenum = line_num; }
     | TOK_NEWLINE TOK_INDENT suite_body TOK_OUTDENT { $$ = Suite::parse($1, $2, $3, $4); $$->linenum = line_num; }
     ;
test_phrase: or_phrase { $$ = TestPhrase::parse($1); $$->linenum = line_num; }
           | or_phrase inline_if_phrase { $$ = TestPhrase::parse($1, $2); $$->linenum = line_num; }
           ;
dotted_as_names: dotted_name { $$ = DottedAsNames::parse($1); $$->linenum = line_num; }
               | dotted_name TOK_AS TOK_NAME { $$ = DottedAsNames::parse($1, $2, $3); $$->linenum = line_num; }
               | dotted_as_names TOK_COMMA dotted_name { $$ = DottedAsNames::parse($1, $2, $3); $$->linenum = line_num; }
               | dotted_as_names TOK_COMMA dotted_name TOK_AS TOK_NAME { $$ = DottedAsNames::parse($1, $2, $3, $4, $5); $$->linenum = line_num; }
               ;
import_as_names: TOK_NAME { $$ = ImportAsNames::parse($1); $$->linenum = line_num; }
               | TOK_NAME TOK_AS TOK_NAME { $$ = ImportAsNames::parse($1, $2, $3); $$->linenum = line_num; }
               | import_as_names TOK_COMMA TOK_NAME { $$ = ImportAsNames::parse($1, $2, $3); $$->linenum = line_num; }
               | import_as_names TOK_COMMA TOK_NAME TOK_AS TOK_NAME { $$ = ImportAsNames::parse($1, $2, $3, $4, $5); $$->linenum = line_num; }
               ;
suite_body: single_input { $$ = SuiteBody::parse($1); $$->linenum = line_num; }
          | suite_body single_input { $$ = SuiteBody::parse($1, $2); $$->linenum = line_num; }
          ;
test_list:  { $$ = TestList::parse(); $$->linenum = line_num; }
         | test_list_non_empty { $$ = TestList::parse($1); $$->linenum = line_num; }
         ;
test_list_non_empty: test_list_non_trailing { $$ = TestListNonEmpty::parse($1); $$->linenum = line_num; }
                   | test_list_non_trailing TOK_COMMA { $$ = TestListNonEmpty::parse($1, $2); $$->linenum = line_num; }
                   ;
inline_if_phrase: TOK_IF or_phrase TOK_ELSE test_phrase { $$ = InlineIfPhrase::parse($1, $2, $3, $4); $$->linenum = line_num; }
                ;
or_phrase: and_phrase { $$ = OrPhrase::parse($1); $$->linenum = line_num; }
         | or_phrase TOK_OR and_phrase { $$ = OrPhrase::parse($1, $2, $3); $$->linenum = line_num; }
         ;
simple_statement: small_statement { $$ = SimpleStatement::parse($1); $$->linenum = line_num; }
                | simple_statement TOK_SEMICOLON { $$ = SimpleStatement::parse($1, $2); $$->linenum = line_num; }
                | simple_statement TOK_SEMICOLON small_statement { $$ = SimpleStatement::parse($1, $2, $3); $$->linenum = line_num; }
                ;
test_list_non_trailing: test_phrase { $$ = TestListNonTrailing::parse($1); $$->linenum = line_num; }
                      | test_list_non_trailing TOK_COMMA test_phrase { $$ = TestListNonTrailing::parse($1, $2, $3); $$->linenum = line_num; }
                      ;
and_phrase: not_phrase { $$ = AndPhrase::parse($1); $$->linenum = line_num; }
          | and_phrase TOK_AND not_phrase { $$ = AndPhrase::parse($1, $2, $3); $$->linenum = line_num; }
          ;
not_phrase: comparison_phrase { $$ = NotPhrase::parse($1); $$->linenum = line_num; }
          | TOK_NOT not_phrase { $$ = NotPhrase::parse($1, $2); $$->linenum = line_num; }
          ;
comparison_phrase: expression { $$ = ComparisonPhrase::parse($1); $$->linenum = line_num; }
                 | comparison_list { $$ = ComparisonPhrase::parse($1); $$->linenum = line_num; }
                 ;
comparison_list: expression comparison_operator expression { $$ = ComparisonList::parse($1, $2, $3); $$->linenum = line_num; }
               | comparison_list comparison_operator expression { $$ = ComparisonList::parse($1, $2, $3); $$->linenum = line_num; }
               ;
expression: xor_expression { $$ = Expression::parse($1); $$->linenum = line_num; }
          | xor_expression op_bor expression { $$ = Expression::parse($1, $2, $3); $$->linenum = line_num; }
          ;
xor_expression: and_expression { $$ = XorExpression::parse($1); $$->linenum = line_num; }
              | and_expression op_bxor xor_expression { $$ = XorExpression::parse($1, $2, $3); $$->linenum = line_num; }
              ;
and_expression: shift_expression { $$ = AndExpression::parse($1); $$->linenum = line_num; }
              | shift_expression op_band and_expression { $$ = AndExpression::parse($1, $2, $3); $$->linenum = line_num; }
              ;
shift_expression: arith_expression { $$ = ShiftExpression::parse($1); $$->linenum = line_num; }
                | shift_expression shift_operator arith_expression { $$ = ShiftExpression::parse($1, $2, $3); $$->linenum = line_num; }
                ;
arith_expression: mult_expression { $$ = ArithExpression::parse($1); $$->linenum = line_num; }
                | arith_expression arith_operator mult_expression { $$ = ArithExpression::parse($1, $2, $3); $$->linenum = line_num; }
                ;
mult_expression: fact_expression { $$ = MultExpression::parse($1); $$->linenum = line_num; }
               | mult_expression mult_operator fact_expression { $$ = MultExpression::parse($1, $2, $3); $$->linenum = line_num; }
               ;
fact_expression: unary_phrase { $$ = FactExpression::parse($1); $$->linenum = line_num; }
               | unary_phrase op_power fact_expression { $$ = FactExpression::parse($1, $2, $3); $$->linenum = line_num; }
               ;
unary_phrase: base_phrase { $$ = UnaryPhrase::parse($1); $$->linenum = line_num; }
            | unary_operator unary_phrase { $$ = UnaryPhrase::parse($1, $2); $$->linenum = line_num; }
            ;
base_phrase: name_phrase { $$ = BasePhrase::parse($1); $$->linenum = line_num; }
           | get_item { $$ = BasePhrase::parse($1); $$->linenum = line_num; }
           | get_attr { $$ = BasePhrase::parse($1); $$->linenum = line_num; }
           | function_call { $$ = BasePhrase::parse($1); $$->linenum = line_num; }
           | list_maker { $$ = BasePhrase::parse($1); $$->linenum = line_num; }
           | tuple_maker { $$ = BasePhrase::parse($1); $$->linenum = line_num; }
           | repr_phrase { $$ = BasePhrase::parse($1); $$->linenum = line_num; }
           | test_phrase_bracketed { $$ = BasePhrase::parse($1); $$->linenum = line_num; }
           | value_int { $$ = BasePhrase::parse($1); $$->linenum = line_num; }
           | value_float { $$ = BasePhrase::parse($1); $$->linenum = line_num; }
           | value_string { $$ = BasePhrase::parse($1); $$->linenum = line_num; }
           ;
test_phrase_bracketed: TOK_OPEN_CURVED test_phrase TOK_CLOSE_CURVED { $$ = TestPhraseBracketed::parse($1, $2, $3); $$->linenum = line_num; }
                     ;
tuple_maker: TOK_OPEN_CURVED test_list_non_trailing TOK_COMMA test_phrase TOK_CLOSE_CURVED { $$ = TupleMaker::parse($1, $2, $3, $4, $5); $$->linenum = line_num; }
           | TOK_OPEN_CURVED test_list_non_trailing TOK_COMMA TOK_CLOSE_CURVED { $$ = TupleMaker::parse($1, $2, $3, $4); $$->linenum = line_num; }
           ;
value_float: TOK_FLOAT { $$ = ValueFloat::parse($1); $$->linenum = line_num; }
           ;
value_int: TOK_INTEGER { $$ = ValueInt::parse($1); $$->linenum = line_num; }
         ;
value_string: TOK_STRING { $$ = ValueString::parse($1); $$->linenum = line_num; }
            ;
function_call: base_phrase TOK_OPEN_CURVED parameter_list TOK_CLOSE_CURVED { $$ = FunctionCall::parse($1, $2, $3, $4); $$->linenum = line_num; }
             ;
get_attr: base_phrase TOK_DOT name_phrase { $$ = GetAttr::parse($1, $2, $3); $$->linenum = line_num; }
        ;
get_item: base_phrase TOK_OPEN_SQUARE slice_list TOK_CLOSE_SQUARE { $$ = GetItem::parse($1, $2, $3, $4); $$->linenum = line_num; }
        | base_phrase TOK_OPEN_SQUARE slice_list TOK_COMMA TOK_CLOSE_SQUARE { $$ = GetItem::parse($1, $2, $3, $4, $5); $$->linenum = line_num; }
        ;
list_maker: TOK_OPEN_SQUARE test_list TOK_CLOSE_SQUARE { $$ = ListMaker::parse($1, $2, $3); $$->linenum = line_num; }
          ;
name_phrase: TOK_NAME { $$ = NamePhrase::parse($1); $$->linenum = line_num; }
           ;
repr_phrase: TOK_BACKTICK test_list_non_trailing TOK_BACKTICK { $$ = ReprPhrase::parse($1, $2, $3); $$->linenum = line_num; }
           ;

%%
