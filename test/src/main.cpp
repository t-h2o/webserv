#include "tests.hpp"

#include <iostream>
int
main(void)
{
	int result;

	result = arguments_launcher();
	result |= config_launcher();
	result |= json_launcher();
	result |= value_launcher();

	return result;
}
