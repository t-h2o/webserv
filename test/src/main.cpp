#include "tests.hpp"

int
main(void)
{
	int result;

	result = launch_arguments();
	result |= launch_arguments_argv();
	result |= launch_http_request();
	result |= launch_value();
	result |= launch_status_code();
	result |= launch_json();
	result |= launch_check_json_config();
	result |= launch_file();
//	result |= launch_execve_cgi();
	result |= launch_php();

	return result;
}
