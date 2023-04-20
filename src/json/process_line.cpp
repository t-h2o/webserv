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
_print_case(File &file, bool states[NSTATES])
{
	print_line(file.get_current_string(), file.get_index());

	std::cout << states[OBJECT] << " OBJECT\n"
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
_process_line(t_object *config, File &file, bool states[NSTATES])
{
	std::pair<std::string, Value> value;
	char						  actual_char;

	actual_char = file.get_char();
	while (!file.eof())
	{
		_set_states(actual_char, states);
		if (LOG)
			_print_case(file, states);

		if (states[OBJECT] && states[STRING] && !states[KEY_FILLED] && !states[MIDDLE] && !states[RIGHT]
			&& !states[VALUE_FILLED] && !states[END])
		{
			if (LOG)
				std::cout << "take the key" << std::endl;
			value.first = file.get_string();
			states[KEY_FILLED] = 1;
		}
		else if (states[OBJECT] && states[STRING] && states[KEY_FILLED] && !states[MIDDLE] && states[RIGHT]
				 && !states[VALUE_FILLED] && !states[END])
		{
			if (LOG)
				std::cout << "take the value (string)" << std::endl;
			value.second = Value(new std::string(file.get_string()));
			config->insert(value);
			states[VALUE_FILLED] = 1;
		}
		else if (states[OBJECT] && !states[STRING] && states[KEY_FILLED] && !states[MIDDLE] && states[RIGHT]
				 && !states[VALUE_FILLED] && !states[END])
		{
			if (LOG)
				std::cout << "take the value (number)" << std::endl;
			value.second = Value(new double(file.get_number()));
			config->insert(value);
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
				_print_case(file, states);
			throw std::runtime_error("Json: undefined state");
		}
		actual_char = file.get_next_char();
	}
}

} /* namespace json */
