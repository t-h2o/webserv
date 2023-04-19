#include "Stream.hpp"

#include "arguments.hpp"

int
test_check_argv_access_valid(void)
{
	Stream output;
	int	   fresutl;

	output.open();

	/* run the function to test */
	fresutl = arguments::check_argv_access("config.json");

	output.close();

	/* check the return value of the function */
	if (fresutl != 0)
		return 1;

	/* check stdout and stderr in one function of the function */
	if (output.check("", ""))
		return 1;

	return 0;
}
