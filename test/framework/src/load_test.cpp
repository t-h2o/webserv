#include "libunit.h"

static void append_node(t_unit_test *testlist, t_unit_test *new_node)
{
	while (testlist->next)
		testlist = testlist->next;
	testlist->next = new_node;
}

void load_test(t_unit_test **testlist, const std::string  name, int (*function_test)(void))
{
	t_unit_test *new_node;

	new_node = new t_unit_test;
	new_node->test_name = name;
	new_node->test_function = function_test;
	new_node->next = 0;
	if (*testlist == 0)
		*testlist = new_node;
	else
		append_node(*testlist, new_node);
}
