#include "Value.hpp"

Value::Value(std::string const &value) : _value(0) { _value = new std::string(value); }

Value::~Value(void) { delete _value; }

std::string
Value::get(void) const
{
	return *_value;
}

std::ostream &
operator<<(std::ostream &output, Value const &value)
{
	output << value.get();

	return output;
}
