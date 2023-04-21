#include "StatusCodes.hpp"

#include "../../../inc/cgi.hpp"

int
test_execve_cgi(void)
{
	std::string output;
	char	   *argument[4];
	{
		argument[0] = (char *)"bin/php-cgi";
		argument[1] = (char *)"test/src/cgi/test.php";
		argument[2] = (char *)"";
		argument[3] = NULL;

		CGI exec(argument[0], argument[1], argument[2]);
//		CGI exec;
//		exec.prepare_env(argument[0], argument[1], argument[2]);
		output = exec.execution_cgi(argument[1]);
		std::cout << "output hello: " << output << std::endl;
		if (output.find("hello World!") == std::string::npos)
			return (1);
	}
	{
		argument[0] = (char *)"bin/php-cgi";
		argument[1] = (char *)"test/src/cgi/test3.php";
		argument[2] = (char *)"";
		argument[3] = NULL;

		CGI exec(argument[0], argument[1], argument[2]);
//		CGI exec;
//		exec.prepare_env(argument[0], argument[1], argument[2]);
		output = exec.execution_cgi(argument[1]);
		std::cout << "output hello: " << output << std::endl;
		if (output.find("My username is kdi-noce!") == std::string::npos)
			return (1);
	}
	return (0);
}
