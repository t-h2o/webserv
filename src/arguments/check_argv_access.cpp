#include <iostream>
#include <unistd.h>

namespace arguments
{

static void
print_help(const char *pathname)
{
	std::cerr << "Error: cannot access to \"" << pathname << '"' << std::endl;
}

int
check_argv_access(const char *pathname)
{
	if (access(pathname, R_OK) == 0)
		return 0;

	print_help(pathname);
	return 1;
}

} /* namespace arguments */
