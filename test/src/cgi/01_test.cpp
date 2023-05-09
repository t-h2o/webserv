#include "../../../inc/cgi.hpp"

#include "setting.hpp"

int
test_cgi_exec(void)
{
	char	   *argument[4];
	std::string output;
	{
		argument[0] = (char *)"/bin/echo";
		argument[1] = (char *)"salut";
		argument[2] = (char *)"";
		argument[3] = NULL;

		CGI exec(argument[0], argument[1], argument[2]);
		output = exec.execution_cgi(argument[1]);
		if (output != "salut\n")
			return (1);
	}
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
		argument[1] = (char *)"test/src/cgi/test.php";
		argument[2] = (char *)"";
		argument[3] = NULL;

		CGI exec(argument[0], argument[1], argument[2]);
		output = exec.execution_cgi(argument[1]);
		if (output.find("hello World!") == std::string::npos)
			return (1);
	}
	return (0);
}
