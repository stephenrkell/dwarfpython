#include "parathon.h"
#include "ast.h"

class ParathonFunction : public ParathonValue {
    public:
        NamePhrase* name;
        ParameterList* params;
        Suite* suite;
        ParathonContext* context;
        ParathonFunction(NamePhrase*, ParameterList*, Suite*,ParathonContext&);
        void toStream(std::ostream&);
        ParathonValue *call(std::vector<ParathonValue*>*);
};
