#include "Unit_test.hpp"
#include "tests.hpp"

int
launcher_json(void)
{
	Unit_test list("json::t_object *json::read(char const *path)");

	list.load_test("normal JSON file", &test_json_normal_file);
	list.load_test("bad path", &test_json_bad_path);
	list.load_test("exception: empty string", &test_json_empty_string);
	list.load_test("exception: missing brace", &test_json_missing_brace);
	list.load_test("normal JSON number", &test_json_number);
	list.load_test("normal JSON string & number", &test_json_string_number);
	return (list.launch_tests());
}
