#include <vector>

#include "Value.hpp"

int
test_value_array_number(void)
{
	std::vector<double> vec_double;

	vec_double.push_back(1);
	vec_double.push_back(2);
	vec_double.push_back(3);

	Value val1(vec_double);

	if (val1[0] != vec_double[0])
		return 1;

	if (val1[1] != vec_double[1])
		return 1;

	if (val1[2] != vec_double[2])
		return 1;

	if (val1.size() != vec_double.size())
		return 1;

	return 0;
}
