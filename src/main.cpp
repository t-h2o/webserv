#include "arguments.hpp"
#include "webserver.hpp"

#define DEFAULT_CONFIG "./config.json"

int
main(int argc, char **argv)
{
	if (arguments::check_argc_number(argc))
		return 1;

	if (argc == 2)
	{
		if (arguments::check_argv_access(argv[1]))
			return 1;

		return webserver(argv[1]);
	}
	else if (argc == 1)
	{
		if (arguments::check_argv_access(DEFAULT_CONFIG))
			return 1;

		return webserver(DEFAULT_CONFIG);
	}
}
