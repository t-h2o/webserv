#include "Unit_test.hpp"
#include "tests.hpp"

int
config_launcher(void)
{
	Unit_test list("Config class");

	list.load_test("insert", &test_config_insert);

	return (list.launch_tests());
}
