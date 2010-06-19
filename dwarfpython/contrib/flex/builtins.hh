#include "parathon.h"

void initialize_builtins(ParathonContext *c);

extern "C" ParathonValue *__eval__(char *, ParathonValue* c);
#define BUILTIN__eval__(c) (*(ParathonValue *(**)(char *,ParathonValue*))((c)->lookup("__eval__")->value))

extern "C" ParathonValue *__import__(char *, ParathonValue* c);
#define BUILTIN__import__(c) (*(ParathonValue *(**)(char *,ParathonValue*))((c)->lookup("__import__")->value))

extern "C" ParathonValue *__getattr__(ParathonValue *, char *);
#define BUILTIN__getattr__(c) (*(ParathonValue *(**)(ParathonValue *, char *))((c)->lookup("__getattr__")->value))

char * str_cattr(ParathonValue *);
