#include "Unit_test.hpp"
#include "tests.hpp"

int
value_launcher(void)
{
	Unit_test list("Value class");

	list.load_test("test string", &test_value_string);
	list.load_test("test number", &test_value_number);
	list.load_test("test boolean", &test_value_boolean);
	list.load_test("test array of numbers", &test_value_array_number);
	return (list.launch_tests());
}
