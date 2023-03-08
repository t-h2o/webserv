#include "Value.hpp"

int
test_value_array_number(void)
{
	Value::t_array *vec_double;

	vec_double = new Value::t_array;

	vec_double->push_back(new double(1));
	vec_double->push_back(new double(2));
	vec_double->push_back(new double(3));

	Value val1(vec_double);

	if (val1[0].get<double>() != 1)
		return 1;

	if (val1[1].get<double>() != 2)
		return 1;

	if (val1[2].get<double>() != 3)
		return 1;

	if (val1.size() != 3)
		return 1;

	std::cout << val1 << std::endl;

	return 0;
}
