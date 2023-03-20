#include "tests.hpp"

int
main(void)
{
	int result;

	result = arguments_launcher();
	result |= http_request_launcher();

	return result;
}
