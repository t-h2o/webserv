#include "f.hpp"

/* check if f() return 1 */
int
f_test_true (void)
{
	if (f ())
		return 0;
	return 1;
}
