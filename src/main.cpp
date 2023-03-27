#include "arguments.hpp"
#include "webserver.hpp"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int
main(int argc, char **argv, char **envp)
{
	if (check_argc_number(argc))
		return 1;

	return webserver(argv[1], envp);
}
