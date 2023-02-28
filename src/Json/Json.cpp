#include "utils_json.hpp"

Config *
read(char const *path)
{
	bool		 states[NSTATES];
	Config		*config;
	std::fstream file;
	std::string	 line;

	memset(states, 0, sizeof(bool) * NSTATES);
	file.open(path, std::fstream::in);

	/* Check if the file is valid */
	if (file.is_open() == 0)
	{
		std::cerr << "Error: read(): file \"" << path << "\" is not valid" << std::endl;
		return 0;
	}

	config = new Config;

	/* Read each lines up to EOF */
	for (getline(file, line); !file.eof(); getline(file, line))
		_process_line(config, line, states);

	if (states[OBJECT])
		throw std::runtime_error("Json: object not finished by a '}'");

	file.close();

	return config;
}
