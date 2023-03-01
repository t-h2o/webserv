#include "Unit_test.hpp"
#include "tests.hpp"

int
config_launcher(void)
{
	Unit_test list("Config class");

	list.load_test("insert", &test_config_insert);
	list.load_test("get", &test_config_get);

	return (list.launch_tests());
}
