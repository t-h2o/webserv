#include "arguments.hpp"
#include "webserver.hpp"

int
main(int argc, char **argv)
{
	if (arguments::check_argc_number(argc))
		return 1;

	if (arguments::check_argv_access(argv[1]))
		return 1;

	return webserver(argv[1]);
}
