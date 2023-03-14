#include "Unit_test.hpp"
#include "tests.hpp"

int
launch_file(void)
{
	Unit_test list("class http parser");

	list.load_test("simple instanciation", &test_file);
	return (list.launch_tests());
}
