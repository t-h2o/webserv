#include "utils_json.hpp"

namespace json
{

static int
read_process_lines(File &file, t_object *config, bool states[NSTATES])
{
	if (file.get_char() != '{')
		return 1;
	try
	{
		_process_line(config, file, states);
	}
	catch (const std::runtime_error &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}

t_object *
read(char const *path)
{
	bool	  states[NSTATES];
	t_object *config;
	File	  file(path);

	/* set at 0 each values of states */
	std::memset(states, 0, sizeof(bool) * NSTATES);

	config = new t_object;

	/* read file and fill config */
	if (read_process_lines(file, config, states))
	{
		delete config;
		return 0;
	}

	return config;
}

} /* namespace json */
