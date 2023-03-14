#include "Value.hpp"

int test_output(Json::Value const &, std::string const &);

int
test_value_array_number(void)
{
	Json::t_array *vec_double;

	vec_double = new Json::t_array;

	vec_double->push_back(new double(1));
	vec_double->push_back(new double(2));
	vec_double->push_back(new double(3));

	Json::Value val1(vec_double);

	if (val1[0].get<double>() != 1)
		return 1;

	if (val1[1].get<double>() != 2)
		return 1;

	if (val1[2].get<double>() != 3)
		return 1;

	if (val1.size() != 3)
		return 1;

	if (test_output(val1, "[1, 2, 3]\n"))
		return 1;

	return 0;
}
