#include "Unit_test.hpp"
#include "tests.hpp"

int
launch_http_request(void)
{
	Unit_test list("class http parser");

	list.load_test("method GET", &test_http_request);
	return (list.launch_tests());
}
