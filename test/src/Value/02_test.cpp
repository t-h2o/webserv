#include "Value.hpp"

int test_output(json::Value const &, std::string const &);

int
test_value_number(void)
{
	json::Value val1(new double(42));
	json::Value val2 = json::Value(new double(1234.5678));
	json::Value val3(val2);

	if (val1.get<double>() != 42)
		return 1;

	if (val2.get<double>() != 1234.5678)
		return 1;

	if (val3.get<double>() != 1234.5678)
		return 1;

	if (test_output(val1, "42\n"))
		return 1;

	if (test_output(val2, "1234.57\n"))
		return 1;

	if (test_output(val3, "1234.57\n"))
		return 1;

	return 0;
}
