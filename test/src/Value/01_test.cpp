#include "Stream.hpp"

#include "Value.hpp"

int
test_output(json::Value const &value, std::string const &expected_cout)
{
	Stream output;

	output.open();

	std::cout << value << std::endl;

	if (output.check(expected_cout, ""))
	{
		output.close();
		return 1;
	}

	output.close();
	return 0;
}

int
test_value_string(void)
{
	json::Value val1(new std::string("Hello"));
	json::Value val2 = json::Value(new std::string("World"));
	json::Value val3(val2);

	if (val1.get<std::string>() != "Hello")
		return 1;

	if (val2.get<std::string>() != "World")
		return 1;

	if (val3.get<std::string>() != "World")
		return 1;

	if (test_output(val1, "\"Hello\"\n"))
		return 1;

	if (test_output(val2, "\"World\"\n"))
		return 1;

	if (test_output(val3, "\"World\"\n"))
		return 1;

	return 0;
}
