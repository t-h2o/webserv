#include "Value.hpp"

Value::Value(std::string const &value) : _value(0) { _value = new std::string(value); }

Value::~Value(void) { delete static_cast<std::string *>(_value); }

std::string
Value::get(void) const
{
	return *static_cast<std::string *>(_value);
}

std::ostream &
operator<<(std::ostream &output, Value const &value)
{
	output << value.get();

	return output;
}
