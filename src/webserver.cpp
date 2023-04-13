
#include "../inc/cgi.hpp"
#include "Json.hpp"
#include "cgi.hpp"
#include "serverTest.hpp"

int
webserver(const char *path_config_file)
{
	std::cout << "Web server written in C++98" << std::endl;
	json::t_object *config(0);

	if (json::load_config(path_config_file, &config))
		return 1;

	std::cout << *config << std::endl;

	serverTest(config);

	delete config;
	return 0;
	//	(void)path;
	//	char	   *argument[4];
	//	std::string output;
	//
	//	argument[0] = (char *)"/Users/kdi-noce/goinfre/bin/php-cgi";
	//	// The php file who contain phpinfo(), a big configuration function.
	//	argument[1] = (char *)"../test.php";
	//	argument[2] = (char *)"q=music&l=Web";
	//	argument[3] = NULL;
	//
	//	CGI exec(argument[0], argument[1], argument[2]);
	//		std::cout << "Web server written in C++98" << std::endl;
	//	output = exec.execution_cgi();
	//
	//	return (0);
}
