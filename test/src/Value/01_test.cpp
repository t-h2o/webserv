#include "Value.hpp"

int
test_value_string(void)
{
	Value val1(new std::string("Hello"));
	Value val2 = Value(new std::string("World"));
	Value val3(val2);

	if (val1.get<std::string>() != "Hello")
		return 1;

	if (val2.get<std::string>() != "World")
		return 1;

	if (val3.get<std::string>() != "World")
		return 1;

	return 0;
}
