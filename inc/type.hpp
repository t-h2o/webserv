#ifndef TYPE_HPP
#define TYPE_HPP

namespace json
{

class Value;

typedef std::map<std::string, Value> t_object;
typedef std::vector<Value>			 t_array;

enum e_type
{
	JSON_UNDEFINED,
	JSON_STRING,
	JSON_NUMBER,
	JSON_ARRAY,
	JSON_BOOLEAN,
	JSON_OBJECT,
};

} /* namespace json */

#endif /* TYPE_HPP */
