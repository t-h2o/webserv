#include "Unit_test.hpp"
#include "tests.hpp"

int
launch_php(void)
{
	Unit_test list("php");

	list.load_test("check_webs_output_php", &test_php_output);
	list.load_test("check_cgi_php", &test_cgi_with_php);
	list.load_test("set_query_env", &test_cgi_with_php_query);
	list.load_test("query_to_parameter", &test_cgi_with_php_query2);
	return (list.launch_tests());
}
