#include "StatusCodes.hpp"

#include "../../../inc/cgi.hpp"

int
test_execve_cgi(void)
{
	std::string output;
	char	   *arguments[4];
	{
		arguments[0] = (char *)"bin/php-cgi";
		arguments[1] = (char *)"test.php";
		arguments[2] = (char *)"?q=abstract%20api";
		arguments[3] = NULL;

		CGI exec(arguments[0], arguments[1], arguments[2]);
		output = exec.execution_cgi();
		std::cout << "output hello: " << output << std::endl;
		if (!output.find("Hello World!"))
			return (1);
	}
	{
		arguments[0] = (char *)"bin/php-cgi";
		arguments[1] = (char *)"test.php";
		arguments[2] = (char *)"?q=abstract%20api";
		arguments[3] = NULL;

		CGI exec(arguments[0], arguments[1], arguments[2]);
		output = exec.execution_cgi();
		std::cout << "output hello: " << output << std::endl;
		if (!output.find("Hello World!"))
			return (1);
	}
	{
		arguments[0] = (char *)"bin/php-cgi";
		arguments[1] = (char *)"test3.php";
		arguments[2] = (char *)"?q=abstract%20api";
		arguments[3] = NULL;

		CGI exec(arguments[0], arguments[1], arguments[2]);
		output = exec.execution_cgi();
		if (!output.find("My username is kdi-noce!"))
			return (1);
	}
	return (0);
}
