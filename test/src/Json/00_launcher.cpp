#include "Unit_test.hpp"
#include "tests.hpp"

int
json_launcher(void)
{
	Unit_test list("Config *read(char const *path)");

	list.load_test("normal JSON file", &test_json_normal_file);
	list.load_test("bad path", &test_json_bad_path);
	list.load_test("exception: empty string", &test_json_empty_string);
	list.load_test("exception: missing brace", &test_json_missing_brace);
	return (list.launch_tests());
}
