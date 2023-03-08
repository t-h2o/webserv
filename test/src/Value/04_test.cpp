#include "Value.hpp"

int test_output(Value const &, std::string const &);

int
test_value_boolean(void)
{
	Value val1(new bool(true));
	Value val2 = Value(new bool(false));
	Value val3(val2);

	if (val1.get<bool>() != true)
		return 1;

	if (val2.get<bool>() != false)
		return 1;

	if (val3.get<bool>() != false)
		return 1;

	if (test_output(val1, "true\n"))
		return 1;

	if (test_output(val2, "false\n"))
		return 1;

	if (test_output(val3, "false\n"))
		return 1;

	return 0;
}
