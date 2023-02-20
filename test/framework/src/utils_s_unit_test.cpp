#include "libunit.h"

void iter_list(t_unit_test *testlist, void (*f)(t_unit_test *))
{
	t_unit_test	*next;

	while (testlist)
	{
		next = testlist->next;
		f(testlist);
		testlist = next;
	}
}
