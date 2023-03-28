#include "Unit_test.hpp"
#include "tests.hpp"

int
launcher_arguments(void)
{
	Unit_test list("int check_argc_number(int)");

	list.load_test("good argument number (2)", &test_check_argc_number_2);
	list.load_test("bad argument number (1)", &test_check_argc_number_1);
	return (list.launch_tests());
}
