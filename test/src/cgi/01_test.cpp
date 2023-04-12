#include "StatusCodes.hpp"
#include <string>

std::string execution_cgi(char **arguments);

int
test_execve_cgi(void)
{
	char	   *arguments[3];
	std::string output;

	arguments[0] = (char *)"/bin/echo";
	arguments[1] = (char *)"salut";
	arguments[2] = NULL;

	output = execution_cgi(arguments);

	if (output != "salut\n")
		return (1);
	std::cout << "success" << std::endl;
	return (0);
}
