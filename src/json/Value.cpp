#include "Value.hpp"

namespace json
{

/* constructor */

Value::Value(void) : _value(0), _type(JSON_UNDEFINED)
{
	if (LOG_JSON_VALUE)
		std::cout << "json::Value: constructor " << _value << " JSON_UNDEFINED" << std::endl;
}

Value::Value(bool *value) : _value(value), _type(JSON_BOOLEAN)
{
	if (LOG_JSON_VALUE)
		std::cout << "json::Value: constructor " << _value << " JSON_BOOLEAN" << std::endl;
}

Value::Value(std::string *value) : _value(value), _type(JSON_STRING)
{
	if (LOG_JSON_VALUE)
		std::cout << "json::Value: constructor " << _value << "  JSON_STRING" << std::endl;
}

Value::Value(double *value) : _value(value), _type(JSON_NUMBER)
{
	if (LOG_JSON_VALUE)
		std::cout << "json::Value: constructor " << _value << "  JSON_NUMBER" << std::endl;
}

Value::Value(t_array *value) : _value(value), _type(JSON_ARRAY)
{
	if (LOG_JSON_VALUE)
		std::cout << "json::Value: constructor " << _value << "  JSON_ARRAY" << std::endl;
}

Value::Value(t_object *value) : _value(value), _type(JSON_OBJECT)
{
	if (LOG_JSON_VALUE)
		std::cout << "json::Value: constructor " << _value << "  JSON_OBJECT" << std::endl;
}

Value::Value(Value const &other) : _value(0), _type(JSON_UNDEFINED) { *this = other; }

/* destructor */

Value::~Value(void) { delete_value(); }

void
Value::delete_value(void)
{
	if (LOG_JSON_VALUE)
		std::cout << "json::Value: delete value and set to NULL : " << _value << std::endl;

	if (_type == JSON_STRING)
		delete static_cast<std::string *>(_value);
	else if (_type == JSON_NUMBER)
		delete static_cast<double *>(_value);
	else if (_type == JSON_ARRAY)
		delete static_cast<t_array *>(_value);
	else if (_type == JSON_BOOLEAN)
		delete static_cast<bool *>(_value);
	else if (_type == JSON_OBJECT)
		delete static_cast<t_object *>(_value);

	_value = 0;
}

/* operator */

Value &
Value::operator=(Value const &other)
{
	if (LOG_JSON_VALUE)
		std::cout << "json::Value: operator =" << std::endl;

	delete_value();
	_type = other._type;
	if (_type == JSON_STRING)
		_value = new std::string(other.get<std::string>());
	else if (_type == JSON_NUMBER)
		_value = new double(other.get<double>());
	else if (_type == JSON_BOOLEAN)
		_value = new bool(other.get<bool>());
	else if (_type == JSON_OBJECT)
		_value = new t_object(other.get<t_object>());
	else if (_type == JSON_ARRAY)
		_value = new t_array(other.get<t_array>());

	return *this;
}

Value &
Value::operator[](size_t const &index)
{
	return get<t_array>()[index];
}

/* getter */

size_t
Value::size(void) const
{
	return get<t_array>().size();
}

enum e_type
Value::get_type(void) const
{
	return _type;
}

Value &
Value::get(std::string const &key) const
{
	return get<t_object>().at(key);
}

/* extra */

std::ostream &
operator<<(std::ostream &output, json::t_array const &value)
{
	json::t_array::const_iterator start(value.begin());
	output << "[";
	for (size_t iteration(value.size()); iteration; --iteration)
	{
		output << *start++;
		if (iteration > 1)
			output << ", ";
	}
	output << "]";

	return output;
}

std::ostream &
operator<<(std::ostream &output, json::t_object const &value)
{
	json::t_object::const_iterator start(value.begin());
	output << "{";
	for (size_t iteration(value.size()); iteration; --iteration)
	{
		output << "\"" << start->first << "\" : " << start++->second;
		if (iteration > 1)
			output << ", ";
	}
	output << "}";

	return output;
}

std::ostream &
operator<<(std::ostream &output, Value const &value)
{
	if (value.get_type() == JSON_STRING)
		output << "\"" << value.get<std::string>() << "\"";
	else if (value.get_type() == JSON_NUMBER)
		output << value.get<double>();
	else if (value.get_type() == JSON_BOOLEAN)
		output << std::boolalpha << value.get<bool>() << std::noboolalpha;
	else if (value.get_type() == JSON_OBJECT)
		output << value.get<json::t_object>();
	else if (value.get_type() == JSON_ARRAY)
		output << value.get<json::t_array>();

	return output;
}

} /* namespace json */
