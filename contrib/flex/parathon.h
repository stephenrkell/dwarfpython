#ifndef PARATHON_H
#define PARATHON_H

class ParathonValue;

#include "runtime/types.h"
#include "die_wrapper.hh"
#include "lexer.h"
#include <ffi.h>

using std::string;

class ParathonContext;

class ParathonValue
{
    public:
        int type;
        void * nspace;
        die_wrapper* die;
        void * value;
        void * _value;
        const char * prefix;

        ParathonValue();
        ParathonValue(void *value); // FIXME

        ParathonValue(char * c);
        ParathonValue(parathon_int i);
        ParathonValue(parathon_float f);
        ParathonValue(void *value, die_wrapper* die);
        bool isTrue();
        bool isFunction();
        unsigned int length();
        virtual void toStream(std::ostream& strm);
        ParathonValue *call(const char *);
        ParathonValue *call(const char *, ParathonValue*);
        ParathonValue *call(ParathonValue*);
        ParathonValue *call();
        virtual ParathonValue *call(std::vector<ParathonValue*>*);
        ParathonValue *bindIfApplicable(ParathonValue*);
        void *castTo(die_wrapper*);
        ffi_type *type_ffi();

        ParathonValue *lookup(string);
        void assign(string, ParathonValue *value);
        bool localise(string);
        bool interpreterMode;
        static ParathonContext builtins;

        ParathonValue *parent;
        std::map<std::string, ParathonValue *> store;

        static std::map<void *, ParathonValue *> all_instances;
        static ParathonValue *retrieveInstance(void *);
        static ParathonValue *get(void *, die_wrapper* die);
        static ParathonValue *getValue(void *, die_wrapper* die);
        void registerInstance(void *, ParathonValue *);

}
;
class ParathonException
{
    public: string message;
    ParathonException(string message);
    ParathonException(string m1, string m2, string m3);
    ParathonException(string message, int linenum);
}
;
class ParathonReturn
{
    public: ParathonValue* value;
    ParathonReturn(ParathonValue*);
}
;
class ReadOnlyProperty : public ParathonValue
{
    public: ReadOnlyProperty(void *value);
}
;

class ParathonContext : public ParathonValue
{
    public:
        ParathonContext(ParathonValue *);
}
;

class ParathonAssigner
{
    public:
        virtual void assign(ParathonValue *)=0;
}
;
class ParathonContextAssigner : public ParathonAssigner
{
    private:
        ParathonValue* context;
        string name;

    public:
        ParathonContextAssigner(ParathonValue& c, string name);
        void assign(ParathonValue*);
}
;

int parse_loop(yy_extra_type extra, ParathonContext* c);
ParathonValue *parathon_call(const char *fn, ParathonValue *lhs);
ParathonValue *parathon_call(const char *fn, ParathonValue *lhs, ParathonValue *rhs);
std::ostream &operator<<(std::ostream &strm, ParathonValue *stmt);
int yyparse();

#define BASIC_EVALUATE(classname, function) \
    ParathonValue * classname::evaluate(ParathonContext& c) \
    { \
        return parathon_call(function, this->lhs->evaluate(c), this->rhs->evaluate(c)); \
    }
#endif

extern ParathonValue * None;
extern ParathonValue * NotImplemented;
