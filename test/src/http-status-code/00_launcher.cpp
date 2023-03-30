#include "Unit_test.hpp"
#include "tests.hpp"

int
launch_status_code(void)
{
	Unit_test list("class status code");

	list.load_test("get_key_value_formated(int)", &test_status_code);
	return (list.launch_tests());
}
