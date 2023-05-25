#include <iostream>

namespace arguments
{

static void
print_help(void)
{
	std::cerr << "Usage: webserv [CONFIGURATION_FILE]" << std::endl;
}

int
check_argc_number(int argc)
{
	if (argc < 3)
		return 0;

	print_help();
	return 1;
}

} /* namespace arguments */
