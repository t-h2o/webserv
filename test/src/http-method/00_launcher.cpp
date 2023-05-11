#include "Unit_test.hpp"
#include "tests.hpp"

int
launch_http_method(void)
{
	Unit_test list("http::Method");

	list.load_test("test", &test_http_method);
	return (list.launch_tests());
}
