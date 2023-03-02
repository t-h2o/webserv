#include "utils_json.hpp"

static int
open_file(std::fstream &file, char const *path)
{
	file.open(path, std::fstream::in);

	/* Check if the file is valid */
	if (file.is_open() == 0)
	{
		std::cerr << "Error: read(): file \"" << path << "\" is not valid" << std::endl;
		return 1;
	}
	return 0;
}

static int
read_process_lines(std::fstream &file, Config *config, bool states[NSTATES])
{
	std::string line;

	/* Read each lines up to EOF */
	for (getline(file, line); !file.eof(); getline(file, line))
	{
		try
		{
			_process_line(config, line, states);
		}
		catch (const std::runtime_error &e)
		{
			std::cerr << e.what() << std::endl;
			delete config;
			return 1;
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
			delete config;
			return 1;
		}
	}
	return 0;
}

static int
check_states_eof(bool states[NSTATES], Config *config)
{
	if (states[OBJECT] || states[STRING] || !states[KEY_FILLED] || states[MIDDLE] || !states[RIGHT]
		|| states[END])
	{
		std::cerr << "Json: object not finished by a '}'" << std::endl;
		delete config;
		return 1;
	}
	return 0;
}

Config *
read(char const *path)
{
	bool		 states[NSTATES];
	Config		*config;
	std::fstream file;

	memset(states, 0, sizeof(bool) * NSTATES);

	/* open the file */
	if (open_file(file, path))
		return 0;

	config = new Config;

	/* read file and fill config */
	if (read_process_lines(file, config, states))
		return 0;

	/* check states at the end of file */
	if (check_states_eof(states, config))
		return 0;

	file.close();

	return config;
}
