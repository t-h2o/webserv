#include "tests.hpp"

int
main(void)
{
	int result;

	result = launcher_arguments();
	result |= launcher_http_request();
	result |= launcher_value();
	result |= launcher_http_response();
	result |= launcher_status_code();
	result |= launcher_json();

	return result;
}
