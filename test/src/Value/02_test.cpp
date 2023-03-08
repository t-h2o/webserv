#include "Value.hpp"

int
test_value_number(void)
{
	Value val1(new double(42));
	Value val2 = Value(new double(1234.5678));
	Value val3(val2);

	if (val1.get<double>() != 42)
		return 1;

	if (val2.get<double>() != 1234.5678)
		return 1;

	if (val3.get<double>() != 1234.5678)
		return 1;

	std::cout << val1 << std::endl;

	return 0;
}
