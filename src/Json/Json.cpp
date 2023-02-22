#include "Json.hpp"

enum e_states
{
	WHITESPACE,
	OBJECT,
	STRING,
	KEY_FILLED,
};

/* get the string value */
std::string
Json::_get_string(std::string const &line, size_t &index)
{
	std::string value;

	while (line[index] && line[index] != '"')
		value += line[index++];

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
Json::_process_line(Config *config, std::string const &line)
{
	static bool states[4];
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
	Config		*config;
	std::fstream file;
	std::string	 line;

	config = new Config;

	file.open(path, std::fstream::in);

	/* Read each lines up to EOF */
	for (getline(file, line); !file.eof(); getline(file, line))
		_process_line(config, line);

	file.close();

	return config;
}
