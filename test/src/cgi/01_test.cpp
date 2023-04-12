#include "../../../inc/cgi.hpp"
#include "StatusCodes.hpp"

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
		output = exec.execution_cgi();

		if (output != "salut\n")
			return (1);
	}
	{
		//		argument[0] = (char *) "/Users/kdi-noce/goinfre/bin/php-cgi";
		argument[0] = (char *)"/usr/bin/php";
		argument[1] = (char *)"test.php";
		argument[2] = (char *)"";
		argument[3] = NULL;

		CGI exec(argument[0], argument[1], argument[2]);
		output = exec.execution_cgi();
		//		std::cout << "output hello: " << output << std::endl;
		if (output != "hello World!")
			return (1);
	}
	{
		argument[0] = (char *)"bin/php-cgi";
		argument[1] = (char *)"test.php";
		argument[2] = (char *)"";
		argument[3] = NULL;

		CGI exec(argument[0], argument[1], argument[2]);
		output = exec.execution_cgi();
		std::cout << "output hello: " << output << std::endl;
		if (!output.find("hello World!"))
			return (1);
	}
	return (0);
}
