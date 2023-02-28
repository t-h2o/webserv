#include "Value.hpp"

Value::Value(std::string const &value) : _value(0), _type(V_STRING) { _value = new std::string(value); }

Value::Value(double const &value) : _value(0), _type(V_NUMBER) { _value = new double(value); }

Value::~Value(void)
{
	if (_type == V_STRING)
		delete static_cast<std::string *>(_value);
	else if (_type == V_NUMBER)
		delete static_cast<double *>(_value);
}

template <typename T>
T
Value::get(void) const
{
	return *static_cast<T *>(_value);
}

int
Value::get_type(void) const
{
	return _type;
}

std::ostream &
operator<<(std::ostream &output, Value const &value)
{
	if (value.get_type() == V_STRING)
		output << value.get<std::string>();
	else if (value.get_type() == V_NUMBER)
		output << value.get<double>();

	return output;
}
