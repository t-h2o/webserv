#include "libunit.h"
#include "tests.hpp"
#include <stdio.h>

int
f_launcher (void)
{
	t_unit_test *list = 0;

	printf ("Hello world\n");
	load_test (&list, "test true", &f_test_true);
	return (launch_tests (&list));
}
