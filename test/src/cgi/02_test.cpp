#include "StatusCodes.hpp"

#include "../../../inc/cgi.hpp"

int
test_execve_cgi(void)
{
	std::string output;
	char	   *arguments[4];
	{
		arguments[0] = (char *)"bin/php-cgi";
		arguments[1] = (char *)"test/src/cgi/test.php";
		arguments[2] = (char *)"";
		arguments[3] = NULL;

		CGI exec(arguments[0], arguments[1], arguments[2]);
		output = exec.execution_cgi();
		std::cout << "output hello: " << output << std::endl;
		if (output.find("hello World!") == std::string::npos)
			return (1);
	}
	{
		arguments[0] = (char *)"bin/php-cgi";
		arguments[1] = (char *)"test/src/cgi/test3.php";
		arguments[2] = (char *)"";
		arguments[3] = NULL;

		CGI exec(arguments[0], arguments[1], arguments[2]);
		output = exec.execution_cgi();
		std::cout << "output hello: " << output << std::endl;
		if (output.find("My username is kdi-noce!") == std::string::npos)
			return (1);
	}
	return (0);
}
