#include "Unit_test.hpp"
#include "tests.hpp"

int
cgi_launcher(void)
{
	Unit_test list("execve cgi");

	list.load_test("simple test", &test_cgi);
	return (list.launch_tests());
}
