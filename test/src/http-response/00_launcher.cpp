#include "Unit_test.hpp"
#include "tests.hpp"

int
http_response_launcher(void)
{
	Unit_test list("class http response");

	list.load_test("response", &test_http_response);
	return (list.launch_tests());
}