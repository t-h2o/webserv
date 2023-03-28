#include "utils_json.hpp"

namespace json
{

static void
print_line(std::string const &line, size_t index)
{
	std::cout << line << "\n";
	for (; index != 0; --index)
		std::cout << ' ';
	std::cout << '^' << std::endl;
}

static void
_print_case(std::string const &line, size_t index, bool states[NSTATES], bool show_states)
{
	if (!show_states)
		print_line(line, index);
	else
		std::cout << "Undefined case\n"
				  << states[OBJECT] << " OBJECT\n"
				  << states[STRING] << " STRING\n"
				  << states[KEY_FILLED] << " KEY_FILLED\n"
				  << states[MIDDLE] << " MIDDLE\n"
				  << states[RIGHT] << " RIGHT\n"
				  << states[VALUE_FILLED] << " VALUE_FILLED\n"
				  << states[END] << " END\n"
				  << std::endl;
}

static void
_set_states(char character, bool states[NSTATES])
{
	if (states[MIDDLE])
	{
		states[MIDDLE] = 0;
		states[RIGHT] = 1;
	}
	else if (states[END])
	{
		states[RIGHT] = 0;
		states[KEY_FILLED] = 0;
		states[VALUE_FILLED] = 0;
		states[END] = 0;
	}
	if (character == '{')
	{
		states[OBJECT] = 1;
	}
	else if (character == '}')
	{
		if (states[OBJECT] == 0)
			throw std::runtime_error("Json: object didn't start by a '{'");
		states[OBJECT] = 0;
	}
	else if (character == '"')
	{
		states[STRING] ^= 1;
	}
	else if (character == ':')
	{
		states[MIDDLE] = 1;
	}
	else if (character == ',')
	{
		states[END] = 1;
	}
}

/* process a line of the json */
void
_process_line(t_object *config, std::string const &line, bool states[NSTATES])
{
	double						  number;
	char						 *end;
	size_t						  index(0);
	std::pair<std::string, Value> value;

	_ignore_blank(line, index);
	while (line[index])
	{
		_set_states(line[index], states);
		if (LOG)
			_print_case(line, index, states, false);

		if (states[OBJECT] && states[STRING] && !states[KEY_FILLED] && !states[MIDDLE] && !states[RIGHT]
			&& !states[VALUE_FILLED] && !states[END])
		{
			if (LOG)
				std::cout << "take the key" << std::endl;
			value.first = _get_string(line, index);
			states[KEY_FILLED] = 1;
		}
		else if (states[OBJECT] && states[STRING] && states[KEY_FILLED] && !states[MIDDLE] && states[RIGHT]
				 && !states[VALUE_FILLED] && !states[END])
		{
			if (LOG)
				std::cout << "take the value (string)" << std::endl;
			value.second = Value(new std::string(_get_string(line, index)));
			config->insert(value);
			states[VALUE_FILLED] = 1;
		}
		else if (states[OBJECT] && !states[STRING] && states[KEY_FILLED] && !states[MIDDLE] && states[RIGHT]
				 && !states[VALUE_FILLED] && !states[END])
		{
			if (LOG)
				std::cout << "take the value (number)" << std::endl;
			number = strtod(&(line[index]), &end);
			value.second = Value(new double(number));
			config->insert(value);
			index += end - &(line[index]) - 1;
			states[VALUE_FILLED] = 1;
		}
		else if (states[OBJECT] && !states[STRING] && states[KEY_FILLED] && !states[MIDDLE] && states[RIGHT]
				 && states[VALUE_FILLED] && !states[END])
		{
			if (LOG)
				std::cout << "value end of string" << std::endl;
		}
		else if (states[OBJECT] && !states[STRING] && !states[KEY_FILLED] && !states[MIDDLE] && !states[RIGHT]
				 && !states[VALUE_FILLED] && !states[END])
		{
			if (LOG)
				std::cout << "start object" << std::endl;
		}
		else if (!states[OBJECT] && !states[STRING] && states[KEY_FILLED] && !states[MIDDLE] && states[RIGHT]
				 && states[VALUE_FILLED] && !states[END])
		{
			if (LOG)
				std::cout << "end of object" << std::endl;
		}
		else if (states[OBJECT] && !states[STRING] && states[KEY_FILLED] && states[MIDDLE] && !states[RIGHT]
				 && !states[VALUE_FILLED] && !states[END])
		{
			if (LOG)
				std::cout << "middle -> ':'" << std::endl;
		}
		else if (states[OBJECT] && !states[STRING] && states[KEY_FILLED] && !states[MIDDLE] && !states[RIGHT]
				 && !states[VALUE_FILLED] && !states[END])
		{
			if (LOG)
				std::cout << "end of key" << std::endl;
		}
		else if (states[OBJECT] && !states[STRING] && states[KEY_FILLED] && !states[MIDDLE] && states[RIGHT]
				 && states[VALUE_FILLED] && states[END])
		{
			if (LOG)
				std::cout << "comma" << std::endl;
		}
		else
		{
			if (LOG)
				_print_case(line, index, states, true);
			throw std::runtime_error("Json: undefined state");
		}
		++index;
		_ignore_blank(line, index);
	}
}

} /* namespace json */
