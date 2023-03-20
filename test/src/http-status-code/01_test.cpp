#include "StatusCodes.hpp"

int
test_status_code(void)
{
	http::StatusCode status_code;

	if (status_code.get_key_value_formated(100) != "100 Continue")
		return 1;

	if (status_code[100] != "Continue")
		return 1;

	return 0;
}
