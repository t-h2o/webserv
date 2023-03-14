#include "tests.hpp"

int
main(void)
{
	int result;

	result = launch_arguments();
	result |= launch_http_request();
	result |= launch_value();
	result |= launch_http_response();
	result |= launch_status_code();
	result |= launch_json();
	result |= launch_file();

	return result;
}
