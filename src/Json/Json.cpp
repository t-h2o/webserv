#include "Json.hpp"

#define WHITESPACE 0
#define OBJECT 1
#define STRING 2
#define KEY_FILLED 3

/* get the string value */
std::string
Json::_get_string(std::string const &line, size_t &index)
{
	std::string value;

	while (line[index] && line[index] != '"')
		value += line[index++];

	if (value == "")
		throw std::runtime_error("Json: _get_string():\n" + line + "\nempty string");

	return value;
}

/* loop up to reach end of string or not a blank character */
void
Json::_loop_isblank(std::string const &line, size_t &index)
{
	while (line[index] && isblank(line[index]))
		++index;
}

/* process a line of the json */
void
Json::_process_line(Config *config, std::string const &line, bool states[NSTATES])
{
	size_t		index(0);

	while (line[index])
	{
		if (isblank(line[index]))
		{
			states[WHITESPACE] = 1;
			_loop_isblank(line, index);
		}
		else
		{
			if (line[index] == '{')
			{
				states[OBJECT] = 1;
			}
			if (line[index] == '}')
			{
				if (states[OBJECT] == 0)
					throw std::runtime_error("Json: object didn't start by a '{'");
				states[OBJECT] = 0;
			}
			if (line[index] == '"')
			{
				states[STRING] ^= 1;
			}
			states[WHITESPACE] = 0;
			++index;
		}

		if (states[STRING])
		{
			Value *value = new Value(_get_string(line, index));
			if (states[KEY_FILLED] == 0)
			{
				config->insert_key(value->get());
				states[KEY_FILLED] = 1;
				delete value;
			}
			else
			{
				config->insert_value(value);
				states[KEY_FILLED] = 0;
			}
		}
	}
}

Config *
Json::read(char const *path)
{
	bool	states[NSTATES];
	Config		*config;
	std::fstream file;
	std::string	 line;

	memset(states, 0, sizeof(bool) * NSTATES);
	file.open(path, std::fstream::in);

	/* Check if the file is valid */
	if (file.is_open() == 0)
	{
		std::cerr << "Error: Json::read(): file \"" << path << "\" is not valid" << std::endl;
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
