#include "StatusCodes.hpp"

#include "../../../inc/cgi.hpp"

int
test_cgi_exec(void)
{
	char	   *argument[4];
	std::string output;
	{
		std::cout << "test1" << std::endl;
		argument[0] = (char *)"/bin/echo";
		argument[1] = (char *)"salut";
		argument[2] = (char *)"";
		argument[3] = NULL;

		CGI exec(argument[0], argument[1], argument[2]);
		output = exec.execution_cgi(argument[1]);
		std::cout << "output echo: " << output << std::endl;
		if (output != "salut\n")
			return (1);
	}
	{
		std::cout << "test2" << std::endl;
		argument[0] = (char *)"/usr/bin/php";
		argument[1] = (char *)"test/src/cgi/test.php";
		argument[2] = (char *)"";
		argument[3] = NULL;

		CGI exec(argument[0], argument[1], argument[2]);
		output = exec.execution_cgi(argument[1]);
		std::cout << "output php: " << output << std::endl;
		if (output.find("hello World!") == std::string::npos)
			return (1);
	}
	{
		std::cout << "test3" << std::endl;
		argument[0] = (char *)"bin/php-cgi";
		argument[1] = (char *)"test/src/cgi/test.php";
		argument[2] = (char *)"";
		argument[3] = NULL;

		CGI exec(argument[0], argument[1], argument[2]);
		output = exec.execution_cgi(argument[1]);
		std::cout << "output php-cgi: " << output << std::endl;
		if (output.find("hello World!") == std::string::npos)
			return (1);
	}
	return (0);
}
