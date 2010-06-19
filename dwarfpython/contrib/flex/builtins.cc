#include "parathon.h"
#include "lexer.h"
#include <dlfcn.h>
#include <sstream>
/**
 * _____________________________ __getattr__ ____________________________________
 *
 * Lookup the string in the value's namespace
 */
extern "C" ParathonValue* __getattr__(ParathonValue* val, char *str)
{
    ParathonValue* result;
    ParathonValue* klass;
    ParathonValue* getattr;

    if ((result = val->lookup(str)))
        return result;

    klass = val->lookup("__class__");

    if (klass)
    {
        getattr = klass->lookup("__getattr__");
        if ((result = klass->lookup(str)))
        {
            return result->bindIfApplicable(val);
        }
        else if (getattr)
        {
            std::vector<ParathonValue *> args;
            args.push_back(val);
            args.push_back(ParathonValue::getValue(str, die_wrapper::builtin("parathon_string")));
            if ((result = getattr->call(&args)))
            {
                return result->bindIfApplicable(val);
            }
        }
    }
    else
    {
        getattr = val->lookup("__getattr__");
        if (getattr)
        {
            std::vector<ParathonValue *> args;
            args.push_back(val);
            args.push_back(ParathonValue::getValue(str, die_wrapper::builtin("parathon_string")));
            if ((result = getattr->call(&args)))
            {
                return result;
            }
        }
    }
    return NULL;
}

char * str_cattr(ParathonValue* cattr)
{
    if(!cattr->die)
        return (char*)"Anonymous variable of anonymous type.";

    std::stringstream*s = new std::stringstream();
    cattr->die->toStream(cattr->value,*s);
    return (char *)s->str().c_str();
}
ParathonValue* getattr_cfile_top(ParathonValue *klass, char* str)
{
    ParathonValue* v_ns = __getattr__(klass, (char *)"__namespace__");
    ParathonValue* v_ds = __getattr__(klass, (char *)"__dieset__");

    if (v_ns == NULL || v_ds == NULL)
    {
        throw ParathonException("Tried to call getattr_cfile on a not cfile!");
    }

    dwarf::encap::dieset* ds =*(dwarf::encap::dieset**)v_ds->value;
    void * ns = *(void**)v_ns->value;

    ParathonValue*ret = ParathonValue::getValue(dlsym(ns, str), new die_wrapper(ds, str));
    ret->assign("__repr__", ParathonValue::getValue((void*)str_cattr, die_wrapper::builtin("__str__"))->bindIfApplicable(ret));
    return ret;

}
ParathonValue* getattr_cfile(ParathonValue* val, char *str)
{   
    ParathonValue* klass = __getattr__(val, (char *)"__class__");
    return getattr_cfile_top(klass, str);
}
char * str_cfile(ParathonValue* cfile)
{
    std::stringstream *str = new std::stringstream();
    if (cfile->lookup("__name__"))
    {
        (*str) << "<module '" << (char*)cfile->lookup("__name__") << "'>";
        return (char *)str->str().c_str();
    }
    else
    {
        return (char *)"<module '<anonymous>'>";
    }
}



ParathonValue* __eval__(char *str, ParathonContext* c)
{
    yy_extra_type a;
    YY_EXTRA_FOR_STRING(a, str);
    parse_loop(a,c);
    return c;
}
ParathonValue* __import__(char *str, ParathonContext* c)
{
    char * nsym = (char *)malloc((strlen(str) + strlen("./runtime/lib.so") + 1) * sizeof(char));
    strcpy(nsym, str);
    strcat(nsym, ".py");

    FILE * f = fopen(nsym, "r");
    if (f)
    {
        ParathonContext *newcontext = new ParathonContext(c->builtins);
        yy_extra_type a;
        YY_EXTRA_FOR_FILE(a, f);
        parse_loop(a, newcontext);
        fclose(f);
        return newcontext;
    }

    nsym[0] = '\0';
    strcpy(nsym, "./runtime/lib");
    strcat(nsym, str);
    strcat(nsym, ".so");

    f = fopen(nsym, "r");
    if (f)
    {
        ParathonValue* nc = new ParathonValue();
        dlerror();
        nc->assign("__namespace__", new ReadOnlyProperty((void *)dlopen(string(nsym) == string("./runtime/libos.so") ? NULL : nsym, RTLD_NOW)));
        char * err;
        if ((err = dlerror())) {
            std::cout << err << std::endl;
        }
        nc->assign("__dieset__", new ReadOnlyProperty((void *)&(new dwarf::encap::file(fileno(f)))->ds()));
        nc->assign("__getattr__", ParathonValue::getValue((void *)getattr_cfile, die_wrapper::builtin("__getattr__")));
        nc->assign("__file__", new ReadOnlyProperty(nsym));
        nc->assign("__class__", ParathonValue::builtins.lookup("cobject"));
        nc->assign("__name__", new ParathonValue(str));
//        nc->assign("__str__", ParathonValue::getValue((void *)str_cfile, die_wrapper::builtin("__str__"))->bindIfApplicable(nc));
        return nc;
    }
    else
    {
        std::cerr << "No such file or directory." << std::endl;
        return NULL;
    }

    return NULL;
}

void initialize_builtins(ParathonContext* builtins)
{
    ParathonValue* cobject = new ParathonValue();
    cobject->assign((char*)"__getattr__", ParathonValue::getValue((void*)getattr_cfile_top, die_wrapper::builtin("__getattr__")));
    builtins->assign((char*)"cobject", cobject);

    builtins->assign((char*)"__eval__", new ReadOnlyProperty((void*)__eval__));
    builtins->assign((char*)"__import__", new ReadOnlyProperty((void*)__import__));
    builtins->assign((char*)"__getattr__", new ReadOnlyProperty((void*)__getattr__));
    builtins->assign((char*)"__repr__", ParathonValue::getValue((void*)str_cattr, die_wrapper::builtin("__str__")));
    builtins->assign((char*)"int", __import__((char*)"int", builtins));
    builtins->assign((char*)"float", __import__((char*)"float", builtins));
    builtins->assign((char*)"str", __import__((char*)"string", builtins));
    builtins->assign((char*)"l", __import__((char*)"levenshtein", builtins));
    
}
