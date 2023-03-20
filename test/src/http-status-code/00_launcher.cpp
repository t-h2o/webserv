#include "Unit_test.hpp"
#include "tests.hpp"

int
status_code_launcher(void)
{
	Unit_test list("class status code");

	list.load_test("get_key_value_formated(int)", &test_status_code);
	return (list.launch_tests());
}
