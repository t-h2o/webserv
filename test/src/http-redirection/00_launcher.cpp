#include "Unit_test.hpp"
#include "tests.hpp"

int
launch_http_redirection(void)
{
	Unit_test list("http::Redirection");

	list.load_test("test", &test_http_redirection);
	return (list.launch_tests());
}
