#include "tests.hpp"

int
main(void)
{
	int result;

	result = f_launcher();
	result |= arguments_launcher();

	return result;
}
