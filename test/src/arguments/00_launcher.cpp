#include "Unit_test.hpp"
#include "tests.hpp"

int
arguments_launcher(void)
{
	Unit_test list("int check_argc_number(int)");

	list.load_test("test check_argc_number()", &test_check_argc_number);
	return (list.launch_tests());
}
