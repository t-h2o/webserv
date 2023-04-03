#include "Unit_test.hpp"
#include "tests.hpp"

int
launch_value(void)
{
	Unit_test list("Value class");

	list.load_test("test string", &test_value_string);
	list.load_test("test number", &test_value_number);
	list.load_test("test boolean", &test_value_boolean);
	list.load_test("test array of numbers", &test_value_array_number);
	list.load_test("test map value", &test_value_map_value);
	list.load_test("test object and array", &test_value_object_array);
	return (list.launch_tests());
}
