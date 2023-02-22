#include "arguments.hpp"

/* check_argc_number()
 * If the argc number is equal to 2, return 0 else return 1
 */

int
test_check_argc_number(void)
{
	if (check_argc_number(1) != 1)
		return 1;
	if (check_argc_number(3) != 1)
		return 1;

	if (check_argc_number(2) != 0)
		return 1;

	return 0;
}
