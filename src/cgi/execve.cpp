#include "cgi.hpp"

int execution_cgi(char **envp)
{
	char *args[2];

	args[0] = (char *)("/bin/ls");
	args[1] = NULL;

	execve("/bin/ls", args, envp);
	std::cout << "error execve" << std::endl;

	return (0);
}
