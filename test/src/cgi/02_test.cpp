#include "StatusCodes.hpp"

#include "../../../inc/cgi.hpp"

#define PATH_CGI_PHP "/Users/tgrivel/goinfre/php/php-8.2.5/sapi/cgi/php-cgi"
#define WHOAMI "tgrivel"

int
test_execve_cgi(void)
{
	std::string output;
	char	   *argument[4];
	{
		argument[0] = (char *)PATH_CGI_PHP;
		argument[1] = (char *)"test/src/cgi/test.php";
		argument[2] = (char *)"";
		argument[3] = NULL;

		CGI exec(argument[0], argument[1], argument[2]);
		output = exec.execution_cgi(argument[1]);
		if (output.find("hello World!") == std::string::npos)
			return (1);
	}
	{
		argument[0] = (char *)PATH_CGI_PHP;
		argument[1] = (char *)"test/src/cgi/test3.php";
		argument[2] = (char *)"";
		argument[3] = NULL;

		CGI exec(argument[0], argument[1], argument[2]);
		output = exec.execution_cgi(argument[1]);
		if (output.find("My username is "WHOAMI) == std::string::npos)
		{
			std::cout << "in 5" << std::endl;
			return (1);
		}
	}
	return (0);
}
