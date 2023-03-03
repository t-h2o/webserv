#include "Value.hpp"

/* constructor */

Value::Value(void) : _value(0), _type(V_UNDEFINED) {}

Value::Value(bool *value) : _value(value), _type(V_BOOLEAN) {}

Value::Value(std::string *value) : _value(value), _type(V_STRING) {}

Value::Value(double *value) : _value(value), _type(V_NUMBER) {}

Value::Value(std::vector<double> *value) : _value(value), _type(V_VEC_NUMBER) {}

Value::Value(std::map<std::string, Value> *value) : _value(value), _type(V_OBJECT) {}

Value::Value(Value const &other) { *this = other; }

/* destructor */

Value::~Value(void)
{
	if (_type == V_STRING)
		delete static_cast<std::string *>(_value);
	else if (_type == V_NUMBER)
		delete static_cast<double *>(_value);
	else if (_type == V_VEC_NUMBER)
		delete static_cast<std::vector<double> *>(_value);
	else if (_type == V_BOOLEAN)
		delete static_cast<bool *>(_value);
	else if (_type == V_OBJECT)
		delete static_cast<std::map<std::string, Value> *>(_value);
}

/* operator */

Value &
Value::operator=(Value const &other)
{
	_type = other._type;

	if (_type == V_STRING)
		_value = new std::string(other.get<std::string>());
	else if (_type == V_NUMBER)
		_value = new double(other.get<double>());
	else if (_type == V_BOOLEAN)
		_value = new bool(other.get<bool>());
	else if (_type == V_OBJECT)
		_value = new std::map<std::string, Value>(*static_cast<std::map<std::string, Value> *>(other._value));

	return *this;
}

double
Value::operator[](size_t const &index)
{
	return static_cast<std::vector<double> *>(_value)->at(index);
}

size_t
Value::size(void) const
{
	return static_cast<std::vector<double> *>(_value)->size();
}

enum e_type
Value::get_type(void) const
{
	return _type;
}

/* extra */

std::ostream &
operator<<(std::ostream &output, Value const &value)
{
	if (value.get_type() == V_STRING)
		output << value.get<std::string>();
	else if (value.get_type() == V_NUMBER)
		output << value.get<double>();
	else if (value.get_type() == V_BOOLEAN)
		output << value.get<bool>();

	return output;
}
