#include "../../../inc/cgi.hpp"

#define PATH_CGI_PHP "/Users/tgrivel/goinfre/php/php-8.2.5/sapi/cgi/php-cgi"

int
test_execve_cgi_env(void)
{
	std::string output;
	char	   *arguments[4];
	{
		arguments[0] = (char *)"/usr/bin/php-cgi";
		arguments[1] = (char *)"test/src/cgi/env.php";
		arguments[2] = (char *)"";
		arguments[3] = NULL;

		CGI exec(arguments[0], arguments[1], arguments[2]);
		output = exec.execution_cgi(arguments[1]);
		if (output.find("failed.") != std::string::npos)
			return (1);
	}
	{
		arguments[0] = (char *)"/usr/bin/php-cgi";
		arguments[1] = (char *)"test/src/cgi/input.php";
		arguments[2] = (char *)"";
		arguments[3] = NULL;

		CGI exec(arguments[0], arguments[1], arguments[2]);
		output = exec.execution_cgi(arguments[1]);
		if (output.find("?php") != std::string::npos)
			return (1);
	}
	return (0);
}
