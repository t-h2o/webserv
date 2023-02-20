#include "libunit.h"
#include "utils.h"

static void do_test(t_unit_test *testlist)
{
	pid_t pid;
	int sig;
	int res;

	testlist->result = unknown;
	pid = fork();
	if (!pid) {
		res = testlist->test_function();
		if (res == 1)
			exit(1);
		exit(0);
	}
	else
	{
		pid = wait(&sig);
		if (!pid)
			return ;
		testlist->result = catch_res(sig);
	}
}

static void print_result(t_unit_test *testlist)
{
	std::cout << "function : " << testlist->test_name << " : ";
	if (testlist->result == OK)
		std::cout << "[OK]\n";
	else if (testlist->result == KO)
		std::cout << "[KO]\n";
	else if (testlist->result == sigsegv)
		std::cout << "[SEGV]\n";
	else if (testlist->result == sigbus)
		std::cout << "[BUS]\n";
	else if (testlist->result == sigabrt)
		std::cout << "[ABRT]\n";
	else if (testlist->result == sigfpe)
		std::cout << "[FPE]\n";
	else if (testlist->result == sigpip)
		std::cout << "[PIP]\n";
	else if (testlist->result == sigill)
		std::cout << "[ILL]\n";
	else
		std::cout << "\n";
}

static void free_node(t_unit_test *testlist)
{
	delete testlist;
}

static void last_line(t_unit_test *testlist)
{
	int	tests;
	int success;

	tests = 0;
	success = 0;
	while (testlist && ++tests && (testlist->result || ++success))
		testlist = testlist->next;
	std::cout << "\n";
	std::cout << success;
	std::cout << "/";
	std::cout << tests;
	std::cout << " tests checked\n";
}

int launch_tests(t_unit_test **testlist)
{
	iter_list(*testlist, &do_test);
	iter_list(*testlist, &print_result);
	last_line(*testlist);
	iter_list(*testlist, &free_node);
	return (0);
}
