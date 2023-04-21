#include "StatusCodes.hpp"

#include "../../../inc/cgi.hpp"

int
test_cgi_exec(void)
{
	char	   *argument[4];
	std::string output;
	//	{
	//		std::cout << "test1\n";
	//		argument[0] = (char *)"/bin/echo";
	//		argument[1] = (char *)"salut";
	//		argument[2] = (char *)"";
	//		argument[3] = NULL;
	//
	//		CGI exec(argument[0], argument[1], argument[2]);
	////		CGI exec;
	////		exec.prepare_env(argument[0], argument[1], argument[2]);
	//		output = exec.execution_cgi();
	//		std::cout << "output echo: " << output << std::endl;
	//		if (output != "salut\n")
	//			return (1);
	//	}
	//	{
	//		std::cout << "test2\n";
	//		//		argument[0] = (char *) "/Users/kdi-noce/goinfre/bin/php-cgi";
	//		argument[0] = (char *)"/usr/bin/php";
	//		argument[1] = (char *)"test/src/cgi/env.php";
	//		argument[2] = (char *)"";
	//		argument[3] = NULL;
	//
	//		CGI exec(argument[0], argument[1], argument[2]);
	////		CGI exec;
	////		exec.prepare_env(argument[0], argument[1], argument[2]);
	//		output = exec.execution_cgi();
	//		std::cout << "output php: " << output << std::endl;
	//		if (output.find("hello World!") == std::string::npos)
	//			return (1);
	//	}
	{
		std::cout << "test3\n";
		std::cout << "bin/php-cgi" << std::endl;
		argument[0] = (char *)"./bin/php-cgi";
		argument[1] = (char *)"test/src/cgi/test.php";
		argument[2] = (char *)"";
		argument[3] = NULL;

		CGI exec(argument[0], argument[1], argument[2]);
		//		CGI exec;
		//		exec.prepare_env(argument[0], argument[1], argument[2]);
		output = exec.execution_cgi(argument[1]);
		std::cout << "output php-cgi: " << output << std::endl;
		if (output.find("hello World!") == std::string::npos)
			return (1);
	}
	return (0);
}
