#include "Unit_test.hpp"
#include "tests.hpp"

int
launch_file(void)
{
	Unit_test list("class File");

	list.load_test("simple instanciation", &test_file);
	list.load_test("read all a file", &test_file_all_file);
	list.load_test("not valid file", &test_file_not_valid_file);
	list.load_test("get string", &test_file_get_string);
	list.load_test("get number", &test_file_get_number);
	list.load_test("get string: empty string", &test_file_get_string_empty_string);
	return (list.launch_tests());
}
