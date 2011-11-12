import os, sys, re
import dircache

"""
    Generates a parser and header therefore from the .cc files in a given directory.
    It is assumed that: 1 class -> 1 rule of the grammer.

    These files must be beautiful - i.e. each function declaration on its own line
    without the opening {

    Any private members are described in a comment line starting " * private: "
"""

files = []

compulsary = [
    ['void', 'toStream', 'std::ostream&'],
    ['val','evaluate'],
    ['void','evaluate_print','std::ostream&']
]

token_types = {
    'T_NAME': 'char *',
    'T_STRING': 'char *',
    'T_INTEGER': 'long long',
    'T_FLOAT': 'double'
}
tokens = set()

re_is_def = re.compile(r"([^ \t]+[ \t]*){2,5}\([^\(\)]*\)")
re_space = re.compile(r"[ \t]+")
re_amp_space = re.compile(r"[ \t]*([&\*])[^>][ \t]*")
re_uc=re.compile(r"[A-Z]")

def get_signature_arguments(line):
    after = line[line.find("(")+1:line.find(")")]
    args = after.strip().split(",")
    args = map(lambda x: re_space.split(re_amp_space.sub(lambda y: y.group(1) + " ",x).strip())[0], args)
    if args == [""]:
        return []
    global tokens
    tokens = tokens.union(x for x in args if x.startswith("T_"))
    return args


def get_signature(line):
    before = line[:line.find("(")]

    blah = re_space.split(re_amp_space.sub(lambda y: (y.group(1) + " "),before).strip())
    (typ, meth) = (" ".join(blah[:-1]), blah[-1])
    #print blah
    (cls, name) = meth.split("::")

    return [typ, name] + get_signature_arguments(line)

sorted_f = []
def sorted_files():
    global sorted_f
    if len(sorted_f):
        return sorted_f
    classes = [f for f in files]

    depends = {}
    for f in files:
        depends[f] = set()
        for cl in classes:
            if f.inherits == cl.classname:
                depends[f].add(cl)
                continue
#            else:
#                print ">>" + f.inherits
#
#            for p in f.publics:
#                if cl in "".join(p):
#                    depends[f.classname].add(cl)
#                    break
#            else:
#                for p in f.privates:
#                    if cl in p:
#                        depends[f.classname].add(cl)
#                        break
#                else:
#                    for p in f.constructors:
#                        if cl in "".join(p):
#                            depends[f.classname].add(cl)
#                            break

    for i in range(len(depends)):
        for f in depends:
            for g in depends[f]:
                depends[f] = depends[f] | depends[g]

    sorted_f = [f[1] for f in sorted((len(depends[f]),f) for f in depends)]

    return sorted_f


class File(object):

    def __init__(self, filename):
        self.classname = filename[filename.rindex("/")+1:-3]
        self.upname = self.classname.replace("&", "")
        self.downname = decamel(self.upname)
        self.privates = []
        self.friends = []
        self.protecteds = []
        self.publics = []
        self.virtuals = []
        self.constructors = []
        self.destructor = False
        self.inherits = "Statement"

        for line in open(filename, "r"):

            if line.startswith(" * private: "):
                self.privates += [line.replace(" * private: ", "")]

            elif line.startswith(" * protected: "):
                self.protecteds += [line.replace(" * protected: ","")]

            elif line.startswith(" * virtual: "):
                self.virtuals += [line.replace(" * virtual: ","").strip()]

            elif line.startswith(" * friend: "):
                self.friends += [line.replace(" * friend: ","").strip()]

            elif line.startswith(" * inherits: "):
                self.inherits = line.replace(" * inherits: ", "").strip()

            elif line.startswith(self.classname + "::" + self.classname):
                self.constructors += [get_signature_arguments(line)]
                #print self.constructors[-1]

            elif line.startswith(self.classname + "::~" + self.classname):
                self.destructor = True

            elif re_is_def.match(line):
                self.publics += [get_signature(line)]
                #print self.publics[-1]

    def get_constructors(self):
        for c in self.constructors:
            #print "%s(%s);" % (self.classname, ", ".join(c))
            yield "%s(%s);" % (self.classname, ", ".join(c))

        if self.destructor:
            yield "~%s();" % self.classname
            
    def get_constructor_rules(self):
        #for c in self.constructors:
        #    rule = " ".join(decamel(a) for a in c)
        #    args = ", ".join("$%s" % (x+1) for x in range(len(c)))
        #    yield "%s { $$ = new %s(%s); }" % (rule, self.classname, args)
        for f in self.publics:
            #print f
            if f[0] == self.classname + "*" and f[1] == "parse":
                rule = " ".join(decamel(a) for a in f[2:])
                args = ", ".join("$%s" % (x+1) for x in range(len(f)-2))
                yield "%s { $$ = %s::parse(%s); $$->linenum = line_num; }" % (rule, self.classname, args)


    def get_public_functions(self):
        for f in self.publics:
            fn = "%s %s(%s)" % (f[0], f[1], ", ".join(f[2:]))
            if fn not in self.virtuals:
                yield "%s%s;" % (("static " if f[1] == "parse" else ""),fn)

        for f in self.virtuals:
            yield "virtual %s;" % (f)

    def get_privates(self):
        for p in self.privates:
            yield p

    def get_friends(self):
        for f in self.friends:
            yield f
 
    def get_protecteds(self):
        for p in self.protecteds:
            yield p

    def get_c_section(self):
        return "typedef struct {} %s;" % self.classname

    def get_cpp_section(self):
        return """
class %s: public %s
{
    public:
        %s
        %s
    %s
    private:
        %s
    protected:
        %s
};
""" % (self.classname, self.inherits,
        "\n        ".join(self.get_constructors()),
        "\n        ".join(self.get_public_functions()),
        "\n        ".join(self.get_privates()),
        "\n        friend ".join(self.get_friends()),
        "\n        ".join(self.get_protecteds()))

def get_statement_interface():
    """Returns the virtual functions in Statement based on compulsary"""
    for c in compulsary:
        yield "        virtual %s %s(%s) = 0;" % (c[0], c[1], ", ".join(c[2:]))

def get_tok_typedefs():
    for t in tokens:
        tt = t.replace("TOK_", "T_")
        #print "typedef %s %s;" % ((token_types[tt] if tt in token_types else "int"), tt)
        yield "typedef %s %s;" % ((token_types[tt] if tt in token_types else "int"), tt)

def decamel(str):
    if str == "":
        return str
    if str.startswith("T_"):
        return str.replace("T_", "TOK_")

    a = re_uc.sub(lambda x: "_" + x.group(0).lower(), str.replace("&","").replace("*", ""))
    if a[0] == "_":
        return a[1:]
    else:
        return a

def get_union_definitions():
    for f in sorted_files():
        yield "%s *%s;" % (f.upname, f.downname)
        
    for t in tokens:
        yield "%s %s;" % (t, t.lower())

def get_type_definitions():
    for f in sorted_files():
        yield "%%type <%s> %s" % ((f.downname,) * 2)
    for t in tokens:
        yield "%%type <%s> %s" % (t.lower(), t.replace("T_", "TOK_"))

def get_bison_rules():
    for f in sorted_files():
        ret = f.downname + ": "
        j = "\n" + " " * len(f.downname) + "| "
        clines = f.get_constructor_rules()

        yield ret + j.join(clines) +  j.replace("| ", ";")

def get_ast_h():
    return """/* This file was autogenerated by %s. Changes will be reverted on build. */

%s
#ifndef AST_H
#define AST_H
#ifndef __cplusplus
%s
#else

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "val.h"
class ParathonAssigner; // to remove soon

using std::string;
%s

class Statement
{
    public:
        int linenum;
%s
};
std::ostream &operator<<(std::ostream &strm, Statement *stmt);
class Operator: public Statement
{
    public:
        Statement *lhs;
        Statement *rhs;
        virtual const char *opname();
};
%s

#endif
#endif
""" % (sys.argv[0], 
        "\n".join(get_tok_typedefs()),
        "\n".join(map(lambda x: x.get_c_section(), sorted_files())), 
        "\n".join("class %s;" % f.classname for f in sorted_files()),
        "\n".join(get_statement_interface()),
        "\n".join(map(lambda x: x.get_cpp_section(), sorted_files())))

def get_parathon_yy():
    return """/* This file was autogenerated by %s. Changes will be reverted on build. */
%%{
#line 288 "ast/autogen.py"

#include <cctype>
#include <cstring>
#include <stdio.h>
#include <iostream>
#include "ast.h"
#include "parathon.h"

extern "C" int line_num;
void evaluate(SingleInput * si);
void yyerror(void* context, char const *s)
{
    std::cout << "Syntax error, line " << line_num << std::endl;
}

%%}

%%define api.pure
%%define api.push_pull "push"
%%parse-param { void* context }

%%token TOK_ERROR

%%token TOK_NEWLINE TOK_INDENT TOK_OUTDENT 
%%token TOK_INTEGER TOK_FLOAT 
%%token TOK_OPEN_SQUARE TOK_CLOSE_SQUARE TOK_OPEN_CURLY TOK_CLOSE_CURLY TOK_OPEN_CURVED TOK_CLOSE_CURVED 
%%token TOK_NAME TOK_STRING 
%%left TOK_DOT TOK_COMMA TOK_SEMICOLON
%%token TOK_ASSIGN TOK_COLON TOK_AT TOK_BACKTICK
%%left TOK_EQ TOK_GT TOK_GTEQ TOK_LT TOK_LTEQ TOK_NOTEQ
%%left TOK_PLUS TOK_MINUS TOK_MULTIPLY TOK_DIVIDE TOK_TRUNC_DIVIDE TOK_MODULUS
%%right TOK_POWER
%%left TOK_BAND TOK_BOR TOK_BNOT TOK_BXOR
%%left TOK_LEFTSHIFT TOK_RIGHTSHIFT
%%token TOK_NOT
%%left TOK_AND TOK_OR TOK_IN TOK_IS
%%token TOK_IF TOK_ELIF TOK_ELSE
%%token TOK_PASS TOK_RETURN TOK_YIELD TOK_PRINT 
%%token TOK_FOR TOK_WHILE TOK_BREAK TOK_CONTINUE 
%%token TOK_TRY TOK_ASSERT TOK_RAISE TOK_EXCEPT TOK_FINALLY 
%%token TOK_CLASS TOK_DEF TOK_LAMBDA 
%%token TOK_FROM TOK_GLOBAL TOK_IMPORT TOK_AS 
%%token TOK_WITH TOK_DEL TOK_EXEC 

%%union {
    %s
    /* lexer */
    long long int_val;
    double float_val;
    char *string;
    char *name;
}

%s
%%%%
#line 341 "ast/autogen.py"

all_input: /* empty */ { }
         | all_input single_input { evaluate($2); }
         | all_input error TOK_NEWLINE { if (interpreterMode) yyerrok; else return 0; }
         | all_input TOK_INDENT error TOK_NEWLINE { if (interpreterMode) yyerrok; else return 0; }
         ;

%s

%%%%
""" % (sys.argv[0], 
        "\n    ".join(get_union_definitions()),
       "\n".join(get_type_definitions()),
       "\n".join(get_bison_rules()))

def main():
    if len(sys.argv) != 2 or not os.path.isdir(sys.argv[1]):
        return usage()

    list = dircache.listdir(sys.argv[1])
    for fname in filter(lambda x: x.endswith(".cc"), list):
        files.append(File(os.path.join(sys.argv[1], fname)))

    f = open("ast.h", "w")
    f.write(get_ast_h())
    f.close()

    f = open("parathon.yy", "w")
    f.write(get_parathon_yy())
    f.close()

def usage():
    print >>sys.stderr,"""
        Usage %s <directory>
        Generates 'ast.h' and 'parathon.yy' in the current directory from files
        in the given directory.
    """ % sys.argv[0]

if __name__ == '__main__':
    main();
