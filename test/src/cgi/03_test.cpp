#include "StatusCodes.hpp"

#include "../../../inc/cgi.hpp"

int
test_execve_cgi_env(void)
{
	std::string output;
	char	   *arguments[4];
	{
		std::cout << "test6" << std::endl;
		arguments[0] = (char *)"bin/php-cgi";
		arguments[1] = (char *)"test/src/cgi/env.php";
		arguments[2] = (char *)"";
		arguments[3] = NULL;

		CGI exec(arguments[0], arguments[1], arguments[2]);
		output = exec.execution_cgi(arguments[1]);
		std::cout << "output hello: " << output << std::endl;
		if (output.find("passed") == std::string::npos)
			return (1);
	}
	return (0);
}
