#include "Unit_test.hpp"
#include "tests.hpp"

int
value_launcher(void)
{
	Unit_test list("Value class");

	list.load_test("test string", &test_value_string);
	return (list.launch_tests());
}
