#include "Value.hpp"

namespace json
{

/* constructor */

Value::Value(void) : _value(0), _type(JSON_UNDEFINED) {}

Value::Value(bool *value) : _value(value), _type(JSON_BOOLEAN) {}

Value::Value(std::string *value) : _value(value), _type(JSON_STRING) {}

Value::Value(double *value) : _value(value), _type(JSON_NUMBER) {}

Value::Value(t_array *value) : _value(value), _type(JSON_ARRAY) {}

Value::Value(t_object *value) : _value(value), _type(JSON_OBJECT) {}

Value::Value(Value const &other) { *this = other; }

/* destructor */

Value::~Value(void)
{
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
}

/* operator */

Value &
Value::operator=(Value const &other)
{
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
	return get<t_object>().find(key)->second;
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
