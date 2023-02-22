#include "Value.hpp"

Value::Value(std::string const &value) : _value(value) {}

std::string
Value::get(void) const
{
	return _value;
}
