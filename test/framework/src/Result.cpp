#include "Result.hpp"
#include <sys/wait.h>

void
Result::print_result(void) const
{
	if (_result == OK)
		std::cout << "[OK]\n";
	else if (_result == KO)
		std::cout << "[KO]\n";
	else if (_result == sigsegv)
		std::cout << "[SEGV]\n";
	else if (_result == sigbus)
		std::cout << "[BUS]\n";
	else if (_result == sigabrt)
		std::cout << "[ABRT]\n";
	else if (_result == sigfpe)
		std::cout << "[FPE]\n";
	else if (_result == sigpip)
		std::cout << "[PIP]\n";
	else if (_result == sigill)
		std::cout << "[ILL]\n";
	else
		std::cout << "\n";
}

void
Result::set_result(int signal)
{
	int status;

	if (WIFEXITED(signal))
	{
		status = WEXITSTATUS(signal);
		if (status == 0)
			_result = OK;
		else
			_result = KO;
	}
	else if (WIFSIGNALED(signal))
	{
		status = WTERMSIG(signal);
		if (status == SIGBUS)
			_result = sigbus;
		if (status == SIGSEGV)
			_result = sigsegv;
		if (status == SIGABRT)
			_result = sigabrt;
		if (status == SIGFPE)
			_result = sigfpe;
		if (status == SIGPIPE)
			_result = sigpip;
		if (status == SIGILL)
			_result = sigill;
	}
	else
		_result = unknown;
}

bool
Result::failed(void) const
{
	return _result;
}
