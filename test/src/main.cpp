#include "tests.hpp"

#include <iostream>
int
main(void)
{
	int result;

	result = arguments_launcher();
	result |= json_launcher();

	return result;
}
