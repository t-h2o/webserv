#include "tests.hpp"

int
main(void)
{
	int result;

	result = arguments_launcher();
	result |= http_request_launcher();
	result |= value_launcher();
	result |= http_response_launcher();
	result |= status_code_launcher();
	result |= json_launcher();

	return result;
}
