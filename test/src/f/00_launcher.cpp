#include "Unit_test.hpp"
#include "tests.hpp"
#include <stdio.h>

int
f_launcher(void)
{
	Unit_test list("f");

	list.load_test("test true", &f_test_true);
	return (list.launch_tests());
}
