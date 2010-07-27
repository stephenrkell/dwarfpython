typedef void ParathonValue;
typedef char * parathon_string;
typedef long long int parathon_int;
typedef parathon_int * parathon_int_p;
typedef double parathon_float;
typedef parathon_float * parathon_float_p;

/**
 * This is un-ideal, to say the least, it exists to allow us to find the types we expect
 * for various builtin functions - just in case they've been customised.
 */

// Attribute overriders
ParathonValue* __getattr__(ParathonValue* self, parathon_string str) {};
ParathonValue* __setattr__(ParathonValue* self, parathon_string str, ParathonValue* value) {};
ParathonValue* __delattr__(ParathonValue* self, parathon_string str) {};

// Descriptor protocol
ParathonValue* __get__(ParathonValue* self, ParathonValue* instance, ParathonValue* class) {};
void __set__(ParathonValue* self, ParathonValue* instance, ParathonValue* value) {};
void __delete__(ParathonValue* self, ParathonValue* instance) {};

// Type conversions
parathon_string __str__(ParathonValue* self){};
parathon_int __int__(ParathonValue* self){};
parathon_float __float__(ParathonValue* self){};

parathon_int_p _____misc__(){};
parathon_float_p _____misc____(){};
