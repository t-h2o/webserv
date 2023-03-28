#include "Stream.hpp"

#include "arguments.hpp"

int
test_check_argc_number_1(void)
{
	Stream output;
	int	   fresutl;

	output.open();

	/* run the function to test */
	fresutl = arguments::check_argc_number(1);

	output.close();

	/* check the return value of the function */
	if (fresutl != 1)
		return 1;

	/* check stdout and stderr in one function of the function */
	if (output.check("", "Usage: webserv [CONFIGURATION_FILE]\n"))
		return 1;

	return 0;
}
