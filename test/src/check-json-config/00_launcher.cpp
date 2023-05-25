#include "Unit_test.hpp"
#include "tests.hpp"

int
launch_check_json_config(void)
{
	Unit_test list("json::check_config(t_object *config)");

	list.load_test("normal JSON file", &test_json_check_config_normal);
	list.load_test("bad port JSON file", &test_json_check_config_bad_port);

	return (list.launch_tests());
}
