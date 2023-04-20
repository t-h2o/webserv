#include "arguments.hpp"
#include "webserver.hpp"
#include "../inc/cgi.hpp"

int
main(int argc, char **argv)
{
	char *argsss[3];

	argsss[0] = (char *)"./bin/php-cgi";
	argsss[1] = (char *)"test/src/cgi/test.php";
	argsss[2] = 0;

	std::vector<char *> popol;

	popol.push_back(argsss[0]);
	popol.push_back(argsss[1]);
	popol.push_back(argsss[2]);


	execve(popol[0], &(popol[0]), 0);
	return 0;

	if (arguments::check_argc_number(argc))
		return 1;

	if (arguments::check_argv_access(argv[1]))
		return 1;

	return webserver(argv[1]);
}
