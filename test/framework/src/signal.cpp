//
// Created by tywael on 2/12/23.
//

#include "libunit.h"

enum e_result catch_res(int signal)
{
	int status;

	if (WIFEXITED(signal))
	{
		status = WEXITSTATUS(signal);
		if (status == 0)
			return (OK);
		else
			return KO;
	}
	if (WIFSIGNALED(signal))
	{
		status = WTERMSIG(signal);
		if (status == SIGBUS)
			return (sigbus);
		if (status == SIGSEGV)
			return (sigsegv);
		if (status == SIGABRT)
			return (sigabrt);
		if (status == SIGFPE)
			return (sigfpe);
		if (status == SIGPIPE)
			return (sigpip);
		if (status == SIGILL)
			return (sigill);
	}
	return (unknown);
}
