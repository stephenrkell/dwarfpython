#include <dlfcn.h>
#include "ast.h"
#include <string.h>
#include "runtime/list.h"
#include "builtins.hh"

ParathonValue * None = new ParathonValue(); // Emphatically, `not` NULL - though its actual value doesn't matter
ParathonValue * NotImplemented = NULL; // Pft. Should have created this from day1, must be NULL.
ParathonContext ParathonValue::builtins(NULL);
std::map<void *, ParathonValue *> ParathonValue::all_instances;

//Needed for subclassing shouldn't be called...
ParathonValue::ParathonValue()
{
    this->die = NULL;
    this->value = NULL;
    this->parent = NULL;
}

// ASSUME this is ACTUALLY a pointer! otherwise it won't be unique - 
// this should be removed in favour of `typed` values...
ReadOnlyProperty::ReadOnlyProperty(void *p)
{
    this->value = malloc(4);
    *(void **)this->value = p;
    this->assign("__set__", None);
    this->assign("__delete__", None);
}
// Use read-only property instead.
//ParathonValue::ParathonValue(void * p)
//{
//    this->value = p;
//    this->die = NULL;
//}

ParathonValue* actually_get_instance(void ** value, die_wrapper* ds)
{
    if (ds->isParathonValue())
        return *(ParathonValue**)value;

    void * x;
    // FIXME: this should be done when calling a function, not pre-emptively!
    if (ds->castTo(value, die_wrapper::builtin("parathon_int"), &x))
        return new ParathonValue(*(parathon_int*)x);

    if (ds->castTo(value, die_wrapper::builtin("parathon_float"), &x))
        return new ParathonValue(*(parathon_float*)x);

    if (ds->castTo(value, die_wrapper::builtin("parathon_string"), &x))
        return new ParathonValue(*(parathon_string*)x);

//    std::cout << "not inbuilt type" << std::endl;
    std::map<void *, ParathonValue *>::iterator i = ParathonValue::all_instances.find(value);
    if (true || i == ParathonValue::all_instances.end())
    {
        if (ds)
        {
            ParathonValue *ret = new ParathonValue();;
            ret->value = value;
            ret->die = ds;
            return ret;
        }
        else
        {
            std::cerr << "Tried to look up a parathon value that did not exist!" << std::cout;
            return NULL;
        }
    }
    else
    {
        return i->second;
    }
}

ParathonValue* ParathonValue::retrieveInstance(void * value)
{
    return actually_get_instance((void**)value, NULL);
}
// Get a new ParathonValue that points to the same value as value points to
ParathonValue* ParathonValue::get(void * value, die_wrapper * ds)
{
    return actually_get_instance((void**)value, ds);
}
// Get a new ParathonValue with this as the value
ParathonValue* ParathonValue::getValue(void * value, die_wrapper * ds)
{
    void ** a = (void **)malloc(4);
    *a  = value;
    return actually_get_instance(a, ds);
}

void ParathonValue::registerInstance(void* value, ParathonValue* instance)
{
    std::map<void *, ParathonValue *>::iterator i = ParathonValue::all_instances.find(value);
    if (i != ParathonValue::all_instances.end())
    {
        std::cerr << "Tried to register a second parathon value for the same instance!" << std::cout;
        return;
    }
    ParathonValue::all_instances[value] = instance;
}

ParathonValue* ParathonValue::bindIfApplicable(ParathonValue* self)
{
    // TODO: consider failing with wrong types?
    die_wrapper *new_type;
    closure_binding *userdata = (closure_binding *)malloc(sizeof(closure_binding));

    if (!(new_type = this->die->for_closure()))
        return this;

    try{
        if (!(userdata->bound_arg = self->castTo(this->die->child(0))))
            return this;
    }catch(ParathonException e){
        //assume "Could not cast"
        return this;
    }

    // TODO: encapsulate this better
    ffi_cif *cif = (ffi_cif*)malloc(sizeof(ffi_cif));
    ffi_type **args = new_type->ffi_args();
    ffi_closure *closure_memory;
    void (*closure_function)();

    userdata->bound_ffi_type = this->die->child(0)->as_ffi();
    userdata->bound_function = *(void(**)())this->value;

    // FIXME: This leaks memory, it's not garbage collected!
    
    if (!(closure_memory = (ffi_closure*)ffi_closure_alloc(sizeof(ffi_closure), (void **)&closure_function)))
    {
        std::cerr << "Could not allocate closure!" << std::endl;
        return this;
    }

    if (ffi_prep_cif(cif, FFI_DEFAULT_ABI, new_type->child_length(), 
            new_type->ffi_return(), args) != FFI_OK)
    {
        std::cerr << "Closure CIF could not be created!" << std::endl;
        return this;
    }

    if (ffi_prep_closure_loc(closure_memory, cif, call_closure, userdata, 
            (void*)closure_function) != FFI_OK)
    {
        std::cerr << "Closure location could not be created!" << std::endl;
        return this;
    }
    ParathonValue* ret = ParathonValue::getValue((void*)closure_function, new_type);
    ret->parent = this;
    return ret;
}

void * ParathonValue::castTo(die_wrapper* type)
{
    // Treat this differently, this means that the function is coming
    // back round into C++ again. Eww.. :p
    // If we're doing it like this, maybe lose the lookup tables...
    if (type->isParathonValue())
    {
        ParathonValue ** result = (ParathonValue**)malloc(sizeof(ParathonValue *));
        *result = this;
        return (void *)result;
    }

    if (type->isSameType(this->die))
        return (void *)this->value;

    if (this->die->isPointerTo(type))
        return *(void **)this->value;

    void* result=NULL;

    if (this->die->castTo((void **)this->value, type, &result))
    {
        return result;
    }

    std::cout << type->tostr() << std::endl;
    std::cout << this->die->tostr() << std::endl;

    throw ParathonException("Could not cast");
}

// Call __getattr__ instead!
ParathonValue *ParathonValue::lookup(string name)
{
    ParathonValue* result = this->die ? this->die->lookupField((void**)this->value, name.c_str()) : NULL;
    if (result)
    {
        return result;
    }
    if (this->store.count(name))
    {
        return this->store.at(name);
    }
    else if (this->parent)
    {
        return this->parent->lookup(name);
    }
    else
    {
        return NULL;
    }
}
void ParathonValue::assign(string name, ParathonValue * value)
{
    this->store[std::string(name)] = value;
}

bool ParathonValue::localise(string name)
{
    //TODO - and rename (to handle "nonlocal")
    return false;
}

ParathonValue::ParathonValue(char * str)
{
    this->value = malloc(sizeof(char *));
    *(char**)this->value = str;
    this->die = die_wrapper::builtin("parathon_string");
    this->assign("__class__", ParathonValue::builtins.lookup("str"));
    this->parent = NULL;
}

ParathonValue::ParathonValue(parathon_int i)
{
    this->value = malloc(8);
    *(parathon_int*)this->value = i;
    this->die = die_wrapper::builtin("parathon_int");
    this->assign("__class__", ParathonValue::builtins.lookup("int"));
    this->parent = NULL;
}

ParathonValue::ParathonValue(parathon_float f)
{
    this->value = malloc(8);
    *(parathon_float*)this->value = f;
    this->die = die_wrapper::builtin("parathon_float");
    this->assign("__class__", ParathonValue::builtins.lookup("float"));
    this->parent = NULL;
}

ParathonValue::ParathonValue(void * pnt, die_wrapper * die)
{
    this->registerInstance(pnt, this);
    this->value = malloc(4);
    *(void **)this->value = pnt;
    this->die = die;
    this->parent = NULL;
}
bool ParathonValue::isTrue()
{
    return *(char *)(this->call("__nonzero__")->value);
}
//ParathonValue *ParathonValue::lookup(char * sym)
//{
//    if (this->nspace && this->die)
//    {
//        char * nsym = (char *)malloc((strlen(sym) + strlen(prefix) + 1) * sizeof(char));
//        strcpy(nsym, this->prefix);
//        strcat(nsym, sym);
//        return new ParathonValue(dlsym(this->nspace, nsym), new die_wrapper(this->die, nsym));
//    }
//    return NULL;
//}
bool ParathonValue::isFunction()
{
    return this->die->isFunction();
}
ffi_type *ParathonValue::type_ffi()
{
    return &ffi_type_sint64;
}
unsigned int ParathonValue::length()
{
    return 1;
}
ParathonValue *ParathonValue::call(const char * sym)
{
    return BUILTIN__getattr__(&builtins)(this, (char*)sym)->call();
}
ParathonValue *ParathonValue::call(const char * sym, ParathonValue* other)
{
    ParathonValue *fun = BUILTIN__getattr__(&builtins)(this, (char*)sym);
    std::vector<ParathonValue *>* argv= new std::vector<ParathonValue *>();
    argv->push_back(other);
    return fun->call(argv);
}
ParathonValue *ParathonValue::call(ParathonValue* other)
{
    std::vector<ParathonValue*> args;
    args.push_back(other);
    return this->call(&args);
}
ParathonValue *ParathonValue::call(std::vector<ParathonValue *>* args)
{
    if (!(this && this->isFunction()))
    {
        std::cerr << "Tried not to call a function" << std::endl;
        return NULL;
    }

    if (this->die->child_length() != args->size())
    {
        std::cerr << "Tried to call a multi-argument function" << std::endl;
        return NULL;
    }

    ffi_type ** arg_types = this->die->ffi_args();
    void ** values = (void **)malloc(sizeof(void*)*args->size());
    ffi_cif cif;
    void** ret = (void**)malloc(4);
    unsigned int argc = this->die->child_length();
    ffi_type *return_type = this->die->ffi_return();
    void(*function)() = *(void(**)())this->value;

    for(unsigned i = 0; i < argc; i++)
    {
        values[i] = (*args)[i]->castTo(this->die->child(i));
    }

    if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, argc, return_type, arg_types) == FFI_OK)
    {
        ffi_call(&cif, function, ret, values);
    }

    return ParathonValue::get(ret, this->die->return_type());
}

using std::ostream;
using std::vector;
ParathonValue *ParathonValue::call()
{
    vector<ParathonValue *> a;
    return this->call(&a);
}

void ParathonValue::toStream(ostream &strm)
{
    ParathonValue* to_str=NULL;
    try{
        to_str = __getattr__(this, (char*)"__repr__");
    }catch(ParathonException e) {
        // FIXME use a subclass
        if (e.message != "Could not find '__repr__' in library."){
            throw e;
        }
        to_str = NULL;
    }
//    std::cout << this->value << *(void**)this->value << std::endl;
    if (!to_str)
    {
        this->die->toStream(this->value, strm);
        return;
    }
    ParathonValue* result = to_str->call();
    if (result)
        strm << *(char **)result->value << std::endl;
    else
        strm << "ParathonValue instance at '" << this->value << std::endl;
}

ostream &operator<<(ostream &strm, ParathonValue *v)
{
    if (v)
    {
        v->toStream(strm);
    }
    else
    {
        strm << "None";
    }
    return strm;
}
