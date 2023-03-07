#include "Test.hpp"
#include <stdlib.h>

Test::Test(std::string const &name, int (*function_ptr)(void)) : _name(name), _function_ptr(function_ptr) {}

void
Test::do_test(void)
{
	pid_t pid;
	int	  sig;
	int	  res;

	pid = fork();
	if (!pid)
	{
		res = _function_ptr();
		if (res == 1)
			exit(1);
		exit(0);
	}
	else
	{
		pid = wait(&sig);
		if (!pid)
			return;
		_result.set_result(sig);
	}
}
