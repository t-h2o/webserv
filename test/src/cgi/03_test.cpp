#include "StatusCodes.hpp"

#include "../../../inc/cgi.hpp"

int
test_execve_cgi_env(void)
{
	std::string output;
	char	   *arguments[4];
	{
		arguments[0] = (char *)"bin/php-cgi";
		arguments[1] = (char *)"test/src/cgi/env.php";
		arguments[2] = (char *)"";
		arguments[3] = NULL;

		CGI exec(arguments[0], arguments[1], arguments[2]);
//		CGI exec;
//		exec.prepare_env(arguments[0], arguments[1], arguments[2]);
		output = exec.execution_cgi(arguments[1]);
		std::cout << "output hello: " << output << std::endl;
//		assert(exec.get_env("CONTENT_LENGTH") == "19");
//		std::cout << "assert = " << exec.get_env("CONTENT_LENGTH") << std::endl;
//		assert(exec.get_env("AUTH_TYPE") == "null");
//		std::cout << "assert = " << exec.get_env("AUTH_TYPE") << std::endl;
//		assert(exec.get_env("GATEWAY_INTERFACE") == "CGI/1.1");
//		std::cout << "assert = " << exec.get_env("GATEWAY_INTERFACE") << std::endl;
		//		if (output.find("CGI/1.1") == std::string::npos)
		//			return (1);
	}
	return (0);
}

