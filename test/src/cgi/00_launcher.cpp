#include "Unit_test.hpp"
#include "tests.hpp"

int
launch_execve_cgi(void)
{
	Unit_test list("execve cgi");

	list.load_test("simple test", &test_cgi_exec);
	list.load_test("test_with_execve", &test_execve_cgi);
	list.load_test("test_execve_var_env", &test_execve_cgi_env);
	return (list.launch_tests());
}
