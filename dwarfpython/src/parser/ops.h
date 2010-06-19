/* Primitive operations defined by the interpreter on AST nodes. */

/* Computer Python truth value of an arbitrary value. */
bool is_true(val value);

/* Resolve a name to an object. */
val lookup_name(ParathonContext& context, const std::string& s);

/* Turn an object into a stream, printing it. */
void print_value_to_stream(val value, std::ostream& s);
