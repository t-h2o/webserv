#include "Unit_test.hpp"
#include "tests.hpp"

int
launch_arguments_argv(void)
{
	Unit_test list("argument::check_argv_access(pathname)");

	list.load_test("valid", &test_check_argv_access_valid);
	list.load_test("unvalid", &test_check_argv_access_unvalid);
	return (list.launch_tests());
}
